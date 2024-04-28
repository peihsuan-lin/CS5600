/*
* message.h / Practicum I
*
* Peihsuan Lin / CS5600 / Northeastern University
* Spring 2024 / May 26, 2024
*
*/
#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "cache.h"
#include "types.h"


Message *create_msg(const char *sender, const char *receiver, const char *content);

int store_msg(sqlite3 *db, CacheManager *cache, Message *msg, ReplacementStrategy strategy);

Message *retrieve_msg(sqlite3 *db, CacheManager *cache, int id, ReplacementStrategy strategy);

#endif // MESSAGE_H