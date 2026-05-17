curl -X POST https://api2.arduino.cc/iot/v1/clients/token ^
-H "Content-Type: application/x-www-form-urlencoded" ^
-d "grant_type=client_credentials" ^
-d "client_id=SEU_CLIENT_ID" ^
-d "client_secret=SEU_CLIENT_SECRET" ^
-d "audience=https://api2.arduino.cc/iot"
