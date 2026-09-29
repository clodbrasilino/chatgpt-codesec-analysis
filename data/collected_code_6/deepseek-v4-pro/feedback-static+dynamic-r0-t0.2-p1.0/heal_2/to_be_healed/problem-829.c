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
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(counts[unique_count].str, strings[i], MAX_LENGTH - 1);
            counts[unique_count].str[MAX_LENGTH - 1] = '\0';
            counts[unique_count].count = 1;
            unique_count++;
        }
    }
    
    if (unique_count < 2) {
        free(counts);
        return NULL;
    }
    
    int first_max = 0, second_max = -1;
    
    for (int i = 1; i < unique_count; i++) {
        /* Possible weaknesses found:
         *  Assuming that condition 'counts[i].count>counts[first_max].count' is not redundant
         */
        if (counts[i].count > counts[first_max].count) {
            second_max = first_max;
            first_max = i;
        /* Possible weaknesses found:
         *  Assuming that condition 'counts[i].count<counts[first_max].count' is not redundant
         */
        } else if (counts[i].count < counts[first_max].count) {
            if (second_max == -1 || counts[i].count > counts[second_max].count) {
                second_max = i;
            }
        /* Possible weaknesses found:
         *  Condition 'counts[i].count==counts[first_max].count' is always true
         *  Condition 'counts[i].count==counts[first_max].count' is always true [knownConditionTrueFalse]
         */
        } else if (counts[i].count == counts[first_max].count) {
            if (second_max == -1 || counts[i].count > counts[second_max].count) {
                second_max = i;
            }
        }
    }
    
    if (second_max == -1) {
        free(counts);
        return NULL;
    }
    
    char *result = (char*)malloc(MAX_LENGTH * sizeof(char));
    if (result == NULL) {
        free(counts);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(result, counts[second_max].str, MAX_LENGTH - 1);
    result[MAX_LENGTH - 1] = '\0';
    free(counts);
    return result;
}

int main() {
    char strings[][MAX_LENGTH] = {
        "apple", "banana", "apple", "orange", "banana", "apple", "grape"
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