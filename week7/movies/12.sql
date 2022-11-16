-- write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.

SELECT title
FROM movies
JOIN stars
ON movies.id = stars.movie_id
WHERE(person_id IN (SELECT id
                    FROM people
                    WHERE name IN("Johnny Depp", "Helena Bonham Carter")))
GROUP BY title
HAVING COUNT(title) > 1;

-- ALTERNATIVELY... --
-- SELECT title
-- FROM movies as m
-- JOIN stars as s
-- ON m.id = s.movie_id
-- JOIN people as p
-- ON s.person_id = p.id
-- WHERE name IN("Johnny Depp", "Helena Bonham Carter")
-- GROUP BY title
-- HAVING COUNT(title) > 1;