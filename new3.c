#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to execute the command
void executeCommand(char* commandLine, char* envp[]) {
    // Create a child process
    pid_t pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        // Tokenize the command line into command and arguments
        char* command = strtok(commandLine, " ");
        char* arguments[10];  // assuming a maximum of 10 arguments
        int argIndex = 0;

        // Store the arguments
        while (command != NULL) {
            arguments[argIndex] = command;
            argIndex++;
            command = strtok(NULL, " ");
        }
        arguments[argIndex] = NULL;  // add NULL as the last element for execve

        // Check if the command is "exit"
        if (strcmp(arguments[0], "exit") == 0) {
            // Exit the program
            exit(0);
        } else if (strcmp(arguments[0], "/bin/ls") == 0) {
            // Execute "/bin/ls" directly
            execve(arguments[0], arguments, envp);
        } else {
            // Search for the command in the directories specified in the PATH environment variable
            char* path = getenv("PATH");
            char* pathDirs[10];  // assuming a maximum of 10 directories in the PATH
            int dirIndex = 0;

            // Tokenize the PATH directories
            char* dir = strtok(path, ":");
            while (dir != NULL) {
                pathDirs[dirIndex] = dir;
                dirIndex++;
                dir = strtok(NULL, ":");
            }

            // Attempt to execute the command in each directory
            for (int i = 0; i < dirIndex; i++) {
                char commandPath[256];  // assuming a maximum path length of 256
                snprintf(commandPath, sizeof(commandPath), "%s/%s", pathDirs[i], arguments[0]);
		printf("args[0]: %s", commandPath);

                // Execute the command
                execve(commandPath, arguments, envp);
            }
        }

        // If execve returns, it means an error occurred or the command was not found
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        // Wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);
    }
}

int main(int argc, char* argv[], char* envp[]) {
    char* commandLine = NULL;
    size_t commandLineSize = 0;
    ssize_t bytes_read;

    while (1) {
        printf("Enter a command: ");
        bytes_read = getline(&commandLine, &commandLineSize, stdin);

        // Remove the trailing newline character
        if (bytes_read > 0 && commandLine[bytes_read - 1] == '\n') {
            commandLine[bytes_read - 1] = '\0';
        }

        // Check for the exit condition (Ctrl+D)
        if (bytes_read == -1) {
            printf("\nExiting...\n");
            break;
        }

        // Execute the command
        executeCommand(commandLine, envp);
    }

    free(commandLine);
    return 0;
}

