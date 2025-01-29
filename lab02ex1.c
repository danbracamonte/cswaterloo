#include <iostream>
#include <dlfcn.h>
#include <string>
#include <cstring>
#include <unistd.h>

typedef int (*system_func_t)(const char* command);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // Uncontrolled Data in Path Expression
    const char* filename = argv[1]; 

    // Load the dynamic library
    void* handle = dlopen("libc.so.6", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading library: " << dlerror() << std::endl;
        return 1;
    }

    // Get the address of the system() function
    system_func_t my_system = (system_func_t)dlsym(handle, "system");
    if (!my_system) {
        std::cerr << "Error finding symbol: " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    // Construct the command with uncontrolled data
    std::string command = "cat " + std::string(filename); 

    // Uncontrolled Dynamic Method Call
    my_system(command.c_str()); 

    dlclose(handle);
    return 0;
}
