#include "cache.h"
#include <limits.h>

// Initialize the cache
void init_cache(CacheManager *cache) {
    for (int i = 0; i < CACHE_SIZE; ++i) {
        cache->messages[i] = NULL;
        cache->lastAccessed[i] = -1;
    }
}

// Clear the cache by freeing all the messages and resetting the last accessed time
void clear_cache(CacheManager *cache) {
    for (int i = 0; i < CACHE_SIZE; ++i) {
        if (cache->messages[i] != NULL) {
            free(cache->messages[i]);
            cache->messages[i] = NULL;
        }
        cache->lastAccessed[i] = -1;
    }
    cache->cache_hits = 0;
    cache->cache_misses = 0;
}

// Finds an empty slot in the cache to store a new message. Returns -1 if the cache is full.
int find_slot(CacheManager *cache) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache->messages[i] == NULL) {
            return i;
        }
    }
    return -1; // Cache is full
}

// Identifies the least recently used message for eviction based on last access time.
int least_recent_use(CacheManager *cache) {
    int oldest_time = INT_MAX;
    int oldest_slot = -1;

    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache->lastAccessed[i] < oldest_time && cache->messages[i] != NULL) {
            oldest_time = cache->lastAccessed[i]; // Update oldest time.
            oldest_slot = i; // Update oldest slot.
        }
    }
    free(cache->messages[oldest_slot]);
    cache->messages[oldest_slot] = NULL;
    cache->lastAccessed[oldest_slot] = -1;
    return oldest_slot;
}

// Randomly selects a message slot for eviction.
int random_replacement(CacheManager *cache) {
    srand(time(NULL));
    int slot = rand() % CACHE_SIZE; // Select a random slot.
    free(cache->messages[slot]);
    cache->lastAccessed[slot] = -1; // Reset last accessed time.
    return slot;
}

void store_in_cache(CacheManager *cache, Message *msg, ReplacementStrategy strategy) {
    int slot = find_slot(cache); // Find an empty slot.
    if (slot == -1) { // If the cache is full, determine which slot to reuse.
        switch (strategy) {
            case LEAST_RECENTLY_USED:
                slot = least_recent_use(cache); // LRU
                break;
            case RANDOM_REPLACEMENT:
                slot = random_replacement(cache); // Random replacement
                break;
            default:
                break;
        }
    }
    cache->messages[slot] = msg; // Store the message in the selected slot.
    cache->lastAccessed[slot] = time(NULL); // Update the last accessed time.
}

// Attempts to retrieve a message from the cache by id, updating cache hits and misses accordingly.
Message *retrieve(CacheManager *cache, int id) {
    for (int i = 0; i < CACHE_SIZE; ++i) {
        if (cache->messages[i] != NULL && cache->messages[i]->id == id) {
            cache->lastAccessed[i] = time(NULL);
            cache->cache_hits++;
            return cache->messages[i]; // Return the message if found.
        }
    }
    cache->cache_misses++; // Increment cache misses if not found.
    return NULL; // Return NULL if the message is not found.
}

// Calculates cache hits, misses, and the hit ratio.
void print_stats(CacheManager *cache) {
    printf("Cache Hits: %d\n", cache->cache_hits);
    printf("Cache Misses: %d\n", cache->cache_misses);
    if (cache->cache_hits + cache->cache_misses > 0) {
        double hit_ratio = ((double) cache->cache_hits / (cache->cache_hits + cache->cache_misses)) * 100;
        printf("Cache Hit Ratio: %.2lf%%\n", hit_ratio);
    }
}
