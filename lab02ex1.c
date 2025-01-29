#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    // Create a buffer with insufficient size
    char buffer[10]; 

    // Copy the file path to the buffer without size check
    strcpy(buffer, argv[1]); 

    // Create a pointer to the buffer 
    char* ptr = buffer; 

    // Use the pointer to access memory beyond the buffer bounds
    // This will likely trigger a use-after-free or out-of-bounds access 
    // if the input string exceeds the buffer size
    while (*ptr != '\0') {
        *ptr = toupper(*ptr); 
        ptr++; 
    }

    struct stat file_stat;
    if (stat(argv[1], &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        fprintf(stderr, "Invalid file. Please provide a valid file path.\n");
        return -1;
    }

    printf("The size of the file is %ld bytes.\n", file_stat.st_size);
    return 0;
}
