#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Uncontrolled Data in Path Expression
    char* filename = argv[1]; 

    // Create a buffer with insufficient size
    char buffer[10];

    // Copy the filename to the buffer without size check
    strcpy(buffer, filename); 

    // Use the potentially corrupted buffer in a system call 
    char command[100];
    snprintf(command, sizeof(command), "cat %s", buffer); 

    // Execute the command 
    system(command); 

    return 0;
}
