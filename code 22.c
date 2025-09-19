#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hFile;
    DWORD written;
    char text[] = "Appending some text.\r\n";

    // 1. Create or open file
    hFile = CreateFileA(
        "testfile.txt",                // file name
        GENERIC_READ | GENERIC_WRITE, // desired access
        0,                            // share mode
        NULL,                         // security attributes
        OPEN_ALWAYS,                  // open or create
        FILE_ATTRIBUTE_NORMAL,        // flags and attributes
        NULL                          // template file
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Could not open file, error %lu\n", GetLastError());
        return 1;
    }
    printf("File opened successfully.\n");

    // 2. Move file pointer to end
    SetFilePointer(hFile, 0, NULL, FILE_END);

    // 3. Write to file
    if (!WriteFile(hFile, text, (DWORD)strlen(text), &written, NULL)) {
        printf("Write failed, error %lu\n", GetLastError());
        CloseHandle(hFile);
        return 1;
    }
    printf("Wrote %lu bytes to file.\n", written);

    // 4. Get file size
    DWORD fileSize = GetFileSize(hFile, NULL);
    if (fileSize == INVALID_FILE_SIZE) {
        printf("GetFileSize failed, error %lu\n", GetLastError());
    } else {
        printf("File size: %lu bytes\n", fileSize);
    }

    CloseHandle(hFile);

    // 5. List files in current directory
    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA("*.*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("FindFirstFile failed, error %lu\n", GetLastError());
        return 1;
    }

    printf("\nFiles in current directory:\n");
    do {
        printf("  %s\n", findFileData.cFileName);
    } while (FindNextFileA(hFind, &findFileData) != 0);

    FindClose(hFind);

    return 0;
}
