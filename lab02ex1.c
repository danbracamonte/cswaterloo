#include <stdio.h>
#include <stdlib.h>
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

    // Allocate memory without size check 
    char* file_contents = (char*)malloc(file_size); 
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

    // No null-termination 
    // This can lead to undefined behavior when 
    // the file_contents are processed as a string 
    // (e.g., by functions like strcpy, strlen, etc.)

    fclose(file);

    // Process the file contents (potential for memory corruption)
    for (int i = 0; i < file_size; i++) {
        if (file_contents[i] == 'a') {
            file_contents[i] = 'A'; 
        }
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
