SELECT title FROM movies WHERE id IN (SELECT stars.movie_id FROM stars JOIN ratings ON stars.movie_id = ratings.movie_id WHERE person_id IN(SELECT id FROM people WHERE name IS "Chadwick Boseman") ORDER BY rating DESC) LIMIT 5;
