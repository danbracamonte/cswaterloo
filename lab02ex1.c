#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    // Construct the command without strict input sanitization
    char cmd[BUFSIZE];
    snprintf(cmd, BUFSIZE, "wc -c < %s", argv[1]); // Directly interpolating user input

    // Execute the command
    if (system(cmd) == -1) {
        perror("Error executing command");
        return -1;
    }

    return 0;
}

    printf("The size of the file is %ld bytes.\n", file_size);
    return 0;
}
