#include <Arduino.h>
#include <iodefs.h>
#include <WiFi.h>
#include <MQTT.h>
#include <secrets.h>
#include <utils.h>

const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;
const char mqtt_address[] = SECRET_SERVICE;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect()
{
    Serial.print("checking wifi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.print("\nconnecting...");
    while (!client.connect("arduino", "public", "public"))
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("\nconnected!");

    client.subscribe("hello");
}

void messageReceived(String &topic, String &payload)
{
    Serial.println(topic + ": " + payload);
    // PSEUDOCODE
    // if topic == "/a":
    //      set_motor(M1, payload)
    // if topic == "/b":
    //      set_motor(M2, payload)
}

int i = 0;
int up = true;

const int red_leds[3] = {R1, R2, R3};
const int yel_leds[3] = {G1, G2, G3};

String bfr = "";
int n = 0;
int pin = M1;

void setup()
{
    // Initialize serial and wait for port to open:
    Serial.begin(9600);

    // Motors
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);

    for (int i = 0; i < 3; i++)
    {
        pinMode(yel_leds[i], OUTPUT);
        pinMode(red_leds[i], OUTPUT);
    }

    WiFi.begin(ssid, pass);
    client.begin(mqtt_address, net);
    client.onMessage(messageReceived);

    Serial.print("BOOT COMPLETE");
}

void loop()
{
    // Simple serial test interface:
    //
    while (Serial.available())
    {
        client.loop();
        if (!client.connected())
        {
            connect();
        }

        char c = Serial.read();
        bfr += c;
        if (c == 'a')
        {
            pin = M1;
            bfr = "";
        }
        if (c == 'b')
        {
            pin = M2;
            bfr = "";
        }
        if (c == '\r')
        { // Command recevied and ready.
            int v = bfr.toInt();
            v = v > 0xFF ? 0xFF : v;
            set_motor(pin, v);
            bfr = ""; // Clear the string ready for the next command.
        }
    }
}
