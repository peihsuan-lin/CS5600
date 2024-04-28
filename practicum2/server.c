
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "server_utils.h"

pthread_mutex_t lock;
#define MAX_FILES 100

typedef struct {
    char file_path[1024];
    int is_writable;     // 0 for read-only, 1 for writable
} FilePermission;

FilePermission filePermissions[MAX_FILES];
int fileCount = 0;

int check_file_permission(const char *file_path, int permission) {
    for (int i = 0; i < fileCount; ++i) {
        if (strcmp(filePermissions[i].file_path, file_path) == 0) {
            return permission;
        }
    }
    // If the file is not found in the list, store it with the given permission
    if (fileCount < MAX_FILES) {
        strcpy(filePermissions[fileCount].file_path, file_path);
        filePermissions[fileCount].is_writable = permission;
        fileCount++;
        return 1;
    }
    return -1;
}

void *client_handler(void *socket_desc) {
    int sock = *(int *) socket_desc;
    free(socket_desc);
    char client_message[8196];
    memset(client_message, '\0', sizeof(client_message));
    // Receive client's message:
    if (recv(sock, client_message,
             sizeof(client_message), 0) < 0) {
        printf("Couldn't receive\n");
        close(sock);
        return NULL;
    }
    printf("Msg from client: %s\n", client_message);
    // Parse the message from the client:
    char *command, *local_fp, *remote_fp, *data, *message, *permission;
    char *response_message = NULL;
    command = strtok(client_message, "|");
    if (strcmp(command, "WRITE") == 0) {
        local_fp = strtok(NULL, "|");
        remote_fp = strtok(NULL, "|");
        data = strtok(NULL, "|");
        permission = strtok(NULL, "");
        pthread_mutex_lock(&lock);
        if (check_file_permission(remote_fp, atoi(permission)) == 0) {
            message = "[Write]Error: File is read-only";
        } else if (write_to_file(remote_fp, data) == -1) {
            message = "Error writing to file";
        } else {
            message = "File written successfully";
        }
        pthread_mutex_unlock(&lock);
    } else if (strcmp(command, "GET") == 0) {
        remote_fp = strtok(NULL, "|");
        if (retrieve_file(sock, remote_fp) == -1) {
            message = "Error retrieving file";
        } else {
            message = "File retrieved successfully";
        }
    } else if (strcmp(command, "RM") == 0) {
        remote_fp = strtok(NULL, "|");
        pthread_mutex_lock(&lock);
        if (check_file_permission(remote_fp, -1) == 0) {
            message = "[Remove]Error: File is read-only";
        }
        else if (remove_file(remote_fp) == -1) {
            message = "Error removing file";
        } else {
            message = "File removed successfully";
        }
        pthread_mutex_unlock(&lock);
    }
    if (response_message != NULL) {
        send(sock, response_message, strlen(response_message), 0);
    } else {
        send(sock, "Unknown command", strlen("Unknown command"), 0);
    }
    close(sock);
    return NULL;
}

int main(void) {
    int socket_desc, client_sock;
    socklen_t client_size;
    struct sockaddr_in server_addr, client_addr;

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init has failed\n");
        return 1;
    }
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0) {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");

    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind to the set port and IP:
    if (bind(socket_desc, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");

    // Listen for clients:
    listen(socket_desc, 5);
    puts("\nListening for incoming connections.....\n");
    // Accept an incoming connection:
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr *) &client_addr, &client_size);

    while ((client_sock = accept(socket_desc, (struct sockaddr *) &client_addr, &client_size))) {
        printf("Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        pthread_t client_thread;
        int *new_sock;
        new_sock = malloc(sizeof(int));
        *new_sock = client_sock;

        if (pthread_create(&client_thread, NULL, client_handler, (void *) new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
        pthread_detach(client_thread);
    }
    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
    pthread_mutex_destroy(&lock);
    return 0;
}
