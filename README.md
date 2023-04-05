# Arduino-KeyPad-Lock-ATM
This project simulates the creation of an ATM using the LCD shield and the keypad lock. I used keypad to enter defined PIN code and see a list of options: choose language, then view balance, update balance, cancel. Moreover, I used extra buttons to simulate extra functionality.
The application will be implemented in the Arduino programming language, along with a series of libraries, Keypad.h and LiquidCrystal_I2C.h.

## Requirements
Arduino IDE

## Usage

### Context
Using an ATM is a sufficiently complex process to make a correct and complete simulation in a software application and a little hardware. Therefore, this project will cover only a part of the operations that a customer could perform through an ATM. These being:
- Language selection
- Viewing the account amount
- Adding money to the account
- Withdrawal of an amount from the account
- Cancellation, basically leaving the current account
- Withdrawal of an amount of money using the exchange rate
It will also be possible to clear user input using a "Clear" key. Moreover, the "D" key will be intended to replace the actual "Enter" key in the ATM.

### Objective
One of the objectives of the application will be to simulate, as realistically as possible, the functionality of an ATM in everyday life using different hardware components such as:
- Arduino compatible board
- LCD with I2C
- 4 Button Module
- Keypad 4x4
- A series of wires for connecting the components

## Visuals 
### Hardware components
<div allign="center">
    <img title="Arduino compatible board" src="https://user-images.githubusercontent.com/93877610/230030072-df6cd79c-8c7c-4687-9a05-a0520d9a370d.jpg" width="250" height="150">
    <img title="LCD with I2C" src="https://user-images.githubusercontent.com/93877610/230030519-5a84a0ab-864d-4f58-92df-02e3a2837e8f.jpg" width="250" height="150">
    <img title="KeyPad" src="https://user-images.githubusercontent.com/93877610/230030189-179d412d-db4c-4cf1-8d88-cdf19b81a5f1.jpg" width="250" height="150">
    <img title="4 Button Module" src="https://user-images.githubusercontent.com/93877610/230030688-a391a53f-5064-455b-8268-0c796f54000d.jpg" width="200" height="100">
</div>

<img allign="center" title="Circuit" src="https://user-images.githubusercontent.com/93877610/230032381-d422b525-e6ad-40da-b85e-0d82165a0f84.jpg" width="350" height="250">

### Functionality
<div allign="center">
    <img src="https://user-images.githubusercontent.com/93877610/230032869-adb098fa-0749-4638-97b5-8acb2fca1de6.jpg" width="240" height="130">
    <img src="https://user-images.githubusercontent.com/93877610/230032874-67f6c423-7e39-439f-9b56-6deea4b6478e.jpg" width="240" height="130">
    <img src="https://user-images.githubusercontent.com/93877610/230032875-66efa0f0-d666-4773-bb14-70634c71fefb.jpg" width="240" height="130">
    <img src="https://user-images.githubusercontent.com/93877610/230032877-6f494d90-5f65-4fd4-8007-226d020a1ba7.jpg" width="240" height="130">
    <img src="https://user-images.githubusercontent.com/93877610/230032880-3cda9d8c-7a9a-4b9e-a686-5ff5e1aeecc3.jpg" width="240" height="130">
    <img src="https://user-images.githubusercontent.com/93877610/230032883-3c6020d9-adef-4cda-80be-b3df31c9275f.jpg" width="240" height="130">
    <img src="https://user-images.githubusercontent.com/93877610/230032885-4ec08f4f-987c-48d8-a494-016170b4809f.jpg" width="240" height="130">
    <img src="https://user-images.githubusercontent.com/93877610/230032889-3bcaa066-85a3-48ed-8b9b-4d27e49e216a.jpg" width="240" height="130">
</div>
