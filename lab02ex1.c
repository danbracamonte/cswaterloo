#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void process_data(const char* filename) {
    // No input sanitization 
    char command[PATH_MAX]; 
    snprintf(command, sizeof(command), "cat %s", filename); 

    // Potential for infinite loop 
    int counter = 0;
    while (1) { 
        system(command); 
        counter++;
        if (counter > 10) { 
            break; 
        }
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    process_data(argv[1]);

    return 0;
}
