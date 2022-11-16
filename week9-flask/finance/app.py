import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

''' create sqlite3 tables

buy_orders
CREATE TABLE buy_orders (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, symbol TEXT NOT NULL, share_qty INTEGER NOT NULL, price NUMERIC NOT NULL, datetime TIMESTAMP, side TEXT NOT NULL DEFAULT BUY);

sell_orders
CREATE TABLE sell_orders (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, symbol TEXT NOT NULL, share_qty INTEGER NOT NULL, price NUMERIC NOT NULL, datetime TIMESTAMP, side TEXT NOT NULL DEFAULT SELL);

positions
CREATE TABLE positions (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, symbol TEXT NOT NULL, share_qty INTEGER NOT NULL, price NUMERIC NOT NULL);
'''

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # get user information
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    user_name = rows[0]["username"]

    # get positions information for user
    positions = db.execute("SELECT * FROM positions WHERE username = ?", user_name)

    # calculate current stock price, purchase value and current value for each position
    for position in positions:
        position["current_price"] = lookup(position['symbol'])['price']
        position["name"] = lookup(position['symbol'])['name']
        position["current_value"] = position["share_qty"] * position["current_price"]

    # calculate cash
    current_cash = db.execute("SELECT cash FROM users WHERE username = ?", user_name)[0]['cash']

    # calculate position net liq
    total_portfolio_value = current_cash
    for position in positions:
        total_portfolio_value += position["current_value"]

    # format as usd
    for position in positions:
        position["current_price"] = usd(position["current_price"])
        position["current_value"] = usd(position["current_value"])

    return render_template("index.html", positions=positions,
                                         current_cash=usd(current_cash),
                                         total_portfolio_value=usd(total_portfolio_value),
                                         user_name=user_name)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    user_name = rows[0]["username"]

    if request.method == "POST":  # POST

        # get user information
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        user_name = rows[0]["username"]

        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)  # error, no symbol

        elif lookup(request.form.get("symbol")) == None:
            return apology("symbol not available", 400)  # error, IEX doesn't have symbol

        elif not request.form.get("shares"):
            return apology("must provide a number of shares", 400)  # error, no share count

        if not request.form.get("shares").isdigit():
            return apology("You cannot purchase partial shares.")  # error, not digit

        # gather all variables
        symbol = request.form.get("symbol")
        time = datetime.datetime.now()

        price = lookup(request.form.get("symbol"))['price']  # share price
        share_qty = int(request.form.get("shares"))  # requested share buy count
        user_cash = db.execute("SELECT cash FROM users WHERE username = ?", user_name)[0]['cash']

        bpr = float(price) * float(share_qty)  # cash required to purchase shares

        if user_cash < bpr:
            return apology("insufficient funds", 400)  # account doesn't have enough cash for this buy

        # insert into buy_orders table
        db.execute("INSERT INTO buy_orders (username, symbol, share_qty, price, datetime) VALUES(?, ?, ?, ?, ?)",
                   user_name, symbol, share_qty, price, time)

        # insert into positions table
        # check if user already has shares
        # get positions information for user
        positions = db.execute("SELECT * FROM positions WHERE username = ?", user_name)

        current_position_symbols = []
        for position in positions:
            current_position_symbols.append(position['symbol'])

        if symbol in current_position_symbols:   # only update share quantity
            current_shares = db.execute("SELECT share_qty FROM positions WHERE username = ? AND symbol = ?",
                                        user_name, symbol)[0]['share_qty']  # available shares for symbol

            new_shares = current_shares + share_qty
            db.execute("UPDATE positions SET share_qty = ? WHERE username = ? AND symbol = ?", new_shares, user_name, symbol)
        else:
            db.execute("INSERT INTO positions (username, symbol, share_qty, price) VALUES(?, ?, ?, ?)",
                       user_name, symbol, share_qty, price)

        # update user's cash position to reflect this new purchase
        new_cash = user_cash - bpr
        db.execute("UPDATE users SET cash = ? WHERE username = ?", new_cash, user_name)

        # Redirect user to home page
        flash("Bought!")
        return redirect("/")

    else:  # GET

        return render_template("buy.html", user_name=user_name)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # get user information
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    user_name = rows[0]["username"]

    # get positions information for user
    history = db.execute("SELECT * FROM buy_orders UNION SELECT * FROM sell_orders WHERE username = ? ORDER BY datetime", user_name)

    # format as usd
    for order in history:
        order["price"] = usd(order["price"])

    return render_template("history.html", history=history, user_name=user_name)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":  # user has just submitted login form

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)  # error, no username

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)  # error, no password

        # Query database for username
        # the question mark serves as a filler for the query
        # what's returned from this request is all of the rows that matched our select query
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        # check we only get one row back
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)  # error, invalid username/password combination

        # Remember which user has logged in
        # made it through all checks
        # session variable keeps track of information on the current user
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/reset", methods=["GET", "POST"])
@login_required
def reset():
    """Reset password"""
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    user_name = rows[0]["username"]

    if request.method == "POST":  # POST

        if not request.form.get("username"):
            return apology("must provide username", 403)  # error, no password

        # Ensure password was submitted
        elif not request.form.get("oldpass"):
            return apology("must provide old password", 403)  # error, no password

        # Ensure password was submitted
        elif not request.form.get("newpass"):
            return apology("must provide new password", 403)  # error, no new password

        # Ensure password-confirmation was submitted
        elif not request.form.get("newpass-confirmation"):
            return apology("must confirm new password", 403)  # error, no new password

        # Ensure old password is correct
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("oldpass")):
            return apology("invalid username and/or password", 403)  # error, invalid username/password combination

        # Ensure new passwords match
        if request.form.get("newpass") != request.form.get("newpass-confirmation"):
            return apology("passwords do not match", 400)

        # hash newpass
        user_newpass = generate_password_hash(request.form.get("newpass"))

        # Update database
        db.execute("UPDATE users SET hash = ? WHERE username = ?", user_newpass, user_name)

        flash("Password reset successfully")

        return render_template("reset.html", user_name=user_name)

    else:

        return render_template("reset.html", user_name=user_name)


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # fetch quote
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    user_name = rows[0]["username"]

    if request.method == "POST":  # POST
        # Ensure ticker was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)  # error, no username

        symbol = request.form.get("symbol")  # store symbol i.e. AAPL

        if lookup(symbol) == None:
            return apology("symbol not available", 400)  # error, IEX doesn't have symbol

        symbol_info = lookup(symbol)  # get symbol information from IEX
        symbol_name = symbol_info['name']  # store symbol_name i.e. Apple Inc
        price = usd(symbol_info['price'])  # store price, formatted as currency

        return render_template("quoted.html", symbol=symbol,
                                              symbol_name=symbol_name,
                                              price=price,
                                              user_name=user_name)

    else:  # GET
        return render_template("quote.html", user_name=user_name)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # register user
    if request.method == "POST":  # POST

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)  # error, no username

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # ensure username doesn't already exist
        if len(rows) > 0:
            return apology("username already exists", 400)  # error, username already exists

        # ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)  # error, no password

        # ensure password-confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("must confirm password", 400)  # error, no password

        # ensure passwords match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # hash the password
        user_name = request.form.get("username")
        user_pass = generate_password_hash(request.form.get("password"))

        # insert user into database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", user_name, user_pass)

        # log user in
        rows = db.execute("SELECT * FROM users WHERE username = ?", user_name)

        # log the user in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # log user in
    else:  # GET
        # display a form for user to register for an account
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    user_name = rows[0]["username"]
    if request.method == "POST":  # POST

        # get user information
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        user_name = rows[0]["username"]

        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)  # error, no symbol

        # check is user doesn't own any stocks
        # get positions information for user
        positions = db.execute("SELECT * FROM positions WHERE username = ?", user_name)

        if len(positions) == 0:
            return apology("can only sell what you own", 400)  # error, no symbol

        elif not request.form.get("shares"):
            return apology("must provide a number of shares", 400)  # error, no share count

        # gather all variables

        symbol = request.form.get("symbol")
        time = datetime.datetime.now()

        price = lookup(request.form.get("symbol"))['price']  # share price
        share_qty = int(request.form.get("shares"))  # requested share sell count
        user_cash = db.execute("SELECT cash FROM users WHERE username = ?", user_name)[0]['cash']  # available cash

        current_shares = db.execute("SELECT share_qty FROM positions WHERE username = ? AND symbol = ?",
                                    user_name, symbol)[0]['share_qty']  # available shares for symbol

        if share_qty > current_shares:
            return apology("cannot sell more shares than you own", 400)  # error, no share count

        # cash freed up from sale
        bpr = float(price) * float(share_qty)

        # insert order into sell_orders table
        db.execute("INSERT INTO sell_orders (username, symbol, share_qty, price, datetime) VALUES(?, ?, ?, ?, ?)",
                   user_name, symbol, share_qty, price, time)

        # update into positions table
        new_shares = current_shares - share_qty
        db.execute("UPDATE positions SET share_qty = ? WHERE username = ? AND symbol = ?", new_shares, user_name, symbol)

        # update user's cash position to reflect this new purchase
        new_cash = user_cash + bpr
        db.execute("UPDATE users SET cash = ? WHERE username = ?", new_cash, user_name)

        # redirect user to home page
        flash("Sold!")
        return redirect("/")

    else:  # GET
        # # gather all variables
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        user_name = rows[0]["username"]

        # get positions information for user
        positions = db.execute("SELECT * FROM positions WHERE username = ?", user_name)

        return render_template("sell.html", positions=positions, user_name=user_name)
