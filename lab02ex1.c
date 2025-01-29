#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

// Function to validate if a user exists in the "database" (users.txt)
int validateUser(const char* username) {
    FILE* file = fopen("users.txt", "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open user database.\n");
        return 0; // User validation fails if the file cannot be read
    }

    char line[BUFSIZE];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        if (strcmp(line, username) == 0) {
            fclose(file);
            return 1; // User found
        }
    }

    fclose(file);
    return 0; // User not found
}

int main(int argc, char** argv) {
    if (argc != 3) { 
        fprintf(stderr, "Usage: %s <username> <file>\n", argv[0]);
        return -1;
    }

    // Validate user before executing any command
    if (!validateUser(argv[1])) {
        fprintf(stderr, "Error: User validation failed.\n");
        return -1;
    }

    char cmd[BUFSIZE] = "wc -c < ";
    strcat(cmd, argv[2]);
    system(cmd);

    return 0;
}
