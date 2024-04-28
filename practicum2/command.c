#include "command.h"

void write_command(int sock, const char *local_fp, const char *remote_fp, const char *permission) {
    char *message = prepare_write(local_fp, remote_fp, permission);
    if (send(sock, message, strlen(message), 0) < 0) {
        printf("[Client]Failed to send WRITE\n");
        close(sock);
    }
    printf("[Client]File sent to server\n");
}

void get_command(int sock, char *remote_fp, char *local_fp) {
    char *message = prepare_get(remote_fp);
    if (send(sock, message, strlen(message), 0) < 0) {
        printf("[Client]Failed to send GET command\n");
        close(sock);
    }
    char recv_message[1024];
    int recv_size = recv(sock, recv_message, sizeof(recv_message), 0);
    printf("[Client]Received %d bytes\n", recv_size);
    if (recv_size < 0) {
        printf("[Client]Error while retrieving files\n");
        close(sock);
        return;
    }
    char *new_local_p = get_path(
            local_fp, remote_fp);
    save_file(new_local_p, recv_message, recv_size);
    free(new_local_p);
    printf("File has been received and saved to: %s\n", new_local_p);
}

void remove_command(int sock, const char *remote_fp) {
    char *message = prepare_rm(remote_fp);
    if (send(sock, message, strlen(message), 0) < 0) {
        printf("Failed to send RM command\n");
    }
}