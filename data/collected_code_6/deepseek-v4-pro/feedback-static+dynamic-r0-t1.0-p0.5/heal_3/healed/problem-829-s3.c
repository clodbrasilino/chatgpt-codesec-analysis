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
            if (strncmp(counts[j].str, strings[i], MAX_LENGTH) == 0) {
                counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            size_t len = strlen(strings[i]);
            size_t copy_len = len < MAX_LENGTH - 1 ? len : MAX_LENGTH - 1;
            memcpy(counts[unique_count].str, strings[i], copy_len);
            counts[unique_count].str[copy_len] = '\0';
            counts[unique_count].count = 1;
            unique_count++;
        }
    }
    
    if (unique_count < 2) {
        free(counts);
        return NULL;
    }
    
    int first_max = 0, second_max = -1;
    int max_count = counts[0].count;
    
    for (int i = 1; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_max = first_max;
            first_max = i;
            max_count = counts[i].count;
        } else if (counts[i].count < max_count) {
            if (second_max == -1 || counts[i].count > counts[second_max].count) {
                second_max = i;
            }
        } else {
            if (second_max == -1) {
                second_max = i;
            }
        }
    }
    
    if (second_max == -1) {
        free(counts);
        return NULL;
    }
    
    size_t result_len = strlen(counts[second_max].str);
    char *result = (char*)malloc(result_len + 1);
    if (result == NULL) {
        free(counts);
        return NULL;
    }
    
    memcpy(result, counts[second_max].str, result_len);
    result[result_len] = '\0';
    free(counts);
    return result;
}

int main() {
    char strings[][MAX_LENGTH] = {
        "abc", "def", "abc", "def", "abc", "ghi"
    };
    int n = 6;
    
    char *result = second_most_frequent(strings, n);
    
    if (result != NULL) {
        printf("Second most frequent string: %s\n", result);
        free(result);
    } else {
        printf("No second most frequent string found\n");
    }
    
    return 0;
}