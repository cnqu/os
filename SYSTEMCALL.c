#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int file_descriptor;
    char data_to_write[] = "Hello, System Calls!";
    char buffer[100];
    ssize_t bytes_read;

    // Open the file for writing
    file_descriptor = open("example.txt", O_WRONLY | O_CREAT, 0644);
    if (file_descriptor == -1)
    {
        perror("open");
        exit(1);
    }

    // Write data to the file
    ssize_t bytes_written = write(file_descriptor, data_to_write, sizeof(data_to_write) - 1);
    if (bytes_written == -1)
    {
        perror("write");
        exit(1);
    }
    printf("Wrote %zd bytes to the file.\n", bytes_written);

    // Close the file after writing
    if (close(file_descriptor) == -1)
    {
        perror("close");
        exit(1);
    }

    // Re-open the file for reading
    file_descriptor = open("example.txt", O_RDONLY);
    if (file_descriptor == -1)
    {
        perror("open");
        exit(1);
    }

    // Read data from the file
    bytes_read = read(file_descriptor, buffer, sizeof(buffer));
    if (bytes_read == -1)
    {
        perror("read");
        exit(1);
    }
    buffer[bytes_read] = '\0';  // Null terminate the string

    // Print the read data
    printf("Read from file: %s\n", buffer);

    // Close the file after reading
    if (close(file_descriptor) == -1)
    {
        perror("close");
        exit(1);
    }

    // Add unlink system call to delete the file
    if (unlink("example.txt") == -1)
    {
        perror("unlink");
        exit(1);
    }
    printf("File 'example.txt' has been deleted.\n");

    return 0;
}
