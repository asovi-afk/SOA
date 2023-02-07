#! /bin/bash
DB='NetflixTitles'
mongosh --eval "use $DB && db.dropDatabase()" > /dev/null
mongoimport --db=$DB --collection=netflix_titles --type=csv --headerline --file=netflix_titles.csv > /dev/null 
echo "DB '$DB' reinitialized!"