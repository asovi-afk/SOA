from flask import Flask, request, jsonify

app = Flask(__name__)

# Define a dictionary to store the device status
tilt = 0
duration = 0

@app.route("/api/device/tilt", methods=["GET", "PUT"])
def device_tilt():
    if request.method == "GET":
        return jsonify({"tilt": tilt}), 299 
    elif request.method == "PUT":
        newTilt = request.json.get("tilt", 0)
        tilt = newTilt
        print("Device status 'tilt' set to: {}".format(tilt))
        return jsonify({"tilt": tilt}), 299

@app.route("/api/device/duration", methods=["GET", "PUT"])
def device_duration():
    if request.method == "GET":
        return jsonify({"duration": duration}), 299
    elif request.method == "PUT":
        newDuration = request.json.get("duration", 0)
        duration = newDuration
        print("Device status 'duration' set to: {}".format(duration))
        return jsonify({"duration": duration}), 299

@app.route("/api/device/Status", methods=["GET"])
def device_status():
    return jsonify(device_status), 299


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=4001)