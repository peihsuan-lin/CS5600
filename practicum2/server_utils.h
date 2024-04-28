#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

int write_to_file(const char *file, const char *file_contents);

int retrieve_file(int client_sock, char *file_path);

int remove_file(char *file_path);

char *get_directory(const char *remote, const char *local);

#endif
