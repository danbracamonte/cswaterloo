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

    // **Uncontrolled Data in Path Expression**
    char* path = argv[1]; // Directly using user input without validation

    // **Uncontrolled Dynamic Method Call**
    if (my_stat(path, NULL) == 0) { 
        fprintf(stderr, "File exists.\n"); 
    } else { 
        fprintf(stderr, "File does not exist.\n"); 
    }

    dlclose(handle);
    return 0;
}
