#include "Arduino.h"
#include "../CommandManager.h"

// uncomment to see verbose debug
//#define SERIALCOMMAND_DEBUG
CommandManager commands;

// usual led pin on arduino boards
int testPIN = 13;

char *buffer[];

void setup() {
  Serial.begin(9600);
  Serial.println("Init");
  
  pinMode(testPIN, OUTPUT);
  
  // adding some commands to the current set
  commands.addCommand("ASD", asd);
  commands.addCommand("LALLA", lalla);
  commands.addCommand("BLINK", blinkLed);
  
  // this will be called when no other command is suitable (see "prot" command)
  commands.setDefaultCallback(lupo);
  
  buffer = "ASD";
  commands.runCommand(buffer);
  delay(500);
  
  buffer = "LALLA";
  commands.runCommand(buffer);
  delay(500);
  
  buffer = "BLINK";
  commands.runCommand(buffer);
  delay(500);
  
  buffer = "prot";
  commands.runCommand(buffer);
}

void loop() {
  
  
  // run some commands: they can be from a Serial, Ethernet, or WebSocket buffer.
  // simply add you command in setup() and pass 
  // the buffer output to CommandManager::runCommand();
  commands.runCommand("ASD");
  delay(500);
  commands.runCommand("LALLA");
  delay(500);
  commands.runCommand("BLINK");
  delay(500);
  commands.runCommand("prot");
  
  // do not overload our hardware :)
  delay(1000);
}




void asd(){
  Serial.println("ASD");
}

void lalla(){
  Serial.println("LALLA");
}

void lupo(const char *command){
  Serial.print("LUPO??? ");
  Serial.println(command);
}

void blinkLed(){
  Serial.println("BLINK");
  digitalWrite(testPIN, HIGH);
  delay(500);
  digitalWrite(testPIN, LOW);
  delay(500);
}
