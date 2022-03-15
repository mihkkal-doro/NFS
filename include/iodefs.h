/**
 * iodefs.h - input/output pin map
 * 
 **/
#pragma once

// Motor control wires, 
// Connected to cascaded BJT's as high-side switches.
// Current gain is about 100 x. Maybe
#define M1 0 // D0
#define M2 1 // D1

// Current sense wires 
// Really have no idea what the actual voltages will be here
// Please don't connect these before we figure it out. 
#define S1 A0
#define S2 A1

// Blinkenlights
#define R1 2 // D2
#define R2 3 // D3
#define R3 4 // D4
#define G1 5 // D5
#define G2 6 // D6
#define G3 7 // D7
