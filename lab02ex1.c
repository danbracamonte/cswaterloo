#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    // Input validation
    if (strlen(argv[1]) >= MAX_PATH_LENGTH) {
        fprintf(stderr, "File path too long.\n");
        return -1;
    }

    // Safe copy of the file path
    char filename[MAX_PATH_LENGTH];
    strncpy(filename, argv[1], MAX_PATH_LENGTH - 1);
    filename[MAX_PATH_LENGTH - 1] = '\0'; 

    // Construct the command with proper input validation
    char command[256]; 
    snprintf(command, sizeof(command), "stat -c %%s %s", filename); 

    // Execute the command 
    FILE *pipe = popen(command, "r");
    if (pipe == NULL) {
        perror("popen");
        return -1;
    }

    char size[100];
    if (fgets(size, sizeof(size), pipe) == NULL) {
        perror("fgets");
        pclose(pipe);
        return -1;
    }

    pclose(pipe);

    printf("The size of the file is %s bytes.\n", size); 
    return 0;
}
