#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <time.h>
#include "message.h"
#include "cache.h"

#define CACHE_SIZE 16
#define MESSAGE_SIZE 1024
#define NUM_MESSAGE 1000
#define NUM_ACCESSES 1000

// Tests the cache access by simulating random message retrievals and prints cache statistics.
void test_cache_access(CacheManager *cache, sqlite3 *db, ReplacementStrategy strategy) {
    srand(time(NULL));
    for (int i = 0; i < NUM_ACCESSES; i++) {
        int random_id = rand() % NUM_MESSAGE + 1; // Generate a random message ID starting from 1
        retrieve_msg(db, cache, random_id, strategy);
    }
    printf("for %d random accesses:\n", NUM_ACCESSES);
    print_stats(cache);
}

// Populates the database with a number of messages.
void populate(sqlite3 *db, CacheManager *cache, ReplacementStrategy strategy) {
    Message *new_msg = malloc(sizeof(MESSAGE_SIZE));
    for (int i = 0; i < NUM_MESSAGE; ++i) {
        new_msg = create_msg("sender", "receiver", "message");
        store_msg(db, cache, new_msg, strategy);
    }
}

// Tests cache access with a focus on locality, simulating a scenario where certain messages are accessed more frequently.
void test_cache_access_locality(CacheManager *cache, sqlite3 *db, ReplacementStrategy strategy) {
    srand(time(NULL));
    for (int i = 0; i < NUM_MESSAGE; i++) {
        int random_id = (CACHE_SIZE) + (rand() % 10); // Simulate more frequent access to a subset of messages.
        retrieve_msg(db, cache, random_id, strategy);
    }
    printf("for %d random accesses:\n", NUM_ACCESSES);
    print_stats(cache);
}
// Resets the cache and database to a clean state for another test run.

void restart(CacheManager *cache, sqlite3 *db) {
    clear_cache(cache);
    clear_db(db);
    init_tb(db, NULL);
    init_cache(cache);
    printf("\n");
}

int main() {
    sqlite3 *db;
    char *errMsg;
    int rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }
    init_tb(db, errMsg);
    CacheManager *cache = (CacheManager *) malloc(sizeof(CacheManager));
    init_cache(cache);
    prepare_statements(db);
    // Populate the database and cache, then test different replacement strategies and access patterns.
    populate(db, cache, RANDOM_REPLACEMENT);
    printf("\nTesting Random Replacement ");
    test_cache_access(cache, db, RANDOM_REPLACEMENT);

    restart(cache, db);
    printf("Testing LRU ");
    populate(db, cache, LEAST_RECENTLY_USED);
    test_cache_access(cache, db, LEAST_RECENTLY_USED);
    restart(cache, db);

    // Restart and test with different scenarios.
    printf("For locality retrieving:\n");
    printf("Testing Random Replacement ");
    populate(db, cache, RANDOM_REPLACEMENT);
    test_cache_access_locality(cache, db, RANDOM_REPLACEMENT);
    restart(cache, db);
    printf("Testing LRU ");
    populate(db, cache, LEAST_RECENTLY_USED);
    test_cache_access_locality(cache, db, LEAST_RECENTLY_USED);

    // Clean up resources before exiting.
    finalize_statements();
    sqlite3_close(db);
    free(cache);
    return 0;
}

