import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    front = {"symbols":[], "names":[], "shares":[], "prices":[], "totals1":[], "totals2":[]}

    username = db.execute("SELECT username FROM users WHERE id = :id", id = session['user_id'])
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session['user_id'])

    rows = db.execute("SELECT symbol, SUM(shares) FROM history WHERE username = :hi GROUP BY symbol ORDER BY symbol ASC", hi=username[0]['username'])

    for i in range(len(rows)):
        check = db.execute("SELECT SUM(shares) FROM history WHERE username = :hi AND symbol = :symbol", hi=username[0]['username'], symbol=rows[i]['symbol'])
        if check[0]['SUM(shares)'] > 0:
            front['symbols'].append(rows[i]['symbol'])
            front['shares'].append(rows[i]['SUM(shares)'])
            look = lookup(rows[i]['symbol'])
            front['names'].append(look['name'])
            front['prices'].append(usd(look['price']))
            front['totals1'].append(usd(look['price'] * rows[i]['SUM(shares)']))
            front['totals2'].append(look['price'] * rows[i]['SUM(shares)'])

    return render_template("index.html", symbols=front['symbols'], shares=front['shares'], names=front['names'], prices=front['prices'], cash=usd(cash[0]['cash']), totals=front['totals1'], total=usd(sum(front['totals2']) + cash[0]['cash']), length=len(front['symbols']))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        action = 'Buy'
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        time = datetime.datetime.now()

        if not symbol:
            return apology("Missing Symbol.", 400)
        if not shares:
            return apology("Missing Shares.", 400)
        if lookup(symbol) == None:
            return apology("Invalid Symbol.", 400)
        if int(shares) <= 0:
            return apology("No Shares Bought.", 400)

        symb_dict = lookup(symbol)
        price = symb_dict['price']

        row = db.execute("SELECT * FROM users WHERE id = :id", id = session['user_id'])
        username = row[0]['username']
        cash = row[0]['cash']

        if cash < (price * int(shares)):
            return apology(f"You're Short ${(price * int(shares)) - cash}!", 400)

        db.execute("INSERT INTO history (username, action, symbol, shares, price, time) VALUES (:username, :action, :symbol, :shares, :price, :time)", username = username, action = action, symbol = symbol, shares = shares, price = price, time = time)

        db.execute("UPDATE users SET cash = :cash WHERE username = :username", cash = (cash - (price * int(shares))), username = username)

        flash(f"Added {shares} shares of {symbol}!")

        return redirect("/")

@app.route("/history")
@login_required
def history():
    hist_dict = {"symbol":[], "shares":[], "price":[], "time":[]}

    username = db.execute("SELECT username FROM users WHERE id = :id", id = session['user_id'])
    row = db.execute("SELECT symbol, shares, price, time FROM history WHERE username = :username", username = username[0]['username'])
    length = len(row)

    for i in range(length):
        hist_dict['symbol'].append(row[i]["symbol"])
        hist_dict['shares'].append(row[i]["shares"])
        hist_dict['price'].append(usd(row[i]["price"]))
        hist_dict['time'].append(row[i]['time'])
    return render_template("history.html", hist_dict = hist_dict, length = len(hist_dict['symbol']))


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        flash(f"Welcome back {rows[0]['username']}!")

        # Redirect user to home page
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
    if request.method == 'GET':
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Missing Symbol.", 400)

        symb_dict = lookup(symbol)
        if symb_dict == None:
            return apology("Invalid Symbol.", 400)

        name = symb_dict['name']
        symbol_1 = symb_dict['symbol']
        price = symb_dict['price']
        return render_template("quoted.html", name=name, symbol=symbol_1, price=price)

@app.route("/register", methods=["GET", "POST"])
def register():
    session.clear()

    if request.method == 'GET':
        return render_template("register.html")
    else:
        reg_username = request.form.get("username")
        reg_password = request.form.get("password")
        reg_password_again = request.form.get("password_again")

        if not reg_username:
            return apology("Must Include a Username!", 403)

        if not reg_password:
            return apology("Must Include a Password!", 403)

        if not reg_password_again:
            return apology("Must Include a Password Confirmation!", 418)

        if reg_password != reg_password_again:
            return apology("Passwords Don't Match.", 418)

        rows = db.execute("SELECT * FROM users WHERE username = :username", username=reg_username)
        if len(rows) == 1:
            return apology("Username Already Exists.", 403)

        reg_user = db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)", username=reg_username, password=generate_password_hash(reg_password, method='pbkdf2:sha256', salt_length=8))

        session["user_id"] = reg_user
        flash(f"You have Registered as {reg_username}!")
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        symbols = []

        username = db.execute("SELECT username FROM users WHERE id = :id", id = session['user_id'])
        row = db.execute("SELECT symbol FROM history WHERE username = :hi GROUP BY symbol ORDER BY symbol ASC", hi = username[0]["username"])
        for i in range(len(row)):
            symbols.append(row[i]['symbol'])

        return render_template("sell.html", symbols=symbols, length=len(symbols))
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        time = datetime.datetime.now()
        username = db.execute("SELECT username FROM users WHERE id = :id", id = session['user_id'])
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session['user_id'])
        shares_input = -1 * int(shares)

        share_symbol = db.execute("SELECT SUM(shares) FROM history WHERE username = :hi AND symbol = :symbol", hi = username[0]["username"], symbol=symbol)

        if not symbol:
            return apology("Missing Symbol.", 400)
        if not shares or int(shares) <= 0 or int(shares) > share_symbol[0]['SUM(shares)']:
            return apology("Invalid Shares.", 400)
        if share_symbol[0]['SUM(shares)'] == 0:
            return apology("Stock Doesn't Exist in Portfolio.", 400)

        look = lookup(symbol)
        price = look['price']

        db.execute("UPDATE users SET cash = :cash WHERE username = :username", cash = (cash[0]['cash'] + (price * int(shares))), username = username[0]["username"])
        db.execute("INSERT INTO history (username, action, symbol, shares, price, time) VALUES (:username, :action, :symbol, :shares, :price, :time)", username = username[0]['username'], action = "Sell", symbol = symbol, shares = shares_input, price = price, time = time)

        flash(f"Sold {shares} shares of {symbol}!")
        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
