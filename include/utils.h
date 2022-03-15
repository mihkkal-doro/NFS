#pragma once
#include <Arduino.h>

void set_motor(int M, int v){
    analogWrite(M, v);
    Serial.print(M);
    Serial.print(" >> ");
    Serial.println(v, HEX);
}