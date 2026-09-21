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

int find_string(StringCount *counts, int unique_count, const char *target, int max_len) {
    for (int j = 0; j < unique_count; j++) {
        if (strncmp(counts[j].str, target, max_len) == 0) {
            return j;
        }
    }
    return -1;
}

int add_string(StringCount *counts, int *unique_count, int max_strings, const char *source, int max_len) {
    if (*unique_count >= max_strings) {
        return 0;
    }
    
    size_t source_len = strnlen(source, max_len - 1);
    if (source_len >= (size_t)(max_len - 1)) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(counts[*unique_count].str, source, source_len);
    counts[*unique_count].str[source_len] = '\0';
    counts[*unique_count].count = 1;
    (*unique_count)++;
    return 1;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'abc', got <no output>
  *  test case 2 failed: expected 'gsm', got <no output>
  *  test case 0 failed: expected 'bbb', got <no output>
  */

char* second_most_frequent(const char strings[][MAX_LENGTH], int n) {
    if (n <= 0 || n > MAX_STRINGS) return NULL;
    
    StringCount *counts = calloc((size_t)n, sizeof(StringCount));
    if (counts == NULL) return NULL;
    
    int unique_count = 0;
    
    for (int i = 0; i < n; i++) {
        size_t input_len = strnlen(strings[i], MAX_LENGTH);
        if (input_len >= MAX_LENGTH) {
            free(counts);
            return NULL;
        }
        
        int found_idx = find_string(counts, unique_count, strings[i], MAX_LENGTH);
        if (found_idx != -1) {
            counts[found_idx].count++;
        } else {
            if (!add_string(counts, &unique_count, n, strings[i], MAX_LENGTH)) {
                free(counts);
                return NULL;
            }
        }
    }
    
    if (unique_count < 2) {
        free(counts);
        return NULL;
    }
    
    int first_max = 0, second_max = -1;
    
    for (int i = 1; i < unique_count; i++) {
        if (counts[i].count > counts[first_max].count) {
            second_max = first_max;
            first_max = i;
        } else if (counts[i].count < counts[first_max].count) {
            if (second_max == -1 || counts[i].count > counts[second_max].count) {
                second_max = i;
            }
        } else {
            if (second_max == -1 || counts[i].count > counts[second_max].count) {
                second_max = i;
            }
        }
    }
    
    if (second_max == -1) {
        free(counts);
        return NULL;
    }
    
    size_t result_len = strnlen(counts[second_max].str, MAX_LENGTH - 1);
    char *result = calloc(result_len + 1, sizeof(char));
    if (result == NULL) {
        free(counts);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, counts[second_max].str, result_len);
    result[result_len] = '\0';
    free(counts);
    return result;
}

int main() {
    char strings[][MAX_LENGTH] = {
        "apple", "banana", "apple", "orange", "banana", "apple", "grape"
    };
    int n = 7;
    
    char *result = second_most_frequent(strings, n);
    
    if (result != NULL) {
        printf("Second most frequent string: %s\n", result);
        free(result);
    } else {
        printf("No second most frequent string found\n");
    }
    
    return 0;
}