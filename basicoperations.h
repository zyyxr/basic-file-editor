#ifndef basicoperations
#define basicoperations

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool doesFileExist(char fileName[]) { // Checks if a file exists by using the filename parameter to open said file.
    FILE *fp;
    fp = fopen(("%s", fileName), "r");
    if (fp == NULL) { // When a file that does not exist is opened, the fp pointer will be NULL, so the file does not exist.
        return false;
    } else {
        fclose(fp);
        return true;
    }  
}

 void removeEndCharacter(char fileName[]) { // Since we use fgets() to get data, it will include an extra character (null terminator or \n) which will prevent it from matching our files etc...
    int len = strlen(fileName);
    fileName[len-1] = fileName[len]; // The data at the position of the extra character is changed to a null value as fileName[len] has no value within it.
    }

int showLinesFile(char fileName[]) { // Returns the number of lines in the file we access using the filename we provide in the parameter.
    FILE *fp;
    fp = fopen(("%s", fileName), "r");
    char fileData[4096];

    int lineCount = 0;
    while (fgets(fileData, sizeof(fileData), fp)) { // Everytime a line is successfully read, the lineCount variable is incremented so we get an indication of the line count.
        lineCount++;
    }
    return lineCount;
}

void addChangeLog(char operation[], char fileName[]) { // After every operation, this method appends a line of content (explaining the operation done on a file and consequently, the line count of said file) into the change log file.
    int lines = showLinesFile(fileName); // Gets the total line count of the specified file.
    char fileLines[4096];
    sprintf(fileLines, "%d",lines); // Converts the integer value of lines into a string in the character array fileLines.
    FILE *fp = fopen("changelog", "a"); 
        fputs(operation,fp);
        fputs(fileName,fp);
        fputs(" - line count of file: ", fp);
        fputs(fileLines,fp); // Appends the line in a specific format to the changelog file.
    fputs("\n", fp);
    fclose(fp);
}

void createSpecificFile(char fileName[]) { // Creates a file with a specific name.
    FILE *fp;
    fp = fopen(("%s.txt", fileName), "w");
    fclose(fp);
} 

void deleteSpecificFile(char fileName[]) { // Deletes a file with a specific name.
    remove(("%s.txt",fileName));
}

int checkLineInput(char fileName[]) { // When using line operations, this ensures the line number input from the user is not that is out of bounds eg. more than the number of lines in the file or less than 1.
    int lineNumber;
    int linesInFile = showLinesFile(fileName);
    char lineNumberChar[4096];
        if (fgets(lineNumberChar, sizeof(lineNumberChar), stdin)) { // Asks the user for input on what line number they want to operate on - this input is a string!
            lineNumber = atoi(lineNumberChar); // This converts the line number (which is a string) into an integer so we can compare it to the linesInFile.
            if (lineNumber > linesInFile) {
                printf("Error: You tried to access a line that doesn't exist in this file. \n");
                return 0; // Returning 0 is indication of an error.
            } else if (lineNumber < 1) {
                printf("Error: The minimum line number you can access is 1. \n");
                return 0;
            } else {
                return lineNumber;
            }
        } else {
            printf("Invalid input provided. \n");
            return 0;
        }

}

void printHelpMessage() { // Displays message of all commands and explanation of each command.
    printf("------------- ALL COMMANDS -------------\n");
    printf("'create file' - creates a new file with a specified name.\n'copy file' - copies the contents of a specified file into a new file with a new name.\n'delete file' - deletes a specfified file.\n'show file' - displays the contents of a specified file.\n'append line' - creates a new line of content at the end of a specified file.\n'delete line' - deletes a particular line of a specified file.\n'insert line' - inserts a custom line of content into a specified file at a particular line.\n'show line' - displays the contents of a particular line of a specified file.\n'changelog' - displays the sequence of operations performed on all files, and their consequent number of lines, during the execution of this program.\n'show file lines' - displays the total number of lines in a specified file.\n'search file' - searches a specified file for a particular word/phrase/character and displays the lines at which they appear.\n'edit line' - edits a particular line of a specified file.\n'help' - prints out a help message.\n");
    printf("----------------------------------------\n");

}

void copyFileToFile(char fileOne[], char fileTwo[]) {
    char fileOneData[4069];
    char fileTwoData[4069];
    FILE* fp = fopen(("%s", fileOne), "r");
    FILE* fp2 = fopen(("%s", fileTwo), "w");
    while (fgets(fileOneData, sizeof(fileOneData), fp)) {
        fputs(fileOneData, fp2);
    }
    fclose(fp);
    fclose(fp2);

}


#endif 