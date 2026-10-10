#include <Keypad.h>           //keypad Library


const byte ROWS = 4;         // defining all variables
const byte COLS = 4;
const int buzzer = 10;
const int greenLED = 11;
const int redLED = 12;


char keys[ROWS][COLS] = {      //Keypad outlook
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};


byte rowPins[ROWS] = {9, 8, 7, 6}; // R1, R2, R3, R4
byte colPins[COLS] = {5, 4, 3, 2}; // C1, C2, C3, C4


String password = "1234";     
String enteredPassword = "";


Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);  

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter password:");
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.print("*");                // hiding input
    enteredPassword += customKey;     
  }

  
  if (enteredPassword.length() == 4) {   // Checking for 4 characters
    delay(500);
    Serial.print("\nEntered: ");
    Serial.println(enteredPassword);

    if (enteredPassword == password) {
      Serial.println("Unlocked");
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);
      noTone(buzzer);
    } else {
      Serial.println("Access Denied! Please enter the correct password");
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);
      tone(buzzer, 1000, 800);              //For 800ms
    }
        
    delay(1500);
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    enteredPassword = "";                   //input reset
    Serial.println("Enter password:");
  }
}

