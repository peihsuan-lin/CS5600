#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#define EXTRA_CHARS 3

char *prepare_write(const char *local_file_path, const char *remote_file_path, const char *permission);

char *prepare_get(const char *remote_file_path);

char *prepare_rm(const char *remote_file_path);

void save_file(const char *path, const char *buffer, size_t buffer_size);

char *get_path(const char *file1, const char *file2);

#endif // FILE_UTILS_H