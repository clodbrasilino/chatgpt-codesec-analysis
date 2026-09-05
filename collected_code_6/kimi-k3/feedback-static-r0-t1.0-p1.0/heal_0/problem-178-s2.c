#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search_literals(const char *text, const char *literals[], size_t count, size_t *found_indices) {
    size_t found = 0;
    size_t i;

    if (text == NULL || literals == NULL || found_indices == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (literals[i] != NULL && strstr(text, literals[i]) != NULL) {
            found_indices[found] = i;
            found++;
        }
    }

    return (int)found;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *literals[] = {"quick", "cat", "lazy", "bird", "fox"};
    size_t literal_count = sizeof(literals) / sizeof(literals[0]);
    size_t *found_indices = NULL;
    int result;
    int i;

    found_indices = (size_t *)malloc(literal_count * sizeof(size_t));
    if (found_indices == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    result = search_literals(text, literals, literal_count, found_indices);

    if (result < 0) {
        fprintf(stderr, "Invalid input parameters\n");
        free(found_indices);
        return EXIT_FAILURE;
    }

    printf("Text: \"%s\"\n", text);
    printf("Found %d literal(s):\n", result);

    for (i = 0; i < result; i++) {
        printf("  - \"%s\" at index %zu\n", literals[found_indices[i]], found_indices[i]);
    }

    free(found_indices);
    found_indices = NULL;

    return EXIT_SUCCESS;
}