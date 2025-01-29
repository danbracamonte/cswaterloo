#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define DB_FILE "file_info_db.txt"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file path>\n", argv[0]);
        return -1;
    }

    struct stat file_stat;
    if (stat(argv[1], &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        fprintf(stderr, "Invalid file. Please provide a valid file path.\n");
        return -1;
    }

    // Save the file information to a simulated database (a text file)
    FILE* db = fopen(DB_FILE, "a");
    if (!db) {
        perror("Error opening database file");
        return -1;
    }
    fprintf(db, "%s,%ld\n", argv[1], file_stat.st_size);
    fclose(db);

    // Read back and display the database content
    db = fopen(DB_FILE, "r");
    if (!db) {
        perror("Error reading database file");
        return -1;
    }

    char line[512];
    printf("<html>\n");
    printf("<body>\n");
    printf("<h1>File Information</h1>\n");
    while (fgets(line, sizeof(line), db)) {
        char file_path[256];
        long file_size;
        if (sscanf(line, "%255[^,],%ld", file_path, &file_size) == 2) {
            // Display the file info without sanitization
            printf("<p>The size of the file '%s' is %ld bytes.</p>\n", file_path, file_size);
        }
    }
    printf("</body>\n");
    printf("</html>\n");

    fclose(db);
    return 0;
}
