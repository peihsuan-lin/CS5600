/*
* database.h / Practicum I
*
* Peihsuan Lin / CS5600 / Northeastern University
* Spring 2024 / May 26, 2024
*
*/
#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include "types.h"
#include <string.h>

int prepare_statements(sqlite3 *db);

void finalize_statements();

int insert(sqlite3 *db, Message *msg);

Message *select(sqlite3 *db, int id);

int init_tb(sqlite3 *db, char *errMsg);

void clear_db(sqlite3 *db);

#endif //DATABASE_H
