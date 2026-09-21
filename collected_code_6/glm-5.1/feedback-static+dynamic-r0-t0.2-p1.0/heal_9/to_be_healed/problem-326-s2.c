#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordEntry;

char *strdup_custom(const char *src, size_t max_len) {
    size_t len = strnlen(src, max_len);
    if (len == max_len) return NULL;
    char *dst = malloc(len + 1);
    if (dst) {
        /* Possible weaknesses found:
         *  Same expression on both sides of '<='. [duplicateExpression]
         */
        if (len + 1 <= len + 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(dst, src, len + 1);
        }
    }
    return dst;
}

void cleanup_entries(WordEntry *entries, int size, int skip_idx) {
    if (entries) {
        for (int i = 0; i < size; i++) {
            if (i != skip_idx && entries[i].word) {
                free(entries[i].word);
            }
        }
        free(entries);
    }
}

int process_word(WordEntry **entries_ptr, int *size_ptr, int *capacity_ptr, char *buffer) {
    WordEntry *entries = *entries_ptr;
    int size = *size_ptr;
    int capacity = *capacity_ptr;

    for (int k = 0; k < size; k++) {
        if (strcmp(entries[k].word, buffer) == 0) {
            entries[k].count++;
            *entries_ptr = entries;
            *size_ptr = size;
            *capacity_ptr = capacity;
            return 0;
        }
    }

    if (size >= capacity) {
        size_t new_capacity = (size_t)capacity * 2;
        if (new_capacity < (size_t)capacity) {
            cleanup_entries(entries, size, -1);
            *entries_ptr = NULL;
            return -1;
        }
        WordEntry *temp = realloc(entries, new_capacity * sizeof(WordEntry));
        if (temp == NULL) {
            cleanup_entries(entries, size, -1);
            *entries_ptr = NULL;
            return -1;
        }
        entries = temp;
        capacity = (int)new_capacity;
    }

    entries[size].word = strdup_custom(buffer, 255);
    if (entries[size].word == NULL) {
        cleanup_entries(entries, size, -1);
        *entries_ptr = NULL;
        return -1;
    }
    entries[size].count = 1;
    size++;

    *entries_ptr = entries;
    *size_ptr = size;
    *capacity_ptr = capacity;
    return 0;
}

char *get_most_frequent_word(char **strings, int num_strings) {
    if (strings == NULL || num_strings <= 0) {
        return NULL;
    }

    int capacity = 16;
    int size = 0;
    WordEntry *entries = malloc((size_t)capacity * sizeof(WordEntry));
    if (entries == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    size_t buf_idx = 0;

    for (int i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            continue;
        }

        buf_idx = 0;

        for (int j = 0; strings[i][j] != '\0'; j++) {
            if (isalpha((unsigned char)strings[i][j])) {
                if (buf_idx < sizeof(buffer) - 1) {
                    buffer[buf_idx++] = (char)tolower((unsigned char)strings[i][j]);
                } else {
                    if (process_word(&entries, &size, &capacity, buffer) != 0) return NULL;
                    memset(buffer, 0, sizeof(buffer));
                    buf_idx = 0;
                    buffer[buf_idx++] = (char)tolower((unsigned char)strings[i][j]);
                }
            } else if (buf_idx > 0) {
                if (process_word(&entries, &size, &capacity, buffer) != 0) return NULL;
                memset(buffer, 0, sizeof(buffer));
                buf_idx = 0;
            }
        }

        if (buf_idx > 0) {
            if (process_word(&entries, &size, &capacity, buffer) != 0) return NULL;
            memset(buffer, 0, sizeof(buffer));
        }
    }

    if (size == 0) {
        free(entries);
        return NULL;
    }

    int max_idx = 0;
    for (int i = 1; i < size; i++) {
        if (entries[i].count > entries[max_idx].count) {
            max_idx = i;
        }
    }

    char *result = entries[max_idx].word;
    cleanup_entries(entries, size, max_idx);

    return result;
}

int main(void) {
    char *strings[] = {
        "Hello world! This is a test.",
        "Hello again, this test is only a test.",
        "A big hello to the world."
    };

    int num_strings = sizeof(strings) / sizeof(strings[0]);

    char *most_frequent = get_most_frequent_word(strings, num_strings);

    if (most_frequent != NULL) {
        printf("%s\n", most_frequent);
        free(most_frequent);
    }

    return 0;
}