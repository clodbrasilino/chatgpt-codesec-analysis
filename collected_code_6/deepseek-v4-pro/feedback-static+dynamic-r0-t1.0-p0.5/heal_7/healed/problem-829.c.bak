#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 1000
#define MAX_LENGTH 100

typedef struct {
    char str[MAX_LENGTH];
    int count;
} StringCount;

char* second_most_frequent(const char strings[][MAX_LENGTH], int n) {
    if (n <= 0) return NULL;
    
    StringCount *counts = (StringCount*)calloc(n, sizeof(StringCount));
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
        } else if (counts[i].count == second_max_count && second_max_idx != -1) {
            if (strcmp(counts[i].str, counts[second_max_idx].str) < 0) {
                second_max_idx = i;
            }
        }
    }
    
    if (second_max_idx == -1) {
        free(counts);
        return NULL;
    }
    
    char *result = (char*)malloc(MAX_LENGTH * sizeof(char));
    if (result == NULL) {
        free(counts);
        return NULL;
    }
    
    strncpy(result, counts[second_max_idx].str, MAX_LENGTH - 1);
    result[MAX_LENGTH - 1] = '\0';
    free(counts);
    return result;
}

int main() {
    char strings[][MAX_LENGTH] = {
        "abc", "abc", "abc", "bbb", "bbb", "gsm", "gsm", "gsm", "gsm"
    };
    int n = sizeof(strings) / sizeof(strings[0]);
    
    char *result = second_most_frequent(strings, n);
    
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    
    return 0;
}