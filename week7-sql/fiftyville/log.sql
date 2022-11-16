-- Keep a log of any SQL queries you execute as you solve the mystery.

-- .tables
-- .schema

-- select * from crime_scene_reports
-- WHERE year = 2021
-- AND month = 7
-- AND day = 28
-- AND street = "Humphrey Street";

-- check interview transcripts for word 'bakery'

-- select * from interviews
-- WHERE transcript LIKE "%bakery%"
-- AND year = 2021
-- AND month = 7
-- AND day = 28;

-- LIST OF SUSPECTS
-- RUTH, witness
-- Sometime within ten minutes of the theft,
-- I saw the thief get into a car in the bakery
-- parking lot and drive away. If you have security footage
-- from the bakery parking lot, you might want to look for
-- cars that left the parking lot in that time frame.

-- check bakery_security_logs on day of crime
-- according to crime_scene_reports, the theft took place at 10:15am
-- narrow our search to be one hour before and after that time
-- select *
-- FROM bakery_security_logs
-- WHERE year = 2021
-- AND month = 7
-- AND day = 28
-- AND hour >= 10 AND hour <= 11
-- AND minute >= 15 AND minute <= 59
-- AND activity = "exit";

-- this gives us a lot of plates
-- 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55, 1106N58

-- let's map these plates to their owners
-- select *
-- FROM bakery_security_logs
-- WHERE year = 2021
-- AND month = 7
-- AND day = 28
-- AND hour >= 10 AND hour <= 11
-- AND minute >= 15 AND minute <= 59
-- AND activity = "exit";

-- select *
-- FROM people
-- LIMIT(10);

-- SELECT *
-- FROM bakery_security_logs
-- JOIN people
-- ON bakery_security_logs.license_plate = people.license_plate
-- WHERE year = 2021
-- AND month = 7
-- AND day = 28
-- AND hour >= 10 AND hour <= 11
-- AND minute >= 15 AND minute <= 59
-- AND activity = "exit"
-- ORDER BY (name);

----------------------------------------------------------------------------------

-- Eugene, witness
-- I don't know the thief's name, but it was someone
-- I recognized. Earlier this morning, before I arrived
-- at Emma's bakery, I was walking by the ATM on
-- Leggett Street and saw the thief there withdrawing some money.

-- check atm_transactions on day of crime
-- SELECT *
-- FROM atm_transactions
-- WHERE year = 2021
-- AND month = 7
-- AND day = 28
-- AND atm_location = "Leggett Street";

-- let's map these account_numbers to their owners via the bank_accounts table
-- select *
-- FROM bank_accounts
-- LIMIT(10);

-- select *
-- FROM people
-- LIMIT(10);

-- SELECT *
-- FROM atm_transactions
-- JOIN bank_accounts
-- ON atm_transactions.account_number = bank_accounts.account_number
-- JOIN people
-- ON bank_accounts.person_id = people.id
-- WHERE year = 2021
-- AND month = 7
-- AND day = 28
-- AND atm_location = "Leggett Street"
-- ORDER BY (name);

----------------------------------------------------------------------------------

-- Raymond, witness
-- As the thief was leaving the bakery, they called someone
-- who talked to them for less than a minute. In the call,
-- I heard the thief say that they were planning to take
-- the earliest flight out of Fiftyville tomorrow. The thief
-- then asked the person on the other end of the phone to purchase
-- the flight ticket.

-- first let's look at phone calls...
-- SELECT *
-- FROM phone_calls
-- WHERE year = 2021
-- AND month = 7
-- AND day = 28
-- AND duration < 60;

-- let's map these phone numbers to their owners via the people table
-- select *
-- FROM people
-- LIMIT(10);

SELECT *
FROM phone_calls
JOIN people
ON phone_calls.caller = people.phone_number
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;

SELECT *
FROM phone_calls
JOIN people
ON phone_calls.receiver = people.phone_number
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;

-- unfortunately no time here either... but we do have the call duration
-- so we can add the filter where the phone call was less than 60 seconds long.
-- need to match this to some kind of data.

-- let's take a look at flight tickets. there are three associated tables here...
-- airports, bank_accounts, passengers, & flights.

SELECT *
FROM airports
JOIN flights
ON airports.id = flights.origin_airport_id
ORDER BY city;
looks like the id for Fiftyville Regional Airport is 8

-- now let's check the flights table where origin_airport_id = 8, i.e. Fiftyville Regional Airport
-- and where the flight is the day after the crime date
-- ordered by the earliest flight...

-- SELECT *
-- FROM flights
-- WHERE origin_airport_id = 8
-- AND year = 2021
-- AND month = 7
-- AND day = 29
-- ORDER BY hour;

-- so the earliest flight out of fiftyville took place at 8:20am
-- and the flight id is 36

-- let's see who the passengers were on that flight:
-- SELECT *
-- FROM passengers
-- WHERE flight_id = 36
-- ORDER BY passport_number;

-- now let's map identities to these passport_number by joining with the people table

-- SELECT *
-- FROM people
-- JOIN passengers
-- ON people.passport_number = passengers.passport_number
-- WHERE(people.passport_number in (SELECT passport_number
--                         FROM passengers
--                         WHERE flight_id = 36)
--      AND flight_id = 36)
-- ORDER BY name;

----------------------------------------------------------------------------------

-------------

-- SUSPECTS
-- RUTH, witness
-- Eugene, witness
-- Raymond, witness

-- Edward, on earliest flight from fiftyville on july, 29, 2021
-- Sofia, on earliest flight from fiftyville on july, 29, 2021
-- Taylor, on earliest flight from fiftyville on july, 29, 2021
-- Bruce, on earliest flight from fiftyville on july, 29, 2021
-- Doris, on earliest flight from fiftyville on july, 29, 2021
-- Kelsey, on earliest flight from fiftyville on july, 29, 2021
-- Luca, on earliest flight from fiftyville on july, 29, 2021
-- Kenny, on earliest flight from fiftyville on july, 29, 2021

-- Vanessa, license plate seen leaving the bakery shortly after the crime took place on july, 28, 2021
-- Bruce, license plate seen leaving the bakery shortly after the crime took place on july, 28, 2021
-- Barry, license plate seen leaving the bakery shortly after the crime took place on july, 28, 2021
-- Luca, license plate seen leaving the bakery shortly after the crime took place on july, 28, 2021
-- Sofia, license plate seen leaving the bakery shortly after the crime took place on july, 28, 2021
-- Iman, license plate seen leaving the bakery shortly after the crime took place on july, 28, 2021
-- Diana, license plate seen leaving the bakery shortly after the crime took place on july, 28, 2021
-- Kelsey, license plate seen leaving the bakery shortly after the crime took place on july, 28, 2021
-- Taylor, license plate seen leaving the bakery shortly after the crime took place on july, 28, 2021

-- Benista, account number matches that of ATM activity on the day the crime took place on july, 28, 2021
-- Brooke, account number matches that of ATM activity on the day the crime took place on july, 28, 2021
-- Bruce, account number matches that of ATM activity on the day the crime took place on july, 28, 2021
-- Diana, account number matches that of ATM activity on the day the crime took place on july, 28, 2021
-- Iman, account number matches that of ATM activity on the day the crime took place on july, 28, 2021
-- Kaelyn, account number matches that of ATM activity on the day the crime took place on july, 28, 2021
-- Kenny, account number matches that of ATM activity on the day the crime took place on july, 28, 2021
-- Luca, account number matches that of ATM activity on the day the crime took place on july, 28, 2021
-- Taylor, account number matches that of ATM activity on the day the crime took place on july, 28, 2021






-- there's a lot of overlap here...
-- bruce
-- luca

-------------

