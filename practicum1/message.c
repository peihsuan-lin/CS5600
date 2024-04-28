#include "message.h"

// Creates a new message with specified sender, receiver, and content, setting the current time as the timestamp.
Message *create_msg(const char *sender, const char *receiver, const char *content) {
    time_t current_time = time(NULL);
    Message *newMessage = (Message *) malloc(sizeof(Message));
    newMessage->timeSent = current_time;
    strcpy(newMessage->sender, sender);
    strcpy(newMessage->receiver, receiver);
    strcpy(newMessage->content, content);
    newMessage->flag = 0;
    return newMessage;
}

// Stores a message in the database and updates the cache with the new message based on the replacement strategy.
int store_msg(sqlite3 *db, CacheManager *cache, Message *msg, ReplacementStrategy strategy) {
    int result = insert(db, msg); // insert the message into the database.
    if (result == -1) {
        return -1;
    }
    msg->id = result; // Update the message's unique id.
    store_in_cache(cache, msg, strategy); // Update the cache with the new message.
    return 0;
}

// Retrieves a message by id, first trying the cache and then the database if not found in the cache.
Message *retrieve_msg(sqlite3 *db, CacheManager *cache, int id, ReplacementStrategy strategy) {
    Message *msg = retrieve(cache, id); // retrieve the message from the cache.
    if (msg != NULL) {
        return msg;
    }
    msg = select(db, id); // retrieve the message from the database if not found in the cache.
    if (msg != NULL) {
        store_in_cache(cache, msg, strategy);
    }
    return msg;
}