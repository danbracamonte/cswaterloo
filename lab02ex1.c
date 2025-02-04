#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv) {

  // declaring file pointer 
    file_stat* fptr; 
  
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    struct stat file_stat;
    if (stat(argv[1], &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        fprintf(stderr, "Invalid file. Please provide a valid file path.\n");
        return -1;
    }

    // printf("The size of the file is %ld bytes.\n", file_stat.st_size);
    printf("Size of FILE Structure: %d bytes", 
    sizeof(file_stat)); 
    return 0;
}


/*

// C Program to demonstrate the file pointer 
#include <stdio.h> 
  
int main() 
{ 
    // declaring file pointer 
    FILE* fptr; 
  
    // trying to get the size of FILE datatype. 
    printf("Size of FILE Structure: %d bytes", 
           sizeof(FILE)); 
  
    return 0; 
}
*/
