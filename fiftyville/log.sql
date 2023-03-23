-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema
select * from crime_scene_reports where day = 28 and month = 7;
select * from interviews where day = 28 and month = 7 and transcript like '%bakery%';
select license_plate from bakery_security_logs where month = 7 and day = 28 and hour = 10 and activity = 'exit';
select person_id from bank_accounts where account_number in (select account_number from atm_transactions where month = 7 and day = 28 and atm_location = 'Leggett Street' and transaction_type = 'withdraw');
select caller from phone_calls where month = 7 and day = 28 and duration <= 60;
select id from flights where origin_airport_id = 8 and month = 7;
select passport_number from passengers where flight_id in (select id from flights where origin_airport_id = 8 and month = 7)
select passport_number from passengers where flight_id in (select id from flights where origin_airport_id = 8 and month = 7 and day = 28 order by hour, minute);
select * from people where license_plate in (select license_plate from bakery_security_logs where month = 7 and day = 28 and activity = 'exit' and hour = 10 and minute > 15 and minute < 25) and id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where month = 7 and day = 28 and atm_location = 'Leggett Street' and transaction_type = 'withdraw')) and phone_number in (select caller from phone_calls where month = 7 and day = 28 and duration <= 60) and passport_number in (select passport_number from passengers where flight_id in (select id from flights where origin_airport_id = 8 and month = 7 and day = 29 order by hour, minute limit 1));
