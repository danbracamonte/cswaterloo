#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return 1;
    }

    // Uncontrolled Data in Path Expression
    char* path = argv[1]; 

    // Create a buffer with insufficient size
    char buffer[10]; 

    // Copy the file path to the buffer without size check
    strcpy(buffer, path); 

    // Use the potentially corrupted buffer in a system call
    char command[100];
    snprintf(command, sizeof(command), "ls -l %s", buffer); 

    // Execute the command without proper error handling
    system(command); 

    return 0;
}
