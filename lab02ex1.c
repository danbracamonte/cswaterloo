#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*stat_func_t)(const char *path, struct stat *buf);

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return 1;
    }

    // Uncontrolled Data in Path Expression
    char* path = argv[1]; 

    // Load the stat function dynamically
    void* handle = dlopen("libc.so.6", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return 1;
    }

    stat_func_t my_stat = (stat_func_t)dlsym(handle, "stat");
    if (!my_stat) {
        fprintf(stderr, "Error finding symbol: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // Buffer Overflow Vulnerability
    char buffer[10];
    strcpy(buffer, path); 

    // Use the potentially corrupted buffer in the dynamic function call
    struct stat file_stat;
    if (my_stat(buffer, &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        fprintf(stderr, "Invalid file. Please provide a valid file path.\n");
        dlclose(handle);
        return -1;
    }

    // Use the potentially corrupted buffer in a system call
    char command[100];
    snprintf(command, sizeof(command), "ls -l %s", buffer); 
    system(command); 

    dlclose(handle);

    printf("The size of the file is %ld bytes.\n", file_stat.st_size);
    return 0;
}
