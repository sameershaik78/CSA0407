#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    char write_buf[] = "Hello, UNIX system calls!\n";
    char read_buf[100];
    ssize_t bytes_written, bytes_read;

    // 1. Open/Create a file for writing (with permissions 0644)
    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 2. Write data to the file
    bytes_written = write(fd, write_buf, strlen(write_buf));
    if (bytes_written < 0) {
        perror("write");
        close(fd);
        return 1;
    }
    close(fd);

    // 3. Open the file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 4. Read the data from the file
    bytes_read = read(fd, read_buf, sizeof(read_buf) - 1);
    if (bytes_read < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    // Null-terminate the read data and print it
    read_buf[bytes_read] = '\0';
    printf("Read from file: %s", read_buf);

    // 5. Close the file
    close(fd);

    return 0;
}
