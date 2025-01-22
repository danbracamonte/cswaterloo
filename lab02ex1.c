#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    struct stat file_stat;
    // Validate the input and check if it is a regular file
    if (stat(argv[1], &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        fprintf(stderr, "Invalid file. Please provide a valid file path.\n");
        return -1;
    }

    // Print the file size
    printf("The size of the file is %ld bytes.\n", file_stat.st_size);
    return 0;
}
