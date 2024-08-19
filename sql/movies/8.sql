SELECT people.name
FROM movies, people, stars
WHERE stars.person_id = people.id
AND stars.movie_id = movies.id
AND movies.title = 'Toy Story';
