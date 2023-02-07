
import requests
import json
import random
import time

import os
from csv import reader

if __name__ == "__main__":

    #edgexip = '192.168.100.13'; primer
    edgexip = os.environ.get('HOST_ADDRESS')
    if (edgexip is None):
        print("'HOST_ADDRESS' environment variable was not found!")
    else:    
        print('HOST_ADDRESS %s' %edgexip)
        with open("Occupancy.csv", "r") as dataFile:
            fileReader = reader(dataFile)
            # prvi red se preskace jer je naziv kolona
            next(fileReader)
            for row in fileReader:
                lightval = float(row[3])
                co2val = float(row[4])
                print("Sending values: Light %f, CO2 %f" % (lightval, co2val))

                url = 'http://%s:59986/api/v2/resource/Occupancy_sensor_cluster_01/light' % edgexip
                payload = lightval
                headers = {'content-type': 'application/json'}
                response = requests.post(url, data=json.dumps(payload), headers=headers, verify=False)

                url = 'http://%s:59986/api/v2/resource/Occupancy_sensor_cluster_01/co2' % edgexip
                payload = co2val
                headers = {'content-type': 'application/json'}
                response = requests.post(url, data=json.dumps(payload), headers=headers, verify=False)

                # Ostaje cekanje od 5 sekundi jer su u csv fajlu ocitavanja retka (svakog minuta)
                time.sleep(5)

        print("The file has been read.")
        while(1):
            time.sleep(100)
