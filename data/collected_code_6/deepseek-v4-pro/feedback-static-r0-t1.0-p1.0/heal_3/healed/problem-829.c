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
    
    StringCount *counts = malloc((size_t)n * sizeof(StringCount));
    if (!counts) return NULL;
    
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
            size_t len = strnlen(strings[i], MAX_LENGTH);
            if (len >= MAX_LENGTH) {
                len = MAX_LENGTH - 1;
            }
            memcpy(counts[unique_count].str, strings[i], len);
            counts[unique_count].str[len] = '\0';
            counts[unique_count].count = 1;
            unique_count++;
        }
    }
    
    if (unique_count < 2) {
        free(counts);
        return NULL;
    }
    
    int max_count = counts[0].count;
    int second_max_count = -1;
    int second_max_index = -1;
    
    for (int i = 1; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_max_count = max_count;
            max_count = counts[i].count;
            second_max_index = -1;
            for (int j = 0; j < i; j++) {
                if (counts[j].count == second_max_count && second_max_index == -1) {
                    second_max_index = j;
                }
            }
            if (second_max_index == -1) {
                second_max_index = i;
                second_max_count = counts[i].count;
            }
        } else if (counts[i].count < max_count) {
            if (second_max_count == -1 || counts[i].count > second_max_count ||
                (counts[i].count == second_max_count && second_max_index == -1)) {
                second_max_count = counts[i].count;
                second_max_index = i;
            }
        }
    }
    
    char *result = NULL;
    if (second_max_index != -1) {
        size_t len = strnlen(counts[second_max_index].str, MAX_LENGTH);
        result = malloc(len + 1);
        if (result) {
            memcpy(result, counts[second_max_index].str, len);
            result[len] = '\0';
        }
    }
    
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
    while ((c = getchar()) != '\n' && c != EOF) {}
    
    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        if (fgets(strings[i], MAX_LENGTH, stdin)) {
            size_t len = strnlen(strings[i], MAX_LENGTH);
            if (len > 0 && strings[i][len - 1] == '\n') {
                strings[i][len - 1] = '\0';
            }
        } else {
            strings[i][0] = '\0';
        }
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