#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 1000
#define MAX_LENGTH 100

typedef struct {
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
    
    StringCount *counts = malloc(n * sizeof(StringCount));
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
    int second_index = -1;
    
    for (int i = 0; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_max_count = max_count;
            second_index = max_index;
            max_count = counts[i].count;
            max_index = i;
        } else if (counts[i].count > second_max_count && counts[i].count < max_count) {
            second_max_count = counts[i].count;
            second_index = i;
        } else if (counts[i].count == second_max_count && second_index == -1 && max_index != i) {
            second_max_count = counts[i].count;
            second_index = i;
        } else if (counts[i].count == max_count && max_index != -1 && second_index == -1) {
            second_max_count = counts[i].count;
            second_index = i;
        }
    }
    
    if (second_index == -1) {
        free(counts);
        return NULL;
    }
    
    char *result = malloc((strlen(counts[second_index].str) + 1) * sizeof(char));
    if (result == NULL) {
        free(counts);
        return NULL;
    }
    
    strcpy(result, counts[second_index].str);
    free(counts);
    return result;
}

int main() {
    const char strings1[][MAX_LENGTH] = {
        "aaa", "bbb", "bbb", "aaa", "aaa", "ccc"
    };
    int n1 = 6;
    
    char *result1 = second_most_frequent(strings1, n1);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }
    
    const char strings2[][MAX_LENGTH] = {
        "abc", "abc", "def", "def", "def", "ghi"
    };
    int n2 = 6;
    
    char *result2 = second_most_frequent(strings2, n2);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }
    
    const char strings3[][MAX_LENGTH] = {
        "gsm", "gsm", "gsm", "cdma", "cdma", "lte"
    };
    int n3 = 6;
    
    char *result3 = second_most_frequent(strings3, n3);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }
    
    return 0;
}