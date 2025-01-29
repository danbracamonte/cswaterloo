#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

// Function to simulate a web response containing user input
void generateWebResponse(const char* filename) {
    printf("Content-Type: text/html\n\n"); // Simulated HTTP header
    printf("<html><body>\n");
    printf("<h1>File size for: %s</h1>\n", filename); // **Vulnerable Output**
    printf("</body></html>\n");
}

int main(int argc, char** argv) {
    if (argc != 2) { 
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }

    // Simulate web output instead of command execution
    generateWebResponse(argv[1]); // Pass user input directly to the response (VULNERABLE!)

    return 0;
}
