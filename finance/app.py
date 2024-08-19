import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """ Ensure responses aren't cached """
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # return render_template("debug.html", id=session["user_id"])
    bal_list = db.execute("SELECT cash FROM users where id=?", session["user_id"])
    list = db.execute("SELECT symbol, SUM(qty) AS no, SUM(total) AS amt FROM records WHERE user_id=? GROUP BY symbol;", session["user_id"])
    data = db.execute("SELECT SUM(qty) AS qty, SUM(total) AS total FROM records WHERE user_id=?", session["user_id"])

    bal = 0
    sum = 0
    total = 0
    sum_total = 0

    if bal_list:
        bal = bal_list[0]["cash"]
        total = bal

    if list:
        for ele in list:
            price = lookup(ele["symbol"])["price"]
            sum += price
            ele["price"] = usd(price)
            sum_total += price * ele["no"]
            ele["amt"] = usd(price * ele["no"])

            data[0]["price"] = usd(sum)
            total = bal + sum_total
            # return render_template("debug.html", id=data[0]["total"])

        if data[0]["total"]:
            data[0]["total"] = usd(sum_total)

    return render_template("index.html", bal=usd(bal), list=list, data=data, total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        sym = request.form.get("symbol").upper()
        qty = int(request.form.get("qty"))
        id = session["user_id"]
        list = lookup(sym)

        if not sym or not qty or not list:
            return apology("Please enter valid Symbol and/or Quantity")
        if qty < 1:
            return apology("Please enter valid Quantity")

        price = list["price"]
        bal = db.execute("SELECT cash FROM users WHERE id=?", id)

        if price * qty > bal[0]["cash"]:
            return apology("Not enough balance")

        bal[0]["cash"] -= price * qty

        db.execute("UPDATE users SET cash=? WHERE id=?", bal[0]["cash"], id)
        db.execute("INSERT INTO records (user_id, symbol, qty, total) VALUES (?,?,?,?)", id, sym, qty, price * qty)

        flash("Purchase successful!")
        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash("Logged In!")
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        list = lookup(request.form.get("symbol"))
        if not list:
            return apology("No such Stock Symbol found")
        list["price"] = usd(list["price"])
        return render_template("quoted.html", list=list)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    session.clear()

    if request.method == "POST":
        username = request.form.get("username")
        pwd = request.form.get("pwd")
        cpwd = request.form.get("cpwd")
        if not username or not pwd or not cpwd:
            return apology("Must enter Username and/or Password", 403)
        if pwd != cpwd:
            return apology("Passwords must be same")
        hash = generate_password_hash(pwd)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            session["user_id"] = db.execute("SELECT id FROM users WHERE hash=?", hash)[0]["id"]
            flash("Registered!")
            return redirect("/")
        except (ValueError):
            return apology("Username already exists")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        stock = request.form.get("stock")
        qty = int(request.form.get("qty"))

        if not stock or not qty:
            return apology("Please provide Stock and/or Quantity")
        if qty < 1:
            return apology("Please provide valid Quantity")

        qty_real = db.execute("SELECT sum(qty) AS n FROM records WHERE user_id=? AND symbol=?", session["user_id"], stock)[0]["n"]
        if qty > qty_real:
            return apology("Not enough shares")

        bal = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]
        price = lookup(stock)["price"]
        bal += price * qty
        db.execute("UPDATE users SET cash=? WHERE id=?", bal, session["user_id"])

        list = db.execute("SELECT symbol, qty, id FROM records WHERE user_id=? AND symbol=?", session["user_id"], stock)
        for i in range(len(list)):
            if qty < list[i]["qty"]:
                list[i]["qty"] -= qty
                total = list[i]["qty"] * price
                db.execute("UPDATE records SET qty=?, total=? WHERE id=?", list[i]["qty"], total, list[i]["id"])
                break
            elif qty == list[i]["qty"]:
                db.execute("DELETE FROM records WHERE id=?", list[i]["id"])
                break
            else:
                qty -= list[i]["qty"]
                db.execute("DELETE FROM records WHERE id=?", list[i]["id"])

        flash("Sale Successful!")
        return redirect("/")

    list = db.execute("SELECT symbol FROM records WHERE user_id=? GROUP BY symbol", session["user_id"])
    return render_template("sell.html", list=list)
