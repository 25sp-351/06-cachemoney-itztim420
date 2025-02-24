#include <stdio.h>
#include <string.h>
#include "cache.h"

// In-memory cache to store values
char memo[MAX_MONEY][MAX_TEXT_LEN] = {0};

// Load cached values from a file
void load_cache() {
    FILE *file = fopen(CACHE_FILE, "r");
    if (!file) return; // No cache file yet, skip loading

    int money;
    char text[MAX_TEXT_LEN];

    while (fscanf(file, "%d = %[^\n]", &money, text) == 2) {
        if (money < MAX_MONEY) {
            strcpy(memo[money], text);
        }
    }

    fclose(file);
}

// Save a computed result to the cache file
void save_cache(int money, const char *text) {
    if (money >= MAX_MONEY) return; // Only cache small values

    // Store in memory for quick lookup
    strcpy(memo[money], text);

    // Append to the cache file
    FILE *file = fopen(CACHE_FILE, "a");
    if (file) {
        fprintf(file, "%d = %s\n", money, text);
        fclose(file);
    }
}

// Check if a value is cached
int get_cached_value(int money, char *result) {
    if (money < MAX_MONEY && memo[money][0] != '\0') {
        strcpy(result, memo[money]);
        return 1;
    }
    return 0;
}