#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search_literal(const char *original, const char *pattern, int **occurrences) {
    if (original == NULL || pattern == NULL || occurrences == NULL) {
        return -1;
    }

    int pattern_len = strlen(pattern);

    if (pattern_len == 0) {
        return -1;
    }

    int count = 0;
    const char *temp = original;
    while ((temp = strstr(temp, pattern)) != NULL) {
        count++;
        temp += pattern_len;
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
    temp = original;
    while ((temp = strstr(temp, pattern)) != NULL) {
        (*occurrences)[count++] = temp - original;
        temp += pattern_len;
    }

    return count;
}

int main(void) {
    const char *original = "hello world, hello universe, hello everyone";
    const char *pattern = "hello";
    int *occurrences = NULL;

    int count = search_literal(original, pattern, &occurrences);

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