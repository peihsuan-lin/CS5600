/*
* cache.h / Practicum I
*
* Peihsuan Lin / CS5600 / Northeastern University
* Spring 2024 / May 26, 2024
*
*/
#ifndef CACHE_H
#define CACHE_H

#include <stdlib.h>
#include "types.h"


void init_cache(CacheManager *cache);

int find_slot(CacheManager *cache);

int least_recent_use(CacheManager *cache);

int random_replacement(CacheManager *cache);

void store_in_cache(CacheManager *cache, Message *msg, ReplacementStrategy strategy);

Message *retrieve(CacheManager *cache, int id);

void clear_cache(CacheManager *cache);

void print_stats(CacheManager *cache);

#endif
