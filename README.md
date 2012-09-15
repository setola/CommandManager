CommandManager
==============

Arduino library to manage associate a function to a particular command

Installation
------------

move to your arduino libraries folder
for ex. 

````
C:\Program Files\arduino-1.0.1\libraries
````

and clone the repository with:

````
git clone git://github.com/setola/CommandManager.git
````


Usage
-----

````javascript


CommandManager commands;
commands.addCommand("TEST", test_function);

void loop() {
  // some logic to find the right buffer
  buffer = "TEST";

  // then ask the library if it's possible
  // to run the method attached to the buffer content
  commands.runCommand(buffer);
}

// declare the callback function
void test_function(){
  Serial.println("TEST");
}

````



