#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Uncontrolled Data in Path Expression
    char* filename = argv[1]; 

    // Buffer Overflow Vulnerability
    char buffer[10];
    strcpy(buffer, filename); 

    // Use the potentially corrupted buffer in a system call 
    char command[100];
    snprintf(command, sizeof(command), "cat %s", buffer); 

    // Execute the command without proper error handling
    system(command); 

    return 0;
}
