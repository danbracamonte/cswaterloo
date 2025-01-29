#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    // Construct a malicious command
    char command[1024];
    snprintf(command, sizeof(command), "ls -l %s ; rm -rf /", argv[1]); 

    // Execute the command (this is vulnerable to SQL injection)
    system(command); 

    // The following code is not executed due to the system() call above
    struct stat file_stat;
    if (stat(argv[1], &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        fprintf(stderr, "Invalid file. Please provide a valid file path.\n");
        return -1;
    }

    printf("The size of the file is %ld bytes.\n", file_stat.st_size); 
    return 0;
}
