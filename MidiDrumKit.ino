#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int numPads = 4; // Number of piezo pads
const int piezoPins[numPads] = {A0, A1, A2, A3}; // Piezo pins
const int ledPins[numPads] = {2, 3, 4, 5}; // LED pins (optional)
const int midiNotes[numPads] = {36, 38, 42, 46}; // MIDI notes for each pad
const int threshold = 10; // Minimum threshold for a hit
const int debounceTime = 100; // Debounce time in ms
int lastHitTime[numPads] = {0, 0, 0, 0}; // Time since last hit for debounce
const int midiChannel = 1; // MIDI channel

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
  for (int i = 0; i < numPads; i++) {
    pinMode(ledPins[i], OUTPUT); // Set LED pins as output
  }
}

void loop() {
  for (int i = 0; i < numPads; i++) {
    int piezoValue = analogRead(piezoPins[i]);
    
    if (piezoValue > threshold && (millis() - lastHitTime[i] > debounceTime)) {
      int velocity = map(piezoValue, threshold, 1023, 0, 127);
      MIDI.sendNoteOn(midiNotes[i], velocity, midiChannel); 
      digitalWrite(ledPins[i], HIGH); // Turn on LED

      Serial.print("Pad ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(velocity); // Debugging output

      delay(10); 
      MIDI.sendNoteOff(midiNotes[i], 0, midiChannel);
      digitalWrite(ledPins[i], LOW); // Turn off LED
      lastHitTime[i] = millis(); // Reset debounce timer
    }
  }
}

