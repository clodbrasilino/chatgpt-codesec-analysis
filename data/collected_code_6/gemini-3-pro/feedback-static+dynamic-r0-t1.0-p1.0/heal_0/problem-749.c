#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings_numerically(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    
    char *endptr_a;
    char *endptr_b;
    
    long val_a = strtol(str_a, &endptr_a, 10);
    long val_b = strtol(str_b, &endptr_b, 10);
    
    if (val_a < val_b) {
        return -1;
    } else if (val_a > val_b) {
        return 1;
    } else {
        return 0;
    }
}

void sort_number_strings(char **array, size_t count) {
    if (array == NULL || count == 0) {
        return;
    }
    
    qsort(array, count, sizeof(char *), compare_strings_numerically);
}

int main(void) {
    const size_t num_strings = 5;
    char **strings = malloc(num_strings * sizeof(char *));
    
    if (strings == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    strings[0] = strdup("42");
    strings[1] = strdup("7");
    strings[2] = strdup("100");
    strings[3] = strdup("-5");
    strings[4] = strdup("0");
    
    for (size_t i = 0; i < num_strings; i++) {
        if (strings[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for string %zu\n", i);
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return 1;
        }
    }
    
    sort_number_strings(strings, num_strings);
    
    for (size_t i = 0; i < num_strings; i++) {
        printf("%s\n", strings[i]);
    }
    
    for (size_t i = 0; i < num_strings; i++) {
        free(strings[i]);
    }
    free(strings);
    
    return 0;
}