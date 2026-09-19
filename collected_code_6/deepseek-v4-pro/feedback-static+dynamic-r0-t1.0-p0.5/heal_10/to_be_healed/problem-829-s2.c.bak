#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct {
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
    
    int max_count = -1;
    int second_max_count = -1;
    int max_index = -1;
    int second_max_index = -1;
    
    for (int i = 0; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_max_count = max_count;
            second_max_index = max_index;
            max_count = counts[i].count;
            max_index = i;
        } else if (counts[i].count > second_max_count && 
                   counts[i].count < max_count) {
            second_max_count = counts[i].count;
            second_max_index = i;
        } else if (counts[i].count == second_max_count && second_max_index != -1) {
            if (strcmp(counts[i].str, counts[second_max_index].str) < 0) {
                second_max_index = i;
            }
        } else if (counts[i].count == max_count && max_index != -1) {
            if (strcmp(counts[i].str, counts[max_index].str) < 0) {
                max_index = i;
            }
        } else if (second_max_index == -1 && counts[i].count < max_count) {
            second_max_count = counts[i].count;
            second_max_index = i;
        }
    }
    
    if (second_max_index == -1) {
        free(counts);
        return NULL;
    }
    
    char *result = (char*)malloc(MAX_LENGTH * sizeof(char));
    if (result == NULL) {
        free(counts);
        return NULL;
    }
    
    strncpy(result, counts[second_max_index].str, MAX_LENGTH - 1);
    result[MAX_LENGTH - 1] = '\0';
    
    free(counts);
    return result;
}

int main() {
    char strings1[][MAX_LENGTH] = {
        "abc", "abc", "abc", "def", "def", "ghi"
    };
    int n1 = sizeof(strings1) / sizeof(strings1[0]);
    
    char *result1 = second_most_frequent(strings1, n1);
    
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }
    
    char strings2[][MAX_LENGTH] = {
        "gsm", "gsm", "gsm", "cdma", "cdma", "lte"
    };
    int n2 = sizeof(strings2) / sizeof(strings2[0]);
    
    char *result2 = second_most_frequent(strings2, n2);
    
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }
    
    char strings3[][MAX_LENGTH] = {
        "bbb", "bbb", "bbb", "aaa", "aaa", "ccc"
    };
    int n3 = sizeof(strings3) / sizeof(strings3[0]);
    
    char *result3 = second_most_frequent(strings3, n3);
    
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }
    
    return 0;
}