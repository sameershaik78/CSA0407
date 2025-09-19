#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <search_pattern> <filename>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LEN];
    int line_num = 0;
    while (fgets(line, sizeof(line), file)) {
        line_num++;
        if (strstr(line, pattern) != NULL) {
            printf("%d: %s", line_num, line);
        }
    }

    fclose(file);
    return 0;
}
