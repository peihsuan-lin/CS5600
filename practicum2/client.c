/*
 * client.c -- TCP Socket Client
 * 
 * adapted from: 
 *   https://www.educative.io/answers/how-to-implement-tcp-sockets-in-c
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "command.h"

int main(int argc, char *argv[]) {

    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000];

    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));

    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0) {
        printf("Unable to create socket\n");
        close(socket_desc);
        return -1;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send connection request to server:
    if (connect(socket_desc, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        printf("Unable to connect\n");
        close(socket_desc);
        return -1;
    }
    printf("Connected with server successfully\n");

    if (argc < 3) {
        printf("Usage:\n");
        printf("  %s WRITE <local_file_path> <remote_file_path> <file_permission>\n", argv[0]);
        printf("  %s GET <remote_file_path> <local_file_path>\n", argv[0]);
        printf("  %s RM <remote_file_path>\n", argv[0]);
        return -1;
    }

    char *command = argv[1];
    char *message = NULL;

    if (strcmp(command, "WRITE") == 0) {
        if (argc != 4 && argc != 3 && argc != 5) {
            printf("Usage: %s WRITE <local_file_path> <remote_file_path> <file_permission>\n", argv[0]);
            return -1;
        }
        write_command(socket_desc, argv[2], argv[3], argv[4] ? argv[4] : "1"); // default permission is 1, writable
    } else if (strcmp(command, "GET") == 0) {
        if (argc != 4 && argc != 3) {
            printf("Usage: %s GET <remote_file_path> <local_file_path>\n", argv[0]);
            return -1;
        }
        get_command(socket_desc, argv[2], argv[3]);
    } else if (strcmp(command, "RM") == 0) {
        if (argc != 3) {
            printf("Usage: %s RM <remote_file_path>\n", argv[0]);
            return -1;
        }
        remove_command(socket_desc, argv[2]);
    } else {
        printf("Invalid command\n");
        return -1;
    }

    // Close the socket:
    close(socket_desc);
    free(message);
    return 0;
}
