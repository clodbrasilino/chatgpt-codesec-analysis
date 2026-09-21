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

static int find_string(StringCount *counts, int unique_count, const char *target, size_t target_len) {
    for (int i = 0; i < unique_count; i++) {
        if (strncmp(counts[i].str, target, target_len) == 0 && 
            counts[i].str[target_len] == '\0') {
            return i;
        }
    }
    return -1;
}

char* find_second_most_frequent(const char strings[][MAX_LENGTH], int n) {
    if (n <= 0 || strings == NULL) {
        return NULL;
    }
    
    StringCount* counts = (StringCount*)calloc((size_t)n, sizeof(StringCount));
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
            if (len < MAX_LENGTH) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(counts[unique_count].str, strings[i], len);
                counts[unique_count].str[len] = '\0';
            } else {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(counts[unique_count].str, strings[i], MAX_LENGTH - 1);
                counts[unique_count].str[MAX_LENGTH - 1] = '\0';
            }
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
        size_t result_len = strnlen(result, MAX_LENGTH);
        if (result_len >= MAX_LENGTH) {
            result_len = MAX_LENGTH - 1;
        }
        return_str = (char*)malloc(result_len + 1);
        if (return_str != NULL) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(return_str, result, result_len);
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