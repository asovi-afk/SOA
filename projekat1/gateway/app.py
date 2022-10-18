import json
from urllib import request
import requests
from flask import Flask
app = Flask(__name__)

url = "https://mdblist.p.rapidapi.com/"
querystring = {"s":"jaws"}

headers = {
    "X-RapidAPI-Key": "d1bc709fe3msh074561e6633c519p1f14efjsn5eb5c2d330cf",
    "X-RapidAPI-Host":"mdblist.p.rapidapi.com"
}


# # ne bih da radimo sa serijama, dovoljni su filmovi
# # routes
# movie/alltitles
# # response kako želiš

# movie/suggestions
# r = {
#     "max-duration": 128, # in minutes
#     "genere": ["Dramas", "Comedies"], # mozda ID za zanrove?
#     "release-year": 1998, # from this year
#     "director": ["Andy Devonshire", "Theodore Melfi"], # atleast one of listed
#     "cast": ["Kofi Ghanaba", "Oyafunmike Ogunlano"] #atleast one of listed
# }
# # response -> [ {sve o filmu 1}, {sve o filmu 2}] sa ID-jem filma

# movie/delete
# r ={
#     "id": "movie id"
# }

# movie/create 
# r = {
#     "title": "ttttt",
#     "director": ["dir 1", "dir 2"],
#     "cast": ["ac 1", "ac 2"], 
#     "country": "Serbia",
#     #"date-added": "asatat" da se ne zanosimo sa formatom, izostavio bih ovo polje
#     "release-year": 2022,
#     "rating": "PG-13", # mozemo da izostavimo
#     "genere": ["Comedies", "Dramas"],
#     "description": "BIG BIG BIG string"
# }

# movie/update
# r = {
#     "id": "s21",
#     # svi parametri sa kojim želiš da radiš
#     # ako je parametar null onda se ne menja
#     # ako parametar nije null onda se postavlja
# }


@app.route('/test/')
def test():
    response = requests.request("GET", url, headers=headers, params=querystring)
    return response.json()


@app.route('/')
def index():
    return json.dumps({'name': 'alice',
                       'email': 'alice@outlook.com'})
app.run()