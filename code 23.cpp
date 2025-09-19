#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind;
    char searchPath[MAX_PATH];

    // If directory path is provided as argument, append \* to it
    if (argc > 1) {
        // Make sure path doesn't end with '\' already
        size_t len = strlen(argv[1]);
        if (argv[1][len - 1] == '\\' || argv[1][len - 1] == '/') {
            snprintf(searchPath, MAX_PATH, "%s*", argv[1]);
        } else {
            snprintf(searchPath, MAX_PATH, "%s\\*", argv[1]);
        }
    } else {
        // Use current directory
        snprintf(searchPath, MAX_PATH, "*");
    }

    // Start finding files
    hFind = FindFirstFileA(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error: Could not find files in directory '%s'\n", 
               argc > 1 ? argv[1] : ".");
        return 1;
    }

    do {
        // Skip "." and ".."
        if (strcmp(findFileData.cFileName, ".") == 0 ||
            strcmp(findFileData.cFileName, "..") == 0) {
            continue;
        }

        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            printf("<DIR>\t%s\n", findFileData.cFileName);
        } else {
            printf("      \t%s\n", findFileData.cFileName);
        }
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);
    return 0;
}
