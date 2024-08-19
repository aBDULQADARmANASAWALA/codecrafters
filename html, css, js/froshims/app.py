from flask import Flask, render_template, redirect, request

app = Flask(__name__)

SPORTS = ["Basketball", "Cricket", "Football"]
REGISTRANTS = {}


@app.route("/")
def index():
    # NOTE: "sports" here is the variable name that is
    # present in the index.html file inside of a for loop of Jinja
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    # NOTE: "name" and "sport" here are the values of name key
    # that I have set in the index.html file
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message="Please enter a name")

    sports = request.form.getlist("sport")
    if not sports:
        return render_template("error.html", message="Please select a sport")
    for sport in sports:
        if sport not in SPORTS:
            return render_template("error.html", message="Please select a valid sport")

    REGISTRANTS[name] = sport

    return str(REGISTRANTS)

