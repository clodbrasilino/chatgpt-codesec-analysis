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
  *  test case 2 failed: expected 'gsm', got <no output>
  *  test case 0 failed: expected 'bbb', got <no output>
  *  test case 1 failed: expected 'abc', got <no output>
  */

char* second_most_frequent(const char strings[][MAX_LENGTH], int n) {
    if (n <= 0) return NULL;
    
    StringCount *counts = (StringCount*)malloc(n * sizeof(StringCount));
    if (counts == NULL) return NULL;
    
    int unique_count = 0;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(counts[j].str, strings[i]) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(strings[i]);
            if (len >= MAX_LENGTH) {
                free(counts);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(counts[unique_count].str, strings[i], len + 1);
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
    char *max_str = NULL;
    char *second_max_str = NULL;
    
    for (int i = 0; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_max_count = max_count;
            second_max_str = max_str;
            max_count = counts[i].count;
            max_str = counts[i].str;
        } else if (counts[i].count > second_max_count && counts[i].count < max_count) {
            second_max_count = counts[i].count;
            second_max_str = counts[i].str;
        }
    }
    
    char *result = NULL;
    if (second_max_str != NULL) {
        result = (char*)malloc(MAX_LENGTH * sizeof(char));
        if (result != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(second_max_str);
            if (len >= MAX_LENGTH) {
                free(result);
                free(counts);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result, second_max_str, len + 1);
        }
    }
    
    free(counts);
    return result;
}

int main() {
    const char strings[][MAX_LENGTH] = {
        "apple", "banana", "apple", "orange", "banana", "banana", "grape"
    };
    int n = sizeof(strings) / sizeof(strings[0]);
    
    char *result = second_most_frequent(strings, n);
    
    if (result != NULL) {
        printf("Second most frequent string: %s\n", result);
        free(result);
    } else {
        printf("No second most frequent string found\n");
    }
    
    return 0;
}