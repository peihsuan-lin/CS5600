#include "file_utils.h"


char *prepare_write(const char *local_file_path, const char *remote_file_path, const char *permission) {
    // Open the local file
    int fd = open(local_file_path, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open local file");
        return NULL;
    }
    // Get the size of the file and allocate memory for it
    struct stat st;
    if (fstat(fd, &st) < 0) {
        perror("Failed to get file size");
        close(fd);
        return NULL;
    }
    char *fileBuffer = (char *) malloc(st.st_size + 1);
    // Read the file content into buffer
    if (read(fd, fileBuffer, st.st_size) < 0) {
        perror("Failed to read file");
        close(fd);
        free(fileBuffer);
        return NULL;
    }
    fileBuffer[st.st_size] = '\0';
    close(fd);
    // Prepare the message
    char *remote_fp = get_path(remote_file_path, local_file_path);
    size_t msg_len = strlen("WRITE") + strlen(local_file_path) + strlen(remote_fp) + st.st_size + sizeof(int) +
                     EXTRA_CHARS; // extra chars for delimiters and null terminator
    char *message = (char *) malloc(msg_len);
    snprintf(message, msg_len, "%s|%s|%s|%s|%s", "WRITE", local_file_path, remote_fp, fileBuffer, permission);
    free(fileBuffer);
    return message;
}

char *prepare_get(const char *remote_file_path) {
    size_t msg_len = strlen("GET") + strlen(remote_file_path) + EXTRA_CHARS;
    char *message = (char *) malloc(msg_len);
    snprintf(message, msg_len, "%s|%s", "GET", remote_file_path);
    return message;
}

char *prepare_rm(const char *remote_file_path) {
    size_t msg_len = strlen("RM") + strlen(remote_file_path) + EXTRA_CHARS;
    char *message = (char *) malloc(msg_len);
    snprintf(message, msg_len, "%s|%s", "RM", remote_file_path);
    return message;
}

void save_file(const char *path, const char *buffer, size_t buffer_size) {
    int fd = open(path, O_WRONLY | O_CREAT);
    if (fd == -1) {
        perror("Failed to open file for writing");
        return;
    }
    if (flock(fd, LOCK_EX) == -1) {
        perror("Failed to lock the file");
        close(fd);
        return;
    }
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        perror("Failed to create file stream for writing");
        flock(fd, LOCK_UN);
        close(fd);
        return;
    }
    size_t written = fwrite(buffer, 1, buffer_size, file);
    if (written < buffer_size) {
        perror("Failed to write the full buffer to file");
    }
    fclose(file);
    if (flock(fd, LOCK_UN) == -1) {
        perror("Failed to unlock the file");
    }
}

// if file2 exists, return file2
// if file1 is NULL, return a copy of file2 with -copy appended to the name
char *get_path(const char *file1, const char *file2) {
    if (file1 == NULL && access(file2, F_OK) != -1) {
        char *modifiedLocal = malloc(strlen(file2) + strlen("-copy") + 1);
        char *dot = strrchr(file2, '.');
        if (dot) {
            size_t prefixLength = dot - file2;
            strncpy(modifiedLocal, file2, prefixLength);
            modifiedLocal[prefixLength] = '\0';
            strcat(modifiedLocal, "-copy");
            strcat(modifiedLocal, dot);
        } else {
            strcpy(modifiedLocal, file2);
            strcat(modifiedLocal, "-copy");
        }
        return modifiedLocal;
    }
    return strdup(file1);
}