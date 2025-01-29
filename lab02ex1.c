#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1024

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char filename[MAX_LENGTH];
    strncpy(filename, argv[1], MAX_LENGTH - 1); // Potential buffer overflow
    filename[MAX_LENGTH - 1] = '\0';

    // Create a buffer with insufficient size
    char buffer[10];

    // Copy filename to the buffer without size check
    strcpy(buffer, filename); 

    // Use the potentially corrupted buffer in a file operation
    FILE* file = fopen(buffer, "r"); 
    if (file == NULL) {
        perror("fopen");
        return 1;
    }
    fclose(file);

    return 0;
}
