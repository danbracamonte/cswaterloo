#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

void process_data(const char* filename) {
    // Allocate memory for the file contents 
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* file_contents = (char*)malloc(file_size + 1); // Allocate memory without size check
    if (file_contents == NULL) {
        perror("malloc");
        fclose(file);
        exit(1);
    }

    size_t bytes_read = fread(file_contents, 1, file_size, file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Error reading file\n");
        fclose(file);
        free(file_contents);
        exit(1);
    }

    file_contents[file_size] = '\0'; // Null-terminate the string

    fclose(file);

    // Process the file contents (vulnerability here)
    int index = 0;
    while (file_contents[index] != '\0') {
        // Attempt to access memory beyond the allocated buffer
        if (file_contents[index] == 'a') {
            file_contents[index + file_size] = 'A'; // Out-of-bounds write 
        }
        index++;
    }

    free(file_contents); 
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    process_data(argv[1]);

    return 0;
}
