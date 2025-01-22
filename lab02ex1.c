#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFSIZE 256

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    // Open the file for reading
    FILE* file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);

    if (file_size < 0) {
        fprintf(stderr, "Error reading file size.\n");
        return -1;
    }

    printf("The size of the file is %ld bytes.\n", file_size);
    return 0;
}
