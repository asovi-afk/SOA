# Projekat 2

Sastojie se od 8 mikroservisa.
Pokrenuti komandom 'docker-compose up', nakon čega treba popuniti bazu pozivom skritpe 'initDB.sh' koja se nalazi u direktorijumu 'projekat2'.

> Preporuka je prvo pročitati sažetak za osmi (analytics) mikroservis koji objašnjava princip rada.

##### 1. gateway
Sve važi kao i za prvi projekat.
Proširena funkcionalnost se nalazi samo u GET metodi. To je prosleđivanje zahtevanih naslova MQTT brokeru preko topic-a "analytics/requests/signal".

##### 2. api ( /node_api/)
Kao i za prvi projekat.
##### 3. mongo_db (/database/)
Kao i za prvi projekat. 
> volume je nezavisan od volume-a za prvi projekat. Treba ga popuniti skriptom.

##### 4. mosquitto
MQTT broker.

##### 5. ekuiper
Analizira događaje u vremenu.
- spike_rule 
vodi evidenciju o broju zahteva za svaki naslov koji se javio u SESSION WINDOW vremenskom prozoru 15 + 5 sekundi (https://ekuiper.org/docs/en/latest/sqls/windows.html)
- formating_rule 
poziva našu aggregate funkciju 'register()', a za ulaz prosleđuje evidenciju prethodnog pravila.
- register() (*ekuiper/config_set/highlights/register_func.go*) 
određuje da li je nastao događaj od značaja.
Pisana u go-u.

Da bi ovakav događaj uopšte postojao neophodno je da su u vremenskom prozoru registrovana barem 3 zahteva ( 3 gateway GET zahteva). Ako je prvi uslov ispunjen biraju se svi naslovi koji učestvuju sa barem 40% od ukupnog broja GET zahteva. Lista ovih naslova je značajan događaj koji se prosleđuje 'analytics' servisu preko "analytics/results/filter" topic-a.
Primer 1:
> - spike_rule registruje: 
[{title: "Ivkova slava", count: 2}]
> - register() vidi samo 2 zahteva, pa smatra da je interesovanje slabo
> - analytics prima [] (prazan niz)

Primer 2:
> - spike_rule registruje:
[{title: "Ivkova slava", count: 2}, {title: "Betmen", count: 1}, {title: "Leptirica", count: 2}]
> - register() vidi 5 zahteva, pa smatra da je interesovanje jako. Sada proverava da li postoje naslovi koji se izdvajaju:
"Ivkova slava" i "Leptirica" učestvuju sa po 40% od ukupnog broja zahteva, pa se registruju kao događaj od značaja ( postoji veliko interesovanje za ovim filmovima). 
Betmen učestvuje sa 20% (zanemarljivo interesovanje).
> - analytics prima ["Ivkova slava", "Leptirica"]

Povremeno se dešava da ovaj servis ne radi kako treba, tj. vraća prazan niz iako bi trebalo da vrati neki naslov.
Zato je dobro proveriti sa 3 uzastopna i ista 'gateway' GET zahteva.
Ako ekuiper ne vraća dobar rezultat treba ga restartovati komandom `docker-compose restart ekuiper`.

##### 6. analytics_influxdb
Obezbeđuje influxdb NoSQL bazu podataka za 'analytics' mikroservis. 
Pristup je na adresi http://localhost:8086.
username: admin
password: admin123
Da bi se pročitali podaci treba:
1. otvoriti bucket 'analytics'
2. umesto 'Graph' izabrati 'Table' 
3. promeniti WINDOW PERIOD na CUSTOM  i postaviti na '10ms' 
4. promeniti aggregate function sa 'mean' na 'last' ( jedino na 'last' radi jer je u pitanju string - "Title")
5. za 'from' odabrati 'analytics' 
6. za prvi filter odabrati bilo šta od ponuđenog
7. SUBMIT

> Ako ništa nije ponuđeno od filtera treba uneti barem neku vrednost (pozivom gateway GET metode), a potom ponovo otvoriti bucket.

##### 7. notification (/notify_server/)
Server stub za gRPC servis definisan u 'notify.proto' fajlu.
Prima niz naslova od 'analytics' mikroservisa i loguje ih u logs.txt fajlu. Ovaj fajl se nalazi u kontejneru, a može se pratiti sa hosta pozivom skripte 'notification_logs.sh'.

Pisan u cpp-u (server.cc).

##### 8. analytics
Pretplaćuje se na mosquitto mikroservis.
Princip rada:
1. sa topic-a "analytics/requests/signal" prima naslove traženih filmova od 'gateway-a'
2. Svaki naslov upisuju u influxdb ('analytics_influxdb') i prosleđuje 'ekuiper-u' na analizu preko "analytics/requests/filter" topic-a 
3. od 'ekuiper-a' prima rezultate analize (događaj od značaja) preko "analytics/results/filter" topic-a
4. Ako značajan događaj postoji (rezultat nije prazan niz) on angažuje 'notification' mikroservis preko gRPC-a ( 'Obaveštavanje')
 - ponaša se ka gRPC klijent

Praćenje izlaza samo ovog servisa je poželjno. Praćenje se može ostvariti komandom `docker-compose logs -f analytics`.

FROM alpine:3.16 
Ima samo izvršnu datoteku

###### 8.1. analytics_test 
FROM golang:1.19-buster
Sadrži izvorni kod 'analytics' mikroservisa. 
Pisan je u go-u: analytics_test/analytics/main.go
Proto fajl: analytics_test/analytics/notify/notify.proto
Test gRPC server: analytics_test/analytics/notification/main.go
