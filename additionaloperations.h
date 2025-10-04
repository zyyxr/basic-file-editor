#ifndef additionaloperations
#define additionaloperations

int searchFile() { // Searches a file for specific content and displays on what lines they occur on.
    char fileName[4096];
    printf("What file would you like to search: "); // Asks for the file the user wants to search.
    fgets(fileName, sizeof(fileName), stdin);
    removeEndCharacter(fileName);

    if (doesFileExist(fileName)) { // Checks if said file exists.
        char word[4096];
        printf("What character/word/phrase would you like to search the file for: "); // Asks the user what they want to search for, and stores it in the word array.
        if (!(fgets(word, sizeof(word), stdin))) { // Checks if the input is invalid.
            printf("Invalid input. \n");
            return 0;
        }
        removeEndCharacter(word);
        char fileData[4096];
        int lineNumber = 0;
        bool wordAppeared = false; // lineNumber allows us to keep track of what lines our content may appear on/ wordAppeared allows us to keep track of whether the content was found.
        char wordLine[4096];
        createSpecificFile("file search data"); // Creates a file which will store the line numbers of which our content appears on.
        FILE *fp = fopen("file search data", "a");
        FILE *fp2 = fopen(("%s",fileName),"r"); // Opens the file we're searching for, in "r" mode so we can read the content.
        while (fgets(fileData, sizeof(fileData), fp2)) {
            lineNumber++;
            char *str = strstr(fileData, word); // As every line of the file we're searching for is read, we check if the content appears anywhere within the line - if it does, str will not be equal to NULL.
            if (str != NULL) {
                wordAppeared = true; // Sets wordAppeared to true so we know the content appeared in the file.
                sprintf(wordLine, "%d", lineNumber);
                fputs(wordLine, fp);
                fputs(", ", fp); // Converts the lineNumber into a string so we can write it to the 'file search data' file.
            }
        }
        fclose(fp);
        fclose(fp2);
        if (!wordAppeared) { // If the content did not appear, it will display this message.
            printf("There are no instances of the intended content within the file. \n");
        } else {
            char fileSearchData[4096];
            fp2 = fopen("file search data", "r"); // If the content did appear in the file, the 'file search data' file will be open in "r" mode so we can read the line numbers from it.
            printf("Content is present at line(s): ");
            while (fgets(fileSearchData, sizeof(fileSearchData), fp2)) {
                printf("%s", fileSearchData); // Prints out the line numbers over which the content appeared.
            }
            printf("\n");
        }
        fclose(fp2);
        deleteSpecificFile("file search data");
        addChangeLog("Searched for content in file: ", fileName); // Submits change log message.
    } else {
        printf("Error: This file does not exist. \n");
    }
    return 0;
}

int editLine() { // Directly edits a particular line of a specified file.
    char fileName[4096];
    printf("What file would you like to access: "); // Asks for filename.
    fgets(fileName, sizeof(fileName), stdin);
    removeEndCharacter(fileName);

    if (doesFileExist(fileName)) { // Checks if file exists.
        char lineNumberChar[4096];
        printf("What line would you like to edit: ");
        
        int lineNumber = checkLineInput(fileName); // Validates the lineNumber input.
        if (lineNumber == 0) {
            return 0;
        }

        char line[4096];
        printf("Enter the content you wish to edit the line to: "); // Asks what we would like to edit the line to and stores it in the line array.
        fgets(line, sizeof(line), stdin);

        char fileData[4096];
        FILE* fp = fopen(("%s", fileName),"r"); // Opens our file in "r" mode so we can read its contents and copy it to a spare file.
        
        int lineCount = 0;
        createSpecificFile("random file");
        FILE *fp2 = fopen("random file", "w"); // Creates and opens a new file which we can copy the data from our initial data to, and update it.
        while (fgets(fileData, sizeof(fileData), fp)) {
            lineCount++; // Increments the lineCount variable as each line is read.
            if (lineCount == lineNumber) { // If we've currently read the line we want to edit, we write the line containing the edited content, rather than the original content.
                fputs(line, fp2);
            } else {
                fputs(fileData, fp2); // For every line that isn't the one we want, we write it into the updated file as usual.
            }
        }
        fclose(fp);
        fclose(fp2);
        fp = fopen(("%s", fileName), "w");
        fp2 = fopen("random file", "r"); // Opens the original file in "w" mode to clear it and the updated file in "r" mode so we can read and copy its contents to the original file.
        char randomFileData[4096];
        while (fgets(randomFileData, sizeof(randomFileData), fp2)) {
            fputs(randomFileData, fp); // As every line from the updated file is read, we copy it over to the original file.
        }
        fclose(fp);
        fclose(fp2);
        deleteSpecificFile("random file"); // Deletes the updated file.
        printf("Line was successfully edited. \n");
        char changeLogMessage[4069];
        sprintf(changeLogMessage, "Edited line %d in file: ", lineNumber);
        addChangeLog(changeLogMessage, fileName); // Submits change log message.
    } else {
        printf("Error: This file does not exist. \n");
    }
    return 0;
}

#endif