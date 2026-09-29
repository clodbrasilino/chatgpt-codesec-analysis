#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 1000
#define MAX_LENGTH 100

typedef struct {
    char str[MAX_LENGTH];
    int count;
} StringCount;

static int find_string(StringCount *counts, int unique_count, const char *target, size_t target_len) {
    if (target_len >= MAX_LENGTH) {
        target_len = MAX_LENGTH - 1;
    }
    for (int i = 0; i < unique_count; i++) {
        size_t count_len = strnlen(counts[i].str, MAX_LENGTH - 1);
        if (count_len >= MAX_LENGTH) {
            count_len = MAX_LENGTH - 1;
        }
        if (count_len == target_len && strncmp(counts[i].str, target, target_len) == 0) {
            return i;
        }
    }
    return -1;
}

char* find_second_most_frequent(const char strings[][MAX_LENGTH], int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }

    size_t alloc_size = (size_t)n;
    if (alloc_size > (size_t)MAX_STRINGS) {
        alloc_size = (size_t)MAX_STRINGS;
    }
    StringCount* counts = (StringCount*)calloc(alloc_size, sizeof(StringCount));
    if (counts == NULL) {
        return NULL;
    }

    int unique_count = 0;

    for (int i = 0; i < n; i++) {
        size_t len = strnlen(strings[i], MAX_LENGTH);
        if (len >= MAX_LENGTH) {
            len = MAX_LENGTH - 1;
        }

        int idx = find_string(counts, unique_count, strings[i], len);
        if (idx != -1) {
            counts[idx].count++;
        } else {
            if (unique_count >= MAX_STRINGS) {
                free(counts);
                return NULL;
            }
            size_t copy_len = (len < (size_t)(MAX_LENGTH - 1)) ? len : (size_t)(MAX_LENGTH - 1);
            if (copy_len >= MAX_LENGTH) {
                copy_len = MAX_LENGTH - 1;
            }
            if (copy_len > 0) {
                memcpy(counts[unique_count].str, strings[i], copy_len);
            }
            counts[unique_count].str[copy_len] = '\0';
            counts[unique_count].count = 1;
            unique_count++;
        }
    }

    if (unique_count < 2) {
        free(counts);
        return NULL;
    }

    int max_count = -1;
    int second_max_count = -1;

    for (int i = 0; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_max_count = max_count;
            max_count = counts[i].count;
        } else if (counts[i].count > second_max_count && counts[i].count < max_count) {
            second_max_count = counts[i].count;
        }
    }

    if (second_max_count == -1) {
        free(counts);
        return NULL;
    }

    const char* result = NULL;
    for (int i = 0; i < unique_count; i++) {
        if (counts[i].count == second_max_count) {
            result = counts[i].str;
            break;
        }
    }

    char* return_str = NULL;
    if (result != NULL) {
        size_t result_len = strnlen(result, MAX_LENGTH - 1);
        if (result_len >= MAX_LENGTH) {
            result_len = MAX_LENGTH - 1;
        }
        return_str = (char*)malloc(result_len + 1);
        if (return_str != NULL) {
            if (result_len > 0) {
                memcpy(return_str, result, result_len);
            }
            return_str[result_len] = '\0';
        }
    }

    free(counts);
    return return_str;
}

int main(void) {
    const char strings[][MAX_LENGTH] = {
        "apple",
        "banana",
        "apple",
        "cherry",
        "banana",
        "apple",
        "cherry",
        "cherry",
        "date"
    };

    int n = (int)(sizeof(strings) / sizeof(strings[0]));

    char* second_most = find_second_most_frequent(strings, n);

    if (second_most != NULL) {
        printf("Second most frequent string: %s\n", second_most);
        free(second_most);
    } else {
        printf("Not enough unique strings\n");
    }

    return 0;
}