#ifndef generaloperations
#define generaloperations

void showLines() { // Displays the total number of lines in a specified file.
    char fileName[4096];
    printf("Enter the name of the file you wish to access: ");
    fgets(fileName, sizeof(fileName), stdin);
    removeEndCharacter(fileName);

    if (doesFileExist(fileName)){ // Checks if file exists.
        FILE *fp = fopen(("%s", fileName), "r"); // Opens the file in "r" mode so it can be read.
        char fileData[4096];

        int lineCount = 0;
        while (fgets(fileData, sizeof(fileData), fp)) {
            lineCount++; // Everytime a line is read, lineCount is incremented.
        }
        printf("Number of lines in \'%s\': %d\n", fileName, lineCount); // Displays number of lines in file.
        addChangeLog("Displayed number of lines in file: ", fileName); // Submits change log message.

    } else {
        printf("Error: This file does not exist. \n");
    }
}

void showChangeLog() { // Prints out the change log.
    FILE *fp = fopen("changelog", "r"); // Opens the change log file in "r" mode so we can access the contents.
    char changeLogData[4096];

    int lineCount = 0;

    while (fgets(changeLogData, sizeof(changeLogData), fp)) {
        lineCount++;
        printf("#%d: %s", lineCount, changeLogData); // Displays the contents of the change log in a list i.e. '#1.... #2....'
    }
    if (lineCount == 0) {
        printf("Change-Log is empty. \n"); // If the change log is empty, a message indicating such will be displayed.
    }
}

#endif