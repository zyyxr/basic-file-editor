#ifndef lineoperations
#define lineoperations

void appendLine() { // Adds a line to the very end of a specified file.
    char fileName[4096];
    printf("Enter the name of the file you wish to append a line to: ");
    fgets(fileName, sizeof(fileName), stdin);
    removeEndCharacter(fileName);

    if (doesFileExist(fileName)){ // Checks if file exists.
        FILE *fp;
        fp = fopen(("%s.txt", fileName), "a"); // Opens file in "a" mode so we can append to it.
        char string[4096];
        printf("Content you wish to append: ");
        fgets(string, sizeof(string), stdin); // The content of the line we wish to append is done by getting user input here.
        fputs(string, fp); // Puts the line into the specified file.
        printf("Line was successfully appended to the file. \n");
        fclose(fp);
        addChangeLog("Appended a line to file: ", fileName); // Submits change log message.
    } else {
        printf("Error: File doesn't exist. \n");
    }
}

 int showLine() { // Displays the content of a particular line in a specified file.
    char fileName[4096];
    printf("Enter the name of the file you wish to access: ");
    fgets(fileName, sizeof(fileName), stdin);
    removeEndCharacter(fileName);

    if (doesFileExist(fileName)){ 
        printf("What line would you like to read: ");
        int lineNumber = checkLineInput(fileName); // Checks if the line number the user inputted is possible to access.
        if (lineNumber == 0) { // If the user inputted an invalid number, lineNumber will be 0 so to abort the operation we check if this is the case, otherwise we continue.
            return 0;
        }
        FILE *fp;
        fp = fopen(("%s.txt", fileName), "r"); // Opens our file so we can read it.
        char line[4096];
        int lineCount = 0;
        while (fgets(line, sizeof(line), fp)) { 
            lineCount++; // As every line is read, the lineCount is incremented to match the line number that is being read.
            if (lineCount == lineNumber) { // Once the lineCount is equal to the line we want to display, we display the line.
                printf("%s", line);
            }
        }
        fclose(fp);
        char changeLogMessage[4069];
        sprintf(changeLogMessage, "Displayed line %d in file: ", lineNumber);
        addChangeLog(changeLogMessage, fileName); // Submits a change log message.
    } else {
        printf("File doesn't exist. \n");
    } 
    return 0;
}

 int deleteLine() { // Deletes a particular line of a specified file.
    char fileName[4096];
    printf("Enter the name of the file you wish to access: "); // Gets the filename.
    fgets(fileName, sizeof(fileName), stdin);
    removeEndCharacter(fileName);

    if (doesFileExist(fileName)){ // Checks if the file exists.
        printf("What line would you like to delete: ");
        int lineNumber = checkLineInput(fileName); // Checks if the line number the user inputted is one that can be accessed.
        if (lineNumber == 0) { // If the line number was invalid, we abort the operation here - this approach will be done for all line operations below.
            return 0;
        }

        FILE *fp;
        fp = fopen(("%s", fileName), "r"); // We open our initial data in "r" mode so we can read the contents from it.
        char fileData[4096];

        createSpecificFile("updated file");
        FILE *fp2;
        fp2 = fopen(("updated file"), "w"); // We create an extra file which we will write the data of the initial file to, except for the line we wish to delete.

        int lineCount = 0;
        
        while (fgets(fileData, sizeof(fileData), fp)) {
            lineCount++; // As we read every line from the initial file, we increment the lineCount.
            if (lineCount == lineNumber) { 
                continue; // If we've reached the line we want to delete, we skip this iteration and do not put the line into the new file.
            } else {
                fputs(fileData, fp2); // For every line that isn't our intended line, we put it into our new file.
            }
        }
        fclose(fp);
        fclose(fp2);
        copyFileToFile("updated file", fileName); // Copies the contents of our updated file to our original file which will have been cleared.
        deleteSpecificFile("updated file"); // Deletes the updated file.
        printf("Line was successfully deleted. \n");

        char changeLogMessage[4069];
        sprintf(changeLogMessage, "Deleted line %d in file: ", lineNumber);
        addChangeLog(changeLogMessage, fileName); // Submits change log message.
    } else {
        printf("Error: File doesn't exist. \n");
    }
    return 0;
}

int insertLine() {
    char fileName[4096];
    printf("Enter the name of the file you wish to access: ");
    fgets(fileName, sizeof(fileName), stdin);
    removeEndCharacter(fileName);

    if (doesFileExist(fileName)){ // Checks if file exists.
        int l = showLinesFile(fileName); 
        if (l < 1) { // If we are choosing to insert a line into a file with no lines, it will tell the user to use the 'append line' command as we cannot insert a line here.
            printf("Error: File is empty and has no lines. To add content, use 'append line'.  \n");
            return 0;
        }

        printf("What line would you like to insert this into: ");
        int lineNumber = checkLineInput(fileName); // Validates the lineNumber input from the user.
        if (lineNumber == 0) {
            return 0;
        }
        FILE *fp = fopen(("%s.txt", fileName), "r");
        char fileData[4096];
        char newLine[4096];
        printf("Content of the line you wish to insert: "); // Gets the content of the line we wish to insert via user input.
        fgets(newLine, sizeof(newLine), stdin); // Stores this input into an array which we can use to add the content to the file.

        createSpecificFile("updated file"); // Similarly to the deleteLine() method, we make an updated file which we open in "w" mode so we can write the data we would like the initial file to have, into this one.
        FILE *fp2;
        fp2 = fopen(("updated file"), "w");

        int lineCount = 0;
        while (fgets(fileData, sizeof(fileData), fp)) {
            lineCount++;
            if (lineCount == lineNumber) { // If we reach the line number we want to insert our line into, we insert our new line first and then the content that was initially present on that line, on the next line.
                fputs(newLine, fp2);
                fputs(fileData, fp2);
            } else {
                fputs(fileData, fp2);
            }
        }
        fclose(fp);
        fclose(fp2);
        copyFileToFile("updated file", fileName); // Copies updated file's contents to our original file which will have been cleared.
        deleteSpecificFile("updated file"); // Updated file is deleted.
        printf("Line was successfully inserted into the file. \n");
        char changeLogMessage[4069];
        sprintf(changeLogMessage, "Insert a line of content into line %d in file: ", lineNumber);
        addChangeLog(changeLogMessage, fileName); // Submits change log message.

        } else {
        printf("Error: File doesn't exist. \n");
    }
    return 0;
}

#endif 