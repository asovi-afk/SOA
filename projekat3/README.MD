# Projekat 3

  

Sastoji se od 2 compose fajla.

Prvi se odnosi na mikroservise u sklopu oblaka, a drugi na edge mikroservise i edgex foundry sistem.
Pre startovanja bilo kog mikroservisa treba kreirati mrežu koja spaja servise iz oba compose fajla:

    docker network create cloud-network

Preći u 'cloud' direktorijum i pozvati komandu 'docker-compose up -d'. Zatim pozvati istu komandu i iz direktorijuma 'edgex'. 
>Bitan je redosled pozivanja komandi.

Nakon što su svi mikroservisi spremni treba aktivirati skriptu komandom './init.bash' koja se nalazi u 'edgex' direktorijumu. Ova skripta će postaviti device-profile i registrovati konkretan device za odgovarajući profil.

Za vizuelizaciju pogledati 'grafana' mikroservis.

### CLOUD


##### 1. mqtt_brocker
MQTT Posrednik između cloud i edgex servisa.
Ima ulogu fasade. Njegovom Open API-ju se pristupa sa hosta preko: http://localhost:5000/swagger .
##### 2.isualization_influxdb
Čuva podatke koje generiš 'sensor_data_gen' mikroservis na south strani.
Pristup preko adrese 'http://localhost:8086'

    username: admin
    password: admin123

##### 3.grafana
Vizuelizacija podataka. Pristupa se preko adrese 'http://localhost:3000'. 

    username: admin
    password: admin
  Odabrati opciju "Add your first data source" i izabrati 'InfluxDB'. 
  Opcije:
  

    Query Language: Flux
    HTTP
    URL: http://v-influxdb:8086
    Auth
    Basic Auth: off
    InfluxDB Detail
    Organization: soa
    Token: UDVHkVrADVF1TpkdCVjaycO9vKJfhjRZeDrcd2nWZN1fzaoGrQiZyxL6ehTjRyj8OGZry8Hsp_fa_4VGLYd-_g==
    Default Bucket: visualization 

Kliknuti na  "Save & test"
- Trebalo bi da je pronašla 3 bucketa. ( uspešno povezivanje)
- Sada treba kreirati novi Dashboard: "Add a new panel" i kopirati query iz influxDB upita.

##### 4.visualization
Pretplaćen na mqtt topic preko kog dobija podatke od  'sensor_data_gen' mikroservisa i čuva ih u influxDB-u.
Pisan u golangu, a izvorni kod se nalazi u /cloud/go_test/visualization/ direktorijumu. Kontejner sadrži samo izvršnu datoteku.

### EDGEX
Pomenuti su samo mikroservisi na koje smo uticali ( konfigurisali ili kreirali)

##### 1. app-service-mqtt-export
Konfigurabilini edgex mikroservis kome smo definisali  pipeline kao execution order sa svim potrebnim parametrima da se podaci proslede to externog mqtt brokera ( cloud ).
##### 2.device-rest
Neophodan za komunikaciju sa eksternim uređajem koji koristi REST protokol. On je veza sa 'sensor_data_gen'.
> Napomena: Ideja je bila da bude veza i sa drugim mikroservisom 'controller_window', međutim ni edgex foundry version 2.3.0 ne podržava REST komande prema uređajima.

##### 3.sensor_data_gen
Čita podatke iz CSV fajla i šalje ih na svakih 5 sekundi.
##### 4.controller_window
REST uređaj koji reaguje na komande. Na žalost REST komande nisu podržane.
