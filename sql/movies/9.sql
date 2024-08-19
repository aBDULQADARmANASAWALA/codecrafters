-- Here we could have used JOIN but it had duplicate people names
-- those who appeared in multiple movies, but we did not want them
SELECT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT id
        FROM movies
        WHERE year = 2004
    )
)
ORDER BY birth;
