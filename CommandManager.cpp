#include "CommandManager.h"


/**
 * Initializes an empty queue of commands
 */
CommandManager::CommandManager(){
  commandCount = 0;
  commandList = NULL;
  defaultCallback = NULL;
  currentCommand = NULL;
}



/**
 * Adds a "command" and a handler function to the list of available commands.
 */
void CommandManager::addCommand(const char *command, void (*function)()) {
  #ifdef SERIALCOMMAND_DEBUG
    Serial.print("Adding command [");
    Serial.print(commandCount);
    Serial.print("]: ");
    Serial.println(command);
  #endif

  commandList = (CommandCallback *) realloc(commandList, (commandCount + 1) * sizeof(CommandCallback));
  strncpy(commandList[commandCount].command, command, COMMAND_LENGHT);
  commandList[commandCount].function = function;
  commandCount++;
}

/**
 * Tries to find the function corresponding to the give command.
 * If it's found it will be run, elsewhere the default method is called.
 */
void CommandManager::runCommand(const char *command){
  currentCommand = command;
  
  #ifdef SERIALCOMMAND_DEBUG
    Serial.print("Running command: ");
    Serial.println(currentCommand);
  #endif
  
  int index = findCommand();
  if(index!=-1){
    (*commandList[index].function)();
  } else if(defaultCallback != NULL){
    (*defaultCallback)(command);
  }
}

/**
 * Search the current list of commands for the given one.
 * Returns the id of the command or -1 if not found
 */
int CommandManager::findCommand(){
  #ifdef SERIALCOMMAND_DEBUG
    Serial.print("Finding command: ");
    Serial.println(currentCommand);
  #endif
  
  for (int i = 0; i < commandCount; i++) {
    #ifdef SERIALCOMMAND_DEBUG
      Serial.print("Comparing [");
      Serial.print(currentCommand);
      Serial.print("] to [");
      Serial.print(commandList[i].command);
      Serial.println("]");
    #endif
    if(strncmp(currentCommand, commandList[i].command, COMMAND_LENGHT) == 0){
      #ifdef SERIALCOMMAND_DEBUG
        Serial.print("Command [");
        Serial.print(currentCommand);
        Serial.print("] found: ");
        Serial.println(i);
      #endif
      return i;
    }
  }
  #ifdef SERIALCOMMAND_DEBUG
    Serial.print("Command [");
    Serial.print(currentCommand);
    Serial.println("] NOT found.");
  #endif
  return -1;
}

/**
 * Set the default fall-back which is called when no other methods are found
 */
void CommandManager::setDefaultCallback( void (*function)(const char *) ){
  defaultCallback = function;
}
