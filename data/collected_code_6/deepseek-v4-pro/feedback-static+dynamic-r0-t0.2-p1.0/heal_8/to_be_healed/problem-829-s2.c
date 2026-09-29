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
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'abc', got <no output>
  *  test case 2 failed: expected 'gsm', got <no output>
  *  test case 0 failed: expected 'bbb', got <no output>
  */

char* second_most_frequent(const char strings[][MAX_LENGTH], int n) {
    if (n <= 0 || n > MAX_STRINGS) return NULL;
    
    StringCount *counts = calloc((size_t)n, sizeof(StringCount));
    if (!counts) return NULL;
    
    int unique_count = 0;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strncmp(counts[j].str, strings[i], MAX_LENGTH - 1) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            size_t len = strnlen(strings[i], MAX_LENGTH - 1);
            if (len >= MAX_LENGTH - 1) {
                free(counts);
                return NULL;
            }
            if (unique_count >= n) {
                free(counts);
                return NULL;
            }
            if (len + 1 > MAX_LENGTH) {
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
    
    int max_count = 0;
    int second_max_count = 0;
    int max_idx = -1;
    int second_max_idx = -1;
    
    for (int i = 0; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_max_count = max_count;
            second_max_idx = max_idx;
            max_count = counts[i].count;
            max_idx = i;
        } else if (counts[i].count > second_max_count && counts[i].count < max_count) {
            second_max_count = counts[i].count;
            second_max_idx = i;
        } else if (second_max_idx == -1 && counts[i].count < max_count) {
            second_max_count = counts[i].count;
            second_max_idx = i;
        }
    }
    
    if (second_max_idx == -1) {
        free(counts);
        return NULL;
    }
    
    size_t len = strnlen(counts[second_max_idx].str, MAX_LENGTH - 1);
    if (len >= MAX_LENGTH - 1) {
        free(counts);
        return NULL;
    }
    
    char *result = malloc(len + 1);
    if (!result) {
        free(counts);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, counts[second_max_idx].str, len);
    result[len] = '\0';
    
    free(counts);
    return result;
}

int main() {
    const char strings[][MAX_LENGTH] = {
        "bbb", "bbb", "abc", "abc", "abc", "gsm", "gsm"
    };
    int n = 7;
    
    char *result = second_most_frequent(strings, n);
    
    if (result) {
        printf("%s\n", result);
        free(result);
    }
    
    return 0;
}