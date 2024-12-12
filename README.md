# Lightweight Authentic Wireless Communications for Micro:Bit IoT Device: Group Project
# IoT Assessment Group 1.6
## Students: Marwan Alkhateeb, Abdulrahman Ali

## OverView

This project uses two Micro:bit v2 devices to send and recieve encrypted commands wirelessly. The system features:
1.	Memory Game: LED-based memory game.
2.	Capacitor Charge Detector: Displays capacitor charge level with LEDs.
3.	Third Command: Template for any future commands.
Features
•	Encryption: Ensures secure communication between devices using a symmetric encryption key (DPK).
•	Wireless Communication: Uses Micro:bit's built-in radio to send and receive commands.

## Setup and Usage
### 1. The Encryption Setup

Securly sending commands involves generating a Device Pairing Key (DPK), which is used for the encryption. Setting Up a shared secret for both the transmitter and the reciever is crucial for generating the DPK:

#### Step 1: Generating the DPK

The DPK is generated using a pre-set shared secret between both devices. 

•	Example DPK: A simple shared secret could be a string like my_shared_secret_key.

•	Encryption: This DPK is used in both the transmitter and receiver to encrypt and decrypt messages.

#### Step 2: Encryption/Decryption

•	Transmitter: Encrypts the command before sending it via radio.

•	Receiver: Decrypts the command upon receiving it and then processes it.

### 2. Sending Commands

The transmitter sends encrypted commands over the radio channel using the radio.send() function. The commands can be:

•	LED Simon Says Game Command (e.g., start or reset the game)

•	Capacitor Charge Detection Command (e.g., start charging and show progress)

•	Custom Command Template: Placeholder for additional functionality.

### 3. Receiving Commands

The receiver listens for incoming commands using radio.onReceived(). Upon receiving a command, it decrypts it using the shared DPK and executes the corresponding action.

## Commands 

### 1. Memory Game

This game uses LEDs (RED, AMBER, YELLOW, GREEN) to display a sequence of lights. The user needs to replicate the sequence using sudo screen. E.g. if the first LED is RED, the user needs to input 'R' in sudo screen. The following sequence would be RED and GREEN, where the user would need to input 'R' and 'G', having the game go one with more complex sequences until the user inputs the wrong sequence, resulting in a "Game Over".

### 2. Capacitor Charge Detector

This command involves having the users input a number from the range of 0-1023 (representing the PWM limit of the Microbit) on sudo screen, which charges the capacitor accordingly, and displaying how full the capacitor is using the 4 LEDs on the breadboard (RED, AMBER, YELLOW, GREEN). E.g. RED being a range below 200 PWM, and GREEN being a range above 750 PWM. 

### 3. Sound Detector

This command involves having the sending Microbit listen to sounds, and counting the amount of sounds in the environment and reflecting it on the LEDs (RED, AMBER, YELLOW, GREEN), with RED being a sounds below 10, and GREEN being sounds above 40 respectively.

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.
