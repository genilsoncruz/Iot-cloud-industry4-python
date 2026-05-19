const CLIENT_ID = "SEU_CLIENT_ID";
const CLIENT_SECRET = "SEU_CLIENT_SECRET";
const THING_ID = "SEU_THING_ID";
const LED_VARIABLE_ID = "SEU_LED_VARIABLE_ID";

async function obterToken() {
    const response = await fetch(
        "https://api2.arduino.cc/iot/v1/clients/token",
        {
            method: "POST",
            headers: {
                "Content-Type": "application/x-www-form-urlencoded"
            },
            body: new URLSearchParams({
                grant_type: "client_credentials",
                client_id: CLIENT_ID,
                client_secret: CLIENT_SECRET,
                audience: "https://api2.arduino.cc/iot"
            })
        }
    );

    return await response.json();
}

async function ligarLED(valor) {

    const tokenData = await obterToken();
    const token = tokenData.access_token;

    const url =
        `https://api2.arduino.cc/iot/v2/things/${THING_ID}/properties/${LED_VARIABLE_ID}/publish`;

    await fetch(url, {
        method: "PUT",
        headers: {
            "Authorization": `Bearer ${token}`,
            "Content-Type": "application/json"
        },
        body: JSON.stringify({
            value: valor
        })
    });
}

ligarLED(true);
