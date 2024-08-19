-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Analyzing the database
.schema

-- checking for crime reports on that day, on that street
SELECT description
FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street = 'Humphrey Street';
-- theft happened at 10.15
-- at some bakery
-- three witnesses interviewed

-- checking for interviews of 3 poeple on that day mentioning bakery
SELECT name, transcript
FROM interviews
WHERE year = 2023
AND month = 7
AND day = 28
AND transcript LIKE '%bakery%';
-- ten minutes within theft, thief exited the bakery parking lot in a car
-- bakeery name is Emma's bakery
-- earlier in the morning, thief was withdrawing money from ATM on Leggett Street
-- theif called and talked to someone for less than a min
-- theif planned to take earliest flight the next day out of Fiftyville

-- checking for bakery parking lot footage for car plate number
CREATE VIEW suspects AS
SELECT *
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25
    AND activity = 'exit'
);
SELECT *
FROM suspects;
-- received 8 suspects

-- checking ATM transaction of above suspects on that day on Leggett Street
CREATE VIEW suspects1 AS
SELECT *
FROM suspects
WHERE name IN (
    SELECT name
    FROM people
    WHERE id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE year = 2023
            AND month = 7
            AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'
        )
    )
    AND license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2023
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 15 AND 25
        AND activity = 'exit'
    )
);
SELECT *
FROM suspects1;
-- 4 suspects remain

-- checking for flight tickets of the next day from Fiftyville of above suspects
SELECT *
FROM airports
WHERE id IN (
    SELECT destination_airport_id
    FROM flights
    WHERE year = 2023
    AND month = 7
    AND day = 29
    AND id IN (
        SELECT flight_id
        FROM passengers
        WHERE passport_number IN (
            SELECT passport_number
            FROM suspects1
        )
    )
    ORDER BY hour ASC
);
-- earliest flight the next day was to New York City

-- querying the name of suspect that took flight to NY the next day
SELECT name
FROM suspects1
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN (
        SELECT id
        FROM flights
        WHERE year = 2023
        AND month = 7
        AND day = 29
        AND origin_airport_id = (
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
        AND destination_airport_id = (
            SELECT id
            FROM airports
            WHERE city = 'New York City'
        )
        ORDER BY hour ASC
    )
);
-- first person to take the flight to NY was Luca

-- checking for call logs of above person on that day to find his accomplice
CREATE VIEW accomplice AS
SELECT *
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE caller = (
        SELECT phone_number
        FROM people
        WHERE name = 'Luca'
    )
    AND year = 2023
    AND month = 7
    AND day = 28
);
SELECT * from accomplice;
-- no accomplices found
-- meaning that theif is not Luca

-- checking for call logs of Bruce on that day to find his accomplice
DROP VIEW accomplice;
CREATE VIEW accomplice AS
SELECT *
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE caller = (
        SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
    AND year = 2023
    AND month = 7
    AND day = 28
);
SELECT * from accomplice;

-- checking for the accomplice that talked less than a min with Bruce on that day
SELECT name
FROM accomplice
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2023
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller IN (
        SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
);
-- the accomplice was Robin
