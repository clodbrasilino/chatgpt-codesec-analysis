#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 1000
#define MAX_LENGTH 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[MAX_LENGTH];
    int count;
} StringCount;

char* find_second_most_frequent(const char strings[][MAX_LENGTH], int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }
    
    if (n > MAX_STRINGS) {
        return NULL;
    }
    
    StringCount* counts = (StringCount*)calloc((size_t)n, sizeof(StringCount));
    if (counts == NULL) {
        return NULL;
    }
    
    int unique_count = 0;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strncmp(counts[j].str, strings[i], MAX_LENGTH) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (unique_count >= n) {
                free(counts);
                return NULL;
            }
            size_t len = strnlen(strings[i], MAX_LENGTH);
            if (len >= MAX_LENGTH) {
                len = MAX_LENGTH - 1;
            }
            if (len >= MAX_LENGTH) {
                free(counts);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(counts[unique_count].str, strings[i], len);
            counts[unique_count].str[len] = '\0';
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
        size_t len = strnlen(result, MAX_LENGTH);
        if (len >= MAX_LENGTH) {
            len = MAX_LENGTH - 1;
        }
        return_str = (char*)malloc(len + 1);
        if (return_str != NULL) {
            if (len >= MAX_LENGTH) {
                free(return_str);
                free(counts);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(return_str, result, len);
            return_str[len] = '\0';
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