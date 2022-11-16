--write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
SELECT title
FROM movies
JOIN ratings
ON movies.id = ratings.movie_id
WHERE(movie_id IN (SELECT movie_id
                    FROM people
                    JOIN stars
                    on people.id = stars.person_id WHERE(name = "Chadwick Boseman")))
ORDER BY rating DESC
LIMIT(5);

-- ALTERNATIVELY... --
-- SELECT title
-- FROM movies as m
-- JOIN ratings as r
-- ON m.id = r.movie_id
-- JOIN stars as s
-- ON s.movie_id = m.id
-- JOIN people as p
-- ON p.id = s.person_id
-- WHERE name = "Chadwick Boseman"
-- ORDER BY rating DESC
-- LIMIT(5);