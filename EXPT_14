#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void copy() {
    const char *sourcefile = "C:/Users/itssk/OneDrive/Desktop/sasi.txt";
    const char *destination_file = "C:/Users/itssk/OneDrive/Desktop/sk.txt";

    int source_fd = open(sourcefile, O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        return;
    }

    int dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(source_fd);
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Write error");
            close(source_fd);
            close(dest_fd);
            return;
        }
    }

    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
}

void create() {
    FILE *fp = fopen("C:/Users/itssk/OneDrive/Desktop/sasi.txt", "w");
    
    if (fp == NULL) {
        printf("Error creating file\n");
        return;
    }

    printf("File created successfully\n");
    fclose(fp);
}

void delete_file() {
    if (remove("C:/Users/itssk/OneDrive/Desktop/sasi.txt") == 0) {
        printf("Deleted successfully\n");
    } else {
        printf("Error deleting file\n");
    }
}

int main() {
    int n;

    printf("1. Create \t2. Copy \t3. Delete\nEnter your choice: ");
    scanf("%d", &n);

    switch (n) {
        case 1:
            create();
            break;
        case 2:
            copy();
            break;
        case 3:
            delete_file();
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}