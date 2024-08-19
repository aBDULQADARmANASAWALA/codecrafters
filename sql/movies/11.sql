SELECT movies.title
FROM movies, people, stars, ratings
WHERE stars.movie_id = movies.id
AND stars.person_id = people.id
AND people.name = 'Chadwick Boseman'
AND ratings.movie_id = movies.id
ORDER BY ratings.rating DESC
LIMIT 5;
