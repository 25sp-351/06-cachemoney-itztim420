#ifndef CACHE_H
#define CACHE_H

#define CACHE_FILE "cache.txt"
#define MAX_MONEY 1500
#define MAX_TEXT_LEN 2048

void load_cache();
void save_cache(int money, const char *text);
int get_cached_value(int money, char *result);

#endif