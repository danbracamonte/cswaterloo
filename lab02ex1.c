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

    // Use the buffer in a subsequent function call 
    // This increases the likelihood of CodeQL detecting the buffer overflow
    char command[50];
    snprintf(command, sizeof(command), "ls -l %s", buffer); 

    // This function call is potentially vulnerable 
    // due to the use of the potentially corrupted buffer
    FILE *fp = fopen(buffer, "r"); 
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }
    fclose(fp);

    struct stat file_stat;
    if (stat(argv[1], &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        fprintf(stderr, "Invalid file. Please provide a valid file path.\n");
        return -1;
    }

    printf("The size of the file is %ld bytes.\n", file_stat.st_size);
    return 0;
}
