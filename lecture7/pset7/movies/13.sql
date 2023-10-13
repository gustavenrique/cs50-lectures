--write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT 
    DISTINCT name 
FROM 
    people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON movies.id = stars.movie_id
WHERE 
    movies.id IN (
        SELECT DISTINCT movies.id FROM movies
        JOIN stars ON stars.movie_id = movies.id
        JOIN people ON stars.person_id = people.id
        WHERE people.name = 'Kevin Bacon'
    )
    AND NOT (people.name = 'Kevin Bacon');