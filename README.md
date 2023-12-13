# DIY MIDI Drum Kit Using Arduino and Raspberry Pi

This project guide describes how to build a MIDI drum kit using piezo sensors, an Arduino Nano, and a Raspberry Pi Zero with FluidSynth and an Audio DAC SHIM for enhanced audio output.

*Note this is a work in progress and has not been fully tested. Feel free to contribute!*

## Hardware Requirements

* Raspberry Pi Zero with Raspberry Pi OS installed
* Audio DAC SHIM (Line-Out) from Pimoroni
* Arduino Nano
* Piezo sensors (one for each drum trigger you want to create)
* 1MΩ resistors (one for each piezo sensor)
* Breadboard and jumper wires
* USB cable for connecting the Arduino Nano to the Raspberry Pi Zero
* Soldering iron and solder

## Software Requirements

* Arduino IDE for programming the Arduino Nano
* FluidSynth on Raspberry Pi Zero for MIDI sound synthesis
* ttymidi for creating a MIDI bridge between the Arduino and Raspberry Pi
* SoundFont for FluidSynth (drum sounds)

## Setup Instructions

### Step 1: Setting up the Audio DAC SHIM

1. Attach the Audio DAC SHIM to Your Raspberry Pi Zero:

  * Follow the [Pimoroni guide](https://shop.pimoroni.com/products/audio-dac-shim-line-out) to attach the Audio DAC SHIM to your Raspberry Pi Zero.
  * Solder the SHIM onto the Pi Zero's GPIO pins for a secure and stable connection.

2. Configure the Audio Output:

  * On your Raspberry Pi, ensure the audio output is set to use the DAC SHIM:
    ```
    sudo raspi-config
    ```
  * Navigate to System Options > Audio, and select the option that corresponds to the DAC SHIM.

### Step 2: Arduino Nano Circuit Assembly

1. Soldering Connections:

  * Solder wires to the analog pins (A0, A1, A2, A3, etc.) on the Arduino Nano for each piezo sensor.
  * Solder wires to the GND pin on the Nano for the ground connections of the piezo sensors.

2. Connecting Piezo Sensors:

  * Connect each piezo sensor to its corresponding analog pin on the Arduino Nano.
  * Connect a 1MΩ resistor in parallel with each piezo sensor between the sensor and the Nano.

3. Optional LED Feedback:

  * If you want visual feedback, solder LEDs to digital pins (e.g., D2, D3, D4, D5) and ground.

### Step 3: Program the Arduino Nano

1. Upload MIDI Sketch:

  * Use the Arduino IDE to upload the provided MIDIDrumKit.ino sketch to the Arduino Nano.
  * This sketch is configured to read piezo hits and send MIDI messages.

### Step 4: Raspberry Pi Zero Setup

1. Install ttymidi:

  * Install ttymidi to create a virtual MIDI device:

    ```
    git clone https://github.com/cjbarnes18/ttymidi.git
    cd ttymidi
    make
    sudo make install
    ```

2. Run ttymidi:

  * Use ttymidi to bridge the Arduino Nano and the Raspberry Pi:

    ```
    ttymidi -s /dev/ttyUSB0 -v
    ```

3. Configure FluidSynth:

  * Start FluidSynth with your desired SoundFont:
    
    ```
    fluidsynth -a alsa -m alsa_seq -g 1.0 /path/to/soundfont.sf2
    ````

### Step 5: Connect Everything Together

1. Connect Arduino to Raspberry Pi:

  * Plug the Arduino Nano into the Raspberry Pi Zero using a USB cable.
  * Ensure ttymidi is running to facilitate MIDI communication.

2. Link MIDI Device to FluidSynth:

  * In a new terminal, connect ttymidi to FluidSynth using aconnect.

### Step 6: Testing and Calibration

1.  Test Each Trigger:
    
  * Tap each piezo sensor to verify that corresponding MIDI notes are triggered in FluidSynth.
  * Adjust the sensitivity in the Arduino sketch as necessary.

### Troubleshooting

* Check all soldered connections for consistency and quality.
* Verify that the Raspberry Pi recognizes the Audio DAC SHIM and Arduino Nano.
* If MIDI signals are not detected, double-check the ttymidi and FluidSynth connections.

### Resources

Here are some related projects and helpful resources:

* [Ardiuno Piezo Midi Controller project](https://diyelectromusic.wordpress.com/2020/07/19/arduino-piezo-midi-controller/)





