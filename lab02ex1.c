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

    // Directly use the user-provided input in a system call
    char command[50];
    snprintf(command, sizeof(command), "cat %s", argv[1]); 
    system(command); 

    // Attempt to use the buffer (likely to be overwritten)
    strcpy(buffer, argv[1]); 

    struct stat file_stat;
    if (stat(buffer, &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        fprintf(stderr, "Invalid file. Please provide a valid file path.\n");
        return -1;
    }

    printf("The size of the file is %ld bytes.\n", file_stat.st_size);
    return 0;
}
