// command.h
#ifndef COMMAND_H
#define COMMAND_H

#include "file_utils.h"

void write_command(int sock, const char *local_fp, const char *remote_fp, const char *permission);

void get_command(int sock, char *, char *local_fp);

void remove_command(int sock, const char *remote_fp);

#endif
