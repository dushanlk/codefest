// include the library code:
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 7, 5, 4, 3, 2);
SoftwareSerial BTSerial(10, 9); // RX=9 | TX=10
int btVPin = 12; 
int btKeyPin = 11;
int connectStatus = 0;

char inData[50]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character

void setup() {
  //Initializing LCD display
  initializeLcd();
    
  //Initializing bluetooth module
  initializeBtDevice();    
}

void loop() {

  searchAndLinkDevice();
  
//    // Keep reading from HC-05 and send to Arduino Serial Monitor
//  if (BTSerial.available()){
//    printLcd("Reading BT..");
//    Serial.write(BTSerial.read());
//    //delay(2000);
//  }
//    
//
//  // Keep reading from Arduino Serial Monitor and send to HC-05
//  if (Serial.available()){
//    printLcd("Reading REQ..");
//    BTSerial.print("AT\r\n");
//    delay(2000);
//  }

}

void searchAndLinkDevice(){
  if(connectStatus==0){
    linkDevice();    
  } else {    
    if (Serial.available()){
      BTSerial.print("AT+STATE?\r\n"); 
      Serial.write(BTSerial.read());   
    }
    
    printLcd("Connected..");   
    delay(2000);    
  }
}

void linkDevice(){
  printLcd("Connecting..");
    BTSerial.print("AT+CMODE=0\r\n");
    delay(2000);
    BTSerial.print("AT+ROLE=1\r\n");
    delay(2000);
    BTSerial.print("AT+INIT\r\n");
    delay(2000);
    BTSerial.print("AT+INQ\r\n");
    delay(2000);
    BTSerial.print("AT+BIND=80b6,86,b66dd2\r\n");
    delay(2000);
    BTSerial.print("AT+PAIR=80b6,86,b66dd2,300\r\n");
    delay(2000);
    BTSerial.print("AT+LINK=80b6,86,b66dd2\r\n");  
    delay(2000);
    connectStatus = 1;
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
  lcd.print(" Welcome to 404 ");
}

void initializeBtDevice(){
  printLcd("   Starting..   ");
  pinMode(btKeyPin, OUTPUT);  // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
  digitalWrite(btKeyPin, HIGH);
  Serial.begin(9600);
  BTSerial.begin(38400);  // HC-05 default speed in AT command more 
  delay(5000);
  //power on bluetooth module
  pinMode(btVPin, OUTPUT);
  digitalWrite(btVPin, HIGH);  
  delay(10);
  printLcd("    Started!    ");  
}
