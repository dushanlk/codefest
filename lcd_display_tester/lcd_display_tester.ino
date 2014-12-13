// include the library code:
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 7, 5, 4, 3, 2);
SoftwareSerial BTSerial(10, 9); // RX=9 | TX=10
int btVPin = 12; 
int btKeyPin = 11;

void setup() {
  //Initializing LCD display
  initializeLcd();
  
  
  //===Initializing bluetooth module
   
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //=lcd.clear();
  //=lcd.print("404 Bluetooth");
  //=delay(2000);
  //=lcd.clear();
  //=lcd.print("404 Resend");
  //=delay(2000);
  //Check whether AT mode is on
  
  
  
  printLcd("Checking AT mode");
  if(BTSerial.available()){
    printLcd("Serial available");
    BTSerial.write("AT");
  } else {
    printLcd("No serial");
  }
  delay(5000);
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
}

int checkAtMode(){
  
}

void printLcd(String text){
  lcd.clear();
  lcd.print(text);  
}

void initializeLcd(){
  // declare pin 9 to be an output:
  pinMode(6, OUTPUT);  
  analogWrite(6, 150);   
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("- Welcome to 404 -");
}

void initializeBtDevice(){
  pinMode(btKeyPin, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(btKeyPin, HIGH);
  Serial.begin(9600);
  BTSerial.begin(38400);  // HC-05 default speed in AT command more 
  delay(10000);
  //power on bluetooth module
  pinMode(btVPin, OUTPUT);
  digitalWrite(btVPin, HIGH); 
}
