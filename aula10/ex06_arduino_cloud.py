import time
import requests
from gpiozero import LED, Button

CLIENT_ID = "SEU_CLIENT_ID"
CLIENT_SECRET = "SEU_CLIENT_SECRET"
THING_ID = "SEU_THING_ID"
LED_VARIABLE_ID = "SEU_LED_VARIABLE_ID"
BUTTON_VARIABLE_ID = "SEU_BUTTON_VARIABLE_ID"

led = LED(18)
button = Button(17)

def obter_token():
    url = "https://api2.arduino.cc/iot/v1/clients/token"

    payload = {
        "grant_type": "client_credentials",
        "client_id": CLIENT_ID,
        "client_secret": CLIENT_SECRET,
        "audience": "https://api2.arduino.cc/iot"
    }

    response = requests.post(url, data=payload)
    return response.json()["access_token"]

def atualizar_variavel(token, variable_id, valor):
    url = f"https://api2.arduino.cc/iot/v2/things/{THING_ID}/properties/{variable_id}/publish"

    headers = {
        "Authorization": f"Bearer {token}",
        "Content-Type": "application/json"
    }

    payload = {"value": valor}

    requests.put(url, json=payload, headers=headers)

def ler_variavel(token, variable_id):
    url = f"https://api2.arduino.cc/iot/v2/things/{THING_ID}/properties/{variable_id}"

    headers = {
        "Authorization": f"Bearer {token}"
    }

    response = requests.get(url, headers=headers)

    return response.json()["last_value"]

token = obter_token()

while True:
    estado_botao = button.is_pressed

    atualizar_variavel(token, BUTTON_VARIABLE_ID, estado_botao)

    estado_led = ler_variavel(token, LED_VARIABLE_ID)

    if estado_led:
        led.on()
    else:
        led.off()

    time.sleep(2)
