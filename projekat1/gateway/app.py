import json
from urllib import request
import requests
import argparse
from flask import Flask, request, Response
from flask_mqtt import Mqtt

from flask_socketio import SocketIO
from flask_bootstrap import Bootstrap

from flask_swagger_ui import get_swaggerui_blueprint

#from flasgger import Swagger, LazyString, LazyJSONEncoder, swag_from

app = Flask(__name__)

#app.json_encoder = LazyJSONEncoder

def parse_boolean(value):
    return value == "True"

parser = argparse.ArgumentParser()
parser.add_argument("-p", "--project", dest = "project", default = 2, type = int, help = "Project 2 uses MQTT")
parser.add_argument("-ua", "--use-api", dest = "use_api", default = False, type = parse_boolean, help = "Using external API")
args = parser.parse_args()

SWAGGER_URL = '/swagger'
API_URL = '/static/openapi.yml'
SWAGGERUI_BLUEPRINT = get_swaggerui_blueprint(
    SWAGGER_URL,
    API_URL,
    config={
        'app_name': "Gateway API"
    }
)

app.register_blueprint(SWAGGERUI_BLUEPRINT, url_prefix=SWAGGER_URL)

app.config['MQTT_BROKER_URL'] = 'mosquitto'
app.config['MQTT_BROKER_PORT'] = 1883
app.config['MQTT_CLIENT_ID'] = 'gateway'
app.config['MQTT_KEEPALIVE'] = 5  # Set KeepAlive time in seconds
app.config['MQTT_TLS_ENABLED'] = False  # If your server supports TLS, set it True

topic = "analytics/requests/signal"

print("ARGS")
print(args)

if args.project == 2: 
    mqtt_client = Mqtt(app)
    socketio = SocketIO(app)
    bootstrap = Bootstrap(app)

    @mqtt_client.on_connect()
    def handle_connect(client, userdata, flags, rc):
        if rc == 0:
            print('Connected to MQTT')
        else :
            print('Bad MQTT connection. Code: ', rc)

    @socketio.on('publish')
    def handle_publish(json_str):
        data = json.loads(json_str)
        mqtt.publish(data['topic'], data['message'], data['qos'])

url = "https://mdblist.p.rapidapi.com/"

headers = {
    "X-RapidAPI-Key": "d1bc709fe3msh074561e6633c519p1f14efjsn5eb5c2d330cf",
    "X-RapidAPI-Host":"mdblist.p.rapidapi.com"
}

apiUrl = "http://api:3000/movie/"
traktTvUrl = "https://trakt.tv/movies/"
imdbUrl = "https://www.imdb.com/title/"

def publis_title(title):
    publish_result = mqtt_client.publish(topic, "{\"title\": \""+title+"\"}")

@app.route('/', methods = ['GET'])
def get():
    apiResponse = requests.request('GET', apiUrl, params=request.args.to_dict())
    if apiResponse.status_code == 200:
        movie = apiResponse.json()
        print(movie)
        if args.project == 2:
            publis_title(movie["title"])

        if args.use_api:
            mdbResponse = requests.request('GET', url, headers=headers, params = {"s": movie["title"]}) 
            if mdbResponse.status_code == 200:
                mdb = mdbResponse.json()
                if mdb["response"] == True and mdb["total"] > 0:
                    for item in mdb["search"]:
                        if item["type"] == "movie" and item["title"] == movie["title"]:
                            movie.update({"score_average": item["score_average"]})
                            if item["imdbid"] != None:
                                movie.update({"imdb":imdbUrl+str(item["imdbid"])})
                            if item["traktid"] != None:
                                movie.update({"trakt":traktTvUrl+str(item["traktid"])})
                            break
        else:
            movie.update({"score_average": None})
            movie.update({"imdb": None})
            movie.update({"trakt": None})

        return movie, apiResponse.status_code
    else :
        return Response(status = apiResponse.status_code) 

@app.route('/create', methods = ['POST'])
def create():
    data = request.get_json()
    apiResponse = requests.request("POST", apiUrl+"create", json=data)
    if apiResponse.status_code == 201:
        return apiResponse.json(), apiResponse.status_code
    else :
        return Response(status = apiResponse.status_code) 
        
@app.route('/update', methods = ['PUT'])
def update():
    data = request.get_json()
    apiResponse = requests.request("PUT", apiUrl+"update", json=data)
    return Response(status = apiResponse.status_code) 

@app.route('/delete', methods = ['DELETE'])
def delete():
    data = request.get_json()
    apiResponse = requests.request("DELETE", apiUrl, json=data)
    return Response(status = apiResponse.status_code) 

@app.route('/suggestions', methods = ['POST'])
def suggestions():
    data = request.get_json()
    print(data)
    apiResponse = requests.post(apiUrl+"suggestions", json=data)
    print(apiResponse.status_code)
    
    return apiResponse.json() if apiResponse.status_code == 200 else Response(status=apiResponse.status_code)


if __name__ == "__main__":
    app.run(host='0.0.0.0',debug=False)