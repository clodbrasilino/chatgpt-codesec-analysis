#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 1000
#define MAX_LENGTH 100

typedef struct {
    char str[MAX_LENGTH];
    int count;
} StringCount;

char *second_most_frequent(char strings[][MAX_LENGTH], int n) {
    if (n <= 0) return NULL;
    
    StringCount *counts = calloc(n, sizeof(StringCount));
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
            strcpy(counts[unique_count].str, strings[i]);
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
    
    for (int i = 0; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_max_count = max_count;
            max_count = counts[i].count;
        } else if (counts[i].count > second_max_count && counts[i].count < max_count) {
            second_max_count = counts[i].count;
        }
    }
    
    if (second_max_count == 0) {
        free(counts);
        return NULL;
    }
    
    char *second_most = NULL;
    for (int i = 0; i < unique_count; i++) {
        if (counts[i].count == second_max_count) {
            if (second_most == NULL || strcmp(counts[i].str, second_most) < 0) {
                second_most = counts[i].str;
            }
        }
    }
    
    char *result = malloc(strlen(second_most) + 1);
    if (result) {
        strcpy(result, second_most);
    }
    
    free(counts);
    return result;
}

int main() {
    char strings[MAX_STRINGS][MAX_LENGTH];
    int n = 0;
    
    printf("Enter number of strings: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_STRINGS) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%99s", strings[i]);
    }
    
    char *result = second_most_frequent(strings, n);
    
    if (result) {
        printf("Second most frequent string: %s\n", result);
        free(result);
    } else {
        printf("No second most frequent string found\n");
    }
    
    return 0;
}