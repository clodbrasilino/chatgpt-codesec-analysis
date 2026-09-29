#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 1000
#define MAX_LENGTH 100

typedef struct {
    char str[MAX_LENGTH];
    int count;
} StringCount;

int find_string(StringCount *counts, int unique_count, const char *target) {
    for (int j = 0; j < unique_count; j++) {
        if (strncmp(counts[j].str, target, MAX_LENGTH) == 0) {
            return j;
        }
    }
    return -1;
}

int add_string(StringCount *counts, int *unique_count, int max_strings, const char *source) {
    if (*unique_count >= max_strings) {
        return 0;
    }
    
    size_t source_len = strnlen(source, MAX_LENGTH);
    if (source_len >= MAX_LENGTH) {
        return 0;
    }
    
    memcpy(counts[*unique_count].str, source, source_len);
    counts[*unique_count].str[source_len] = '\0';
    counts[*unique_count].count = 1;
    (*unique_count)++;
    return 1;
}

char* second_most_frequent(const char strings[][MAX_LENGTH], int n) {
    if (n <= 0 || n > MAX_STRINGS) return NULL;
    
    StringCount *counts = calloc((size_t)n, sizeof(StringCount));
    if (counts == NULL) return NULL;
    
    int unique_count = 0;
    
    for (int i = 0; i < n; i++) {
        size_t input_len = strnlen(strings[i], MAX_LENGTH);
        if (input_len >= MAX_LENGTH) {
            free(counts);
            return NULL;
        }
        
        int found_idx = find_string(counts, unique_count, strings[i]);
        if (found_idx != -1) {
            counts[found_idx].count++;
        } else {
            if (!add_string(counts, &unique_count, n, strings[i])) {
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
    int max_count = counts[0].count;
    int second_count = -1;
    
    for (int i = 1; i < unique_count; i++) {
        if (counts[i].count > max_count) {
            second_count = max_count;
            second_max = first_max;
            max_count = counts[i].count;
            first_max = i;
        } else if (counts[i].count < max_count) {
            if (second_max == -1 || counts[i].count > second_count) {
                second_count = counts[i].count;
                second_max = i;
            }
        } else {
            if (second_max == -1) {
                second_count = counts[i].count;
                second_max = i;
            }
        }
    }
    
    if (second_max == -1) {
        free(counts);
        return NULL;
    }
    
    size_t result_len = strnlen(counts[second_max].str, MAX_LENGTH);
    char *result = calloc(result_len + 1, sizeof(char));
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
    const char strings[][MAX_LENGTH] = {
        "bbb", "bbb", "bbb",
        "abc", "abc", "abc", "abc",
        "gsm", "gsm"
    };
    int n = 9;
    
    char *result = second_most_frequent(strings, n);
    
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    
    return 0;
}