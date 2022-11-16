--write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
SELECT DISTINCT(name)
FROM stars as s
JOIN people as p
ON s.person_id = p.id
WHERE movie_id IN (SELECT movie_id
                   FROM people as p
                   JOIN stars as s
                   ON s.person_id = p.id
                   WHERE birth = 1958 and name = "Kevin Bacon")
AND name != "Kevin Bacon";