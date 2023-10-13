/* Notes
theft time and place: 10:15 at Chamberlin Street courthouse

TEN MINUTES within the theft, the thief drove away from the courthouse parking lot
after leaving the courthouse, made a CALL for LESS than a MINUTE
saying that wanted to take the EARLIEST flight FROM FIFTYVILLE in JULY 29 (next day)

thief WITHDREW money from the ATM in Fifer Street before the theft

/* To take a look at the crime report

Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
Interviews were conducted today with three witnesses who were present
at the time — each of their interview transcripts mentions the courthouse.
*/
SELECT description FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28;

/* To see the transcripts of the interviews

Ruth: Sometime within ten minutes of the theft, I saw the thwas walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

Raymond: As the thief was leaving the courthouse, they called someief get into
a car in the courthouse parking lot and drive away.
If you have security footage from the courthouse parking lot,
you might want to look for cars that left the parking lot in that time frame.

Eugene: I don't know the thief's name, but it was someone I recognized.
Earlier this morning, before I arrived at the courthouse, I one who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/
SELECT transcript, name FROM interviews
WHERE year = 2020 AND month = 7
AND day = 28 AND transcript LIKE '%courthouse%';

/* To see the license plates of the cars that left the place right after the theft

5P2BI95 | exit | 16
94KL13X | exit | 18
6P58WS2 | exit | 18
4328GD8 | exit | 19
G412CB7 | exit | 20
L93JTIZ | exit | 21
322W7JE | exit | 23
0NTHK55 | exit | 23
*/
SELECT id, license_plate, activity, minute FROM courthouse_security_logs
WHERE year = 2020 AND month =7 AND day = 28
AND hour = 10 AND minute >= 15 AND minute <= 25;

/* To see the phone calls made after the crime

caller | receiver | duration
(130) 555-0289 | (996) 555-8899 | 51
(499) 555-9472 | (892) 555-8872 | 36
(367) 555-5533 | (375) 555-8161 | 45
(499) 555-9472 | (717) 555-1342 | 50
(286) 555-6063 | (676) 555-6554 | 43
(770) 555-1861 | (725) 555-3243 | 49
(031) 555-6622 | (910) 555-3251 | 38
(826) 555-1652 | (066) 555-9701 | 55
(338) 555-6650 | (704) 555-2131 | 54
*/
SELECT id, caller, receiver, duration FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28
AND duration < 60;

/* To see the earliest flight of the day after the theft
time: 8h20
flight_id: 36
origin_airport_id: 8
destination_airport_id: 4
*/
SELECT * FROM flights
WHERE year = 2020 AND month = 7 AND day = 29;

/* To see the passengers of the flight

flight_id | passport_number | seat
36 | 7214083635 | 2A
36 | 1695452385 | 3B
36 | 5773159633 | 4A
36 | 1540955065 | 5C
36 | 8294398571 | 6C
36 | 1988161715 | 6D
36 | 9878712108 | 7A
36 | 8496433585 | 7B
*/
SELECT * FROM passengers WHERE flight_id = 36;

/* To see where the thief escaped to:
LONDON
*/
SELECT city FROM airports WHERE id = 4;

-- To get the transactions
SELECT DISTINCT account_number, amount FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28
AND transaction_type = 'withdraw' AND atm_location = "Fifer Street"
ORDER BY (amount);

-- To get the person id of the people that withdrew some money before the theft
SELECT bank_accounts.person_id, bank_accounts.account_number FROM bank_accounts
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_transactions.transaction_type = 'withdraw' AND atm_transactions.atm_location = "Fifer Street";


-- Now filtering the database accordingly to all the informations I got so far mixing all together
SELECT DISTINCT people.name, people.phone_number, people.passport_number,people.license_plate FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number 
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
JOIN flights ON flights.id = passengers.flight_id
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE flights.id = 36 AND courthouse_security_logs.year = 2020
AND courthouse_security_logs.month = 7 AND courthouse_security_logs.day = 28
AND courthouse_security_logs.hour = 10 AND courthouse_security_logs.minute >= 15
AND courthouse_security_logs.minute <= 25
AND phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28
AND phone_calls.duration < 60
AND atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_transactions.transaction_type = 'withdraw' AND atm_transactions.atm_location = "Fifer Street";

/* RESULT:
name | phone_number | passport_number | license_plate
Ernest | (367) 555-5533 | 5773159633 | 94KL13X
*/

-- To see who he was talking to in the phone call
SELECT name FROM people
WHERE phone_number = 
(SELECT receiver FROM phone_calls
WHERE id = 233);



