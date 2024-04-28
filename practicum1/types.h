/*
* types.h / Practicum I
*
* Peihsuan Lin / CS5600 / Northeastern University
* Spring 2024 / May 26, 2024
*
*/
#ifndef TYPES_H
#define TYPES_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define CACHE_SIZE 16

// Represents a message with metadata and content.
typedef struct Message {
    int id;                      // Unique identifier for the message.
    time_t timeSent;             // Timestamp when the message was sent.
    char sender[128];            // Name of the sender.
    char receiver[128];          // Name of the receiver.
    char content[512];           // Actual content of the message.
    int flag;                    // Status flag, e.g., 0 for not delivered, 1 for delivered.
} Message;
// Manages the caching of messages, including tracking access times and cache performance.
typedef struct CacheManager {
    Message *messages[CACHE_SIZE];  // Array of pointers to cached messages.
    time_t lastAccessed[CACHE_SIZE];  // Array of timestamps for last access of each cached message.
    int cache_hits;                // Number of times a requested message was found in the cache.
    int cache_misses;              // Number of times a requested message was not found in the cache.
} CacheManager;

// Possible strategies for page replacement
typedef enum {
    LEAST_RECENTLY_USED,
    RANDOM_REPLACEMENT
} ReplacementStrategy;
#endif // TYPES_H
