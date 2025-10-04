#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Essential libraries for our program.

#include "basicoperations.h"
#include "additionaloperations.h"
#include "fileoperations.h"
#include "lineoperations.h"
#include "generaloperations.h" // Ensures we have access to all the file/line/additional operations we need for the program to function.

 void main(int argc, char *argv[]) {

    createSpecificFile("changelog"); // Creates the changelog file which we can append to during the operation of the program.
    printHelpMessage(); // Prints out all the commands to get the user familiar.
    printf("The following message can be accessed by using 'help'. \n");
    
    while (true) { // Ensures a command is prompted from user until 'quit' is inputted.
         char command[4096];
         printf("Command: ");
        fgets(command, sizeof(command), stdin); // Prompts a command from the user.
        removeEndCharacter(command);
        int len = strlen(command);
        int i;
        for (i = 0; i < len; i++ ) {
            command[i] = tolower(command[i]); // These 4 lines turn every character of the input from the user into lowercase, so that the input is not case-sensitive. 
        }
       
        if (strcmp("create file",command) == 0) { // This statements compares 'command' (the user input) to specific strings - if they match, it will return a value of 0 - so if it is 0, the appropriate method is executed.
            createFile();
        } else if (strcmp("copy file",command) == 0) {
            copyFile();
        } else if (strcmp("show file",command) == 0) {
            showFile();
        } else if (strcmp("delete file",command) == 0) {
            deleteFile();
        } else if (strcmp("append line",command) == 0) {
            appendLine();
        } else if (strcmp("show line", command) == 0) {
            showLine();
        } else if (strcmp("delete line", command) == 0) {
            deleteLine();
        } else  if (strcmp("insert line", command) == 0) {
            insertLine();
        } else if (strcmp("show file lines", command) == 0) {
            showLines();
        } else if (strcmp("changelog", command) == 0) {
            showChangeLog(); 
        } else if (strcmp("search file", command) == 0) {
            searchFile(); 
        } else if (strcmp("edit line", command) == 0) {
            editLine(); 
        } else if (strcmp("quit", command) == 0) {
            printf("Exiting program. \n");
            break; // Exits the while loop and eventually terminates the program by breaking from the loop.
        } else if (strcmp("help", command) == 0) {
            printHelpMessage();
        } else { // If the command does not match any of the above strings, it will tell the user they inputted an invalid command.
            printf("Invalid command, try again. \n");
        }
    }
    deleteSpecificFile("changelog"); // Deletes the changelog file.
 }
