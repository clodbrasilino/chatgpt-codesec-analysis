#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 1000
#define MAX_LENGTH 100

typedef struct {
    char str[MAX_LENGTH];
    int count;
} StringCount;

char *second_most_frequent(const char strings[][MAX_LENGTH], int n) {
    if (n <= 0) return NULL;
    
    StringCount *counts = calloc((size_t)n, sizeof(StringCount));
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
            size_t len = strlen(strings[i]);
            if (len >= MAX_LENGTH) {
                len = MAX_LENGTH - 1;
            }
            if (unique_count < n) {
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
    
    int first_max = 0;
    int second_max = -1;
    
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
    
    size_t len = strlen(counts[second_max].str);
    if (len >= MAX_LENGTH) {
        len = MAX_LENGTH - 1;
    }
    char *result = malloc(len + 1);
    if (!result) {
        free(counts);
        return NULL;
    }
    memcpy(result, counts[second_max].str, len);
    result[len] = '\0';
    
    free(counts);
    return result;
}

int main(void) {
    char strings[MAX_STRINGS][MAX_LENGTH];
    int n = 0;
    
    printf("Enter number of strings: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_STRINGS) {
        printf("Invalid input\n");
        return 1;
    }
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%99s", strings[i]) != 1) {
            printf("Input error\n");
            return 1;
        }
        while ((c = getchar()) != '\n' && c != EOF);
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