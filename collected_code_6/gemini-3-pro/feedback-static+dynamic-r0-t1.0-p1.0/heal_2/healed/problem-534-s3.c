#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_literal(const char *original, size_t original_len, const char *pattern, size_t pattern_len, int **occurrences) {
    if (original == NULL || pattern == NULL || occurrences == NULL) {
        return -1;
    }

    if (pattern_len == 0 || original_len == 0 || pattern_len > original_len) {
        return -1;
    }

    int count = 0;
    for (size_t i = 0; i <= original_len - pattern_len; i++) {
        if (strncmp(&original[i], pattern, pattern_len) == 0) {
            count++;
            i += pattern_len - 1;
        }
    }

    if (count == 0) {
        *occurrences = NULL;
        return 0;
    }

    *occurrences = (int *)malloc(count * sizeof(int));
    if (*occurrences == NULL) {
        return -1;
    }

    count = 0;
    for (size_t i = 0; i <= original_len - pattern_len; i++) {
        if (strncmp(&original[i], pattern, pattern_len) == 0) {
            (*occurrences)[count++] = i;
            i += pattern_len - 1;
        }
    }

    return count;
}

int main() {
    const char *original = "hello world, hello universe, hello everyone";
    const char *pattern = "hello";
    int *occurrences = NULL;

    size_t original_len = 43; 
    size_t pattern_len = 5;   

    int count = search_literal(original, original_len, pattern, pattern_len, &occurrences);

    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            printf("Pattern found at index: %d\n", occurrences[i]);
        }
        free(occurrences);
    } else if (count == 0) {
        printf("Pattern not found.\n");
    } else {
        printf("Error occurred during search.\n");
    }

    return 0;
}