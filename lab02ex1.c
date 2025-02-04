#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    FILE* fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return -1;
    }

    fseek(fp, 0, SEEK_END); // Move file pointer to the end
    long file_size = ftell(fp); 
    fclose(fp);
    
    if (file_size < 0) {
        fprintf(stderr, "Error getting file size.\n");
        return -1;
    }

     printf("The size of the file is %ld bytes.\n", sizeof(FILE));
    return 0;
}
