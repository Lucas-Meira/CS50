SELECT DISTINCT name FROM
people JOIN stars ON people.id=stars.person_id
WHERE movie_id IN
(SELECT DISTINCT id FROM movies
INTERSECT
SELECT DISTINCT movies.id FROM
movies JOIN stars ON movies.id=stars.movie_id JOIN
people ON people.id=stars.person_id
WHERE name = "Kevin Bacon"
AND birth = 1958)
AND name IS NOT "Kevin Bacon"
ORDER BY name;
