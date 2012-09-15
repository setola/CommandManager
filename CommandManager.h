#ifndef CommandManager_h
#define CommandManager_h

// The maximum number of unique commands
#define MAXCALLBACKS 50    

// The maximum length of a command (defaults to 64)
#define COMMAND_LENGHT 64

// define this variable to enable verbose debug
//#define SERIALCOMMAND_DEBUG

#include <string.h>
#include "Arduino.h"

#endif;

class CommandManager{
  public:
    CommandManager();
    
    // Adds a single command to the list
    void addCommand(const char *command, void(*function)());
    
    // Tryes to run the given command
    void runCommand(const char *command);
    
    // This is called when no suitable command is found
    void setDefaultCallback( void (*function)(const char *) );
    
    // reset the command list
    void reset();

  protected:
    // structure of a single callback: command and related function to be called
    struct CommandCallback {
      char command[COMMAND_LENGHT + 1];
      void (*function)();
    };
    
    // The list of command this object can understand
    CommandCallback *commandList;
    
    // Pointer to the default handler function
    void (*defaultCallback)(const char *);
    
    // search for the current command in the list
    int findCommand();
    
    // number of command stored in the list
    int commandCount;
    
    // stores the current command
    const char *currentCommand;

};
