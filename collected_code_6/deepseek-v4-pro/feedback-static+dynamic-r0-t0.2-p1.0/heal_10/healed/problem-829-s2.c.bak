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
    
    StringCount *counts = malloc(n * sizeof(StringCount));
    if (!counts) return NULL;
    
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
    
    int max_count = 0;
    int second_max_count = 0;
    int max_index = -1;
    int second_max_index = -1;
    
    for (int i = 0; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_max_count = max_count;
            second_max_index = max_index;
            max_count = counts[i].count;
            max_index = i;
        } else if (counts[i].count > second_max_count && counts[i].count < max_count) {
            second_max_count = counts[i].count;
            second_max_index = i;
        } else if (counts[i].count == max_count) {
            if (second_max_index == -1 || strcmp(counts[i].str, counts[max_index].str) < 0) {
                max_index = i;
            }
        } else if (counts[i].count == second_max_count && second_max_count != 0) {
            if (second_max_index == -1 || strcmp(counts[i].str, counts[second_max_index].str) < 0) {
                second_max_index = i;
            }
        }
    }
    
    if (second_max_index == -1) {
        for (int i = 0; i < unique_count; i++) {
            if (counts[i].count < max_count) {
                if (second_max_index == -1 || counts[i].count > counts[second_max_index].count ||
                    (counts[i].count == counts[second_max_index].count && 
                     strcmp(counts[i].str, counts[second_max_index].str) < 0)) {
                    second_max_index = i;
                }
            }
        }
    }
    
    if (second_max_index == -1) {
        free(counts);
        return NULL;
    }
    
    char *result = malloc(strlen(counts[second_max_index].str) + 1);
    if (result) {
        strcpy(result, counts[second_max_index].str);
    }
    
    free(counts);
    return result;
}

int main() {
    char strings[][MAX_LENGTH] = {
        "apple", "banana", "apple", "orange", "banana", "apple", "grape"
    };
    int n = 7;
    
    char *result = second_most_frequent(strings, n);
    
    if (result) {
        printf("Second most frequent string: %s\n", result);
        free(result);
    } else {
        printf("No second most frequent string found\n");
    }
    
    return 0;
}