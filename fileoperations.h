#ifndef fileoperations
#define fileoperations

void createFile() { // Creates a file with a specified name.
    char fileName[4096];
    printf("Name of file to be created: ");
    fgets(fileName, sizeof(fileName), stdin); // Asks user what name they want for the file, and stores this into an array.
    removeEndCharacter(fileName);
    if (doesFileExist(fileName)) { // If a file already exists with the same name, a new file will not be created.
        printf("Error: A file already exists with that name - if you want to create a new file with this name, delete the original file. \n");
    } else {
        FILE *fp;
        fp = fopen(("%s.txt", fileName), "w"); // Opening a file (doesn't exist yet) with this name in "w" mode will create a new empty file with that name.
        fclose(fp);
        printf("File ('%s') was created. \n", fileName);
        addChangeLog("Created file: ", fileName); // Adds a message to the change log to show a file was created.
    }
    }

void copyFile() { // Creates a new file with a specified name and copies data from an initial file to the new file.
    char oldFileName[4096];

    printf("Enter the file you want to copy: ");
    fgets(oldFileName, sizeof(oldFileName),stdin); // Gets user input on what file they want to copy from.
    removeEndCharacter(oldFileName); // Removes the last character of our input so that it can match the name of the file, if it exists.
    if (doesFileExist(oldFileName)) { // If this file exists, copy it.
        char oldFileData[4096];

        FILE *fp;
        fp = fopen(("%s.txt", oldFileName),"r"); // Opens our initial file in "r" mode so we can copy the data from it.

        char newFileName[4069];
        printf("What would you like to name the new file: "); // Gets user input on what the name of the new file will be and removes the final character so it can be accessed.
        fgets(newFileName, sizeof(newFileName), stdin);
        removeEndCharacter(newFileName);
        if (doesFileExist(newFileName)) {
            printf("Error: A file already exists with that name - if you want to copy into this file, you will have to delete the file with this name. \n"); // If the user wants to copy into a file with this name, they can delete the file with this name.
        } else {
            FILE *fp2;
            fp2 = fopen(("%s.txt",newFileName),"w"); // This new file doesn't exist yet, so we open a new file with the specified name in "w" mode so we can copy the data TO it.
            while (fgets(oldFileData,sizeof(oldFileData),fp)) { // As every line of the initial file is read, it's copied into the new file.
                fputs(oldFileData,fp2);
            }
            printf("File was successfully copied into ('%s') \n", newFileName);
            fclose(fp);
            fclose(fp2);
            char changeLogMessage[5000];
            sprintf(changeLogMessage, "Copied (%s) into a new file: ", oldFileName);  // Allows us to setup the changeLogMessage which will pass through the operation[] parameter in the addChangeLog() method. 
            addChangeLog(changeLogMessage, newFileName); // Submits a changelog message to show a file was copied - these 3 lines will be present in every operation!
            }
    } else {
        printf("Error: File doesn't exist. \n"); // If file doesn't exist, we print the error message: this is the case for every other operation below.
    }
}

void showFile() { // Displays the contents of a specified file.
    char fileName[4096];
    printf("Name of file you want to display: ");
    fgets(fileName, sizeof(fileName), stdin); // Asks the user for the filename.
    removeEndCharacter(fileName);

    if (doesFileExist(fileName)) {  // Checks if the file exists, and if it does, display the contents.
        printf("\'%s\': \n", fileName);
        char fileData[4096];
        FILE *fp;
        fp = fopen(("%s.txt", fileName),"r");
        while (fgets(fileData, sizeof(fileData), fp)) { // The while loop will continue until every line is read - as every line is read, it is printed out to the terminal. 
        printf("%s", fileData);
        }
        fclose(fp);
        addChangeLog("Displayed file: ", fileName); // Submits a message to the change log.
    } else {
        printf("Error: File doesn't exist. \n");
    }
}

void deleteFile() { // Deletes a specified file.
    char fileName[4096];
    printf("What file do you want to delete: ");
    fgets(fileName, sizeof(fileName), stdin);
    removeEndCharacter(fileName);
    if (doesFileExist(fileName)) { // If file exists, we add the change log message first so we can get the line count of the file: doing this after removal of the file will give a line count of 0.
        addChangeLog("Deleted file: ", fileName);
        remove(("%s.txt",fileName));
        printf("Deleted \'%s\'. \n", fileName);
    } else {
        printf("Error: File doesn't exist. \n");
    }
}


#endif