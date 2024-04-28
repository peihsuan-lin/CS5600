#include "server_utils.h"

int retrieve_file(int client_sock, char *file_path) {
    printf("[Server]Retrieving file: %s\n", file_path);
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        send(client_sock, "Error opening file", strlen("Error opening file"), 0);
        return -1;
    }
    char buffer[1024];
    int bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(client_sock, buffer, bytes_read, 0); // Send the file contents to the client
        printf("[Server]Sent %d bytes\n", bytes_read);
    }
    fclose(file);
    return 0;
}


int write_to_file(const char *file_path, const char *file_contents) {
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    if (fputs(file_contents, file) == EOF) {
        perror("Error writing to file");
        fclose(file);
        return -1;
    }
    fclose(file);
    printf("File written successfully\n");
    return 0;
}

int remove_file(char *file_path) {
    if (remove(file_path) == 0) {
        return 0;
    }
    return -1;
}

char *get_directory(const char *remote, const char *local) {
    if (remote == NULL) {
        char *modifiedLocal = malloc(strlen(local) + strlen("-copy") + 1);
        char *dot = strrchr(local, '.');
        if (dot) {
            size_t prefixLength = dot - local;
            strncpy(modifiedLocal, local, prefixLength);
            modifiedLocal[prefixLength] = '\0';
            strcat(modifiedLocal, "-copy");
            strcat(modifiedLocal, dot);
        } else {
            strcpy(modifiedLocal, local);
            strcat(modifiedLocal, "-copy");
        }
        return modifiedLocal;
    }
    return strdup(remote);
}