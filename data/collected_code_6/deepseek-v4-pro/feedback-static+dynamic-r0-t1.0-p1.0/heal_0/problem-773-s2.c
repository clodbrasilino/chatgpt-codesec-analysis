#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_substrings(const char *str, const char *sub, int **positions, size_t *count) {
    if (str == NULL || sub == NULL || positions == NULL || count == NULL) {
        return -1;
    }

    size_t str_len = strlen(str);
    size_t sub_len = strlen(sub);

    if (sub_len == 0 || str_len < sub_len) {
        *count = 0;
        *positions = NULL;
        return 0;
    }

    size_t max_count = str_len - sub_len + 1;
    int *found_positions = (int *)malloc(max_count * sizeof(int));
    if (found_positions == NULL) {
        return -1;
    }

    size_t found_count = 0;
    const char *current = str;
    const char *ptr;

    while ((ptr = strstr(current, sub)) != NULL) {
        found_positions[found_count] = (int)(ptr - str);
        found_count++;
        current = ptr + 1;
        if (found_count >= max_count) {
            break;
        }
    }

    if (found_count == 0) {
        free(found_positions);
        *positions = NULL;
        *count = 0;
        return 0;
    }

    int *resized = (int *)realloc(found_positions, found_count * sizeof(int));
    if (resized == NULL) {
        free(found_positions);
        return -1;
    }

    *positions = resized;
    *count = found_count;
    return 0;
}

int main(void) {
    const char *text = "the cat and the dog and the bird";
    const char *sub = "the";
    int *positions = NULL;
    size_t count = 0;

    int result = find_substrings(text, sub, &positions, &count);
    if (result != 0) {
        printf("Error occurred\n");
        return 1;
    }

    printf("Found %zu occurrences of '%s' in '%s'\n", count, sub, text);
    for (size_t i = 0; i < count; i++) {
        printf("Position: %d\n", positions[i]);
    }

    free(positions);
    return 0;
}