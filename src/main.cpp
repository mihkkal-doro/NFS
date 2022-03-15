#include <Arduino.h>
#include <iodefs.h>

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
}

void loop()
{
    // Simple serial test interface:
    // 
    while (Serial.available())
    {
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
            Serial.print(pin);
            Serial.print(" >> ");
            Serial.println(v, HEX);
            analogWrite(pin, v);
            bfr = ""; // Clear the string ready for the next command.
        }
    }
}
