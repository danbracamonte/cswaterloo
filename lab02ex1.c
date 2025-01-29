#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

// This program simulates generating an HTML page reflecting user input
int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command-line argument
    if (argc != 2) { 
        fprintf(stderr, "Please provide an input argument.\n");
        return -1;
    }

    // Simulate an HTML response reflecting user input
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head><title>XSS Example</title></head>\n");
    printf("<body>\n");

    // Reflect user input directly in the HTML response (introducing XSS vulnerability)
    printf("<h1>Welcome, %s</h1>\n", argv[1]);

    printf("</body>\n");
    printf("</html>\n");

    return 0;
}
