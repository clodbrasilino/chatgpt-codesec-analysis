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
    
    StringCount *counts = (StringCount*)calloc((size_t)n, sizeof(StringCount));
    if (counts == NULL) return NULL;
    
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
            if (len < (size_t)(MAX_LENGTH - 1)) {
                memcpy(counts[unique_count].str, strings[i], len);
                counts[unique_count].str[len] = '\0';
                counts[unique_count].count = 1;
                unique_count++;
            } else {
                free(counts);
                return NULL;
            }
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
    
    if (second_max_str == NULL) {
        free(counts);
        return NULL;
    }
    
    size_t len = strnlen(second_max_str, MAX_LENGTH - 1);
    char *result = (char*)malloc(len + 1);
    if (result == NULL) {
        free(counts);
        return NULL;
    }
    
    memcpy(result, second_max_str, len);
    result[len] = '\0';
    
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