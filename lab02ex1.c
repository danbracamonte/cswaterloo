#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define BUFSIZE 256

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) { 
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }

    // Validate that the input is a valid file path
    struct stat file_stat;
    if (stat(argv[1], &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        fprintf(stderr, "Invalid file. Please provide a valid file path.\n");
        return -1;
    }

    // Use a safer approach for constructing the command
    char cmd[BUFSIZE];
    snprintf(cmd, BUFSIZE, "wc -c < '%s'", argv[1]); // Use single quotes to prevent command injection

    // Execute the command
    system(cmd);
    return 0;
}
