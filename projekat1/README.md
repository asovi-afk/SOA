# Projekat 1

Sastoji se od 3 mikroservisa.
Pokrenuti komandom 'docker-compose up', nakon čega treba popuniti bazu pozivom skritpe 'initDB.sh'.

##### 1. gateway
Ima ulogu fasade. Njegovom Open API-ju se pristupa sa hosta preko: http://localhost:5000/swagger .
Komunicira sa 'api' mikroservisom i u kombinaciji sa eksternim API-jem (https://rapidapi.com/linaspurinis/api/mdblist) svaki get zahtev dopunjuje sa linkom o traženom filmu na IMDB i tracktortv web stranicama.
> Napomena: Eksterni API podržava samo 100 zahteva dnevno. Zato smo bili prinuđeni da ga koristimo za pojedinačne filmove, a ne i za sugestije.

U 'docker-compose.yml' fajlu su za ovaj mikroservis postavljena dva parametra preko 'command' tag-a.
Bitno je da parametar '--project' ostane na '1' jer u suprotnom mikroservis neće raditi. Razlog za uvođenje parametara je u tome što se za drugi projekat koristi isti mikroservis, ali sa proširenim funkcionalnostima.

Pisan je u python-u.
##### 2. api ( /node_api/)
Rest api koji upisuje i čita podatke iz 'mongo_db' mikroservisa.

Pisan je u node-u.
##### 3. mongo_db (/database/)
mongodb - čuva podatke o filmovima.
Podaci se ne čuvaju u kontejneru, već u volume-u.
`docker-compose up` komanda će kreirati kontejnere i volume 'db_data' koji će inicijalno biti prazan. Zato je neophodno da se za svaki prazan volume sa hosta pozove skripta 'initDB.sh' koja će ga popuniti podacima. Ova skripta se može koristiti i za resetovanje podataka u bazi.