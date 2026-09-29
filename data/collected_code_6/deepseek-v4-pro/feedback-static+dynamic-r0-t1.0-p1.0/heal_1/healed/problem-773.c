#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_substrings(const char *str, const char *sub, int **positions) {
    if (str == NULL || sub == NULL || positions == NULL) {
        return -1;
    }

    size_t str_len = 0;
    size_t sub_len = 0;

    while (str[str_len] != '\0') {
        str_len++;
    }

    while (sub[sub_len] != '\0') {
        sub_len++;
    }

    if (sub_len == 0 || str_len < sub_len) {
        *positions = NULL;
        return 0;
    }

    int capacity = 10;
    int count = 0;
    *positions = (int *)malloc(capacity * sizeof(int));
    if (*positions == NULL) {
        return -1;
    }

    size_t max_index = str_len - sub_len;

    for (size_t i = 0; i <= max_index; i++) {
        size_t j;
        for (j = 0; j < sub_len; j++) {
            if (str[i + j] != sub[j]) {
                break;
            }
        }
        if (j == sub_len) {
            if (count >= capacity) {
                capacity *= 2;
                int *temp = (int *)realloc(*positions, capacity * sizeof(int));
                if (temp == NULL) {
                    free(*positions);
                    *positions = NULL;
                    return -1;
                }
                *positions = temp;
            }
            (*positions)[count++] = (int)i;
            i += sub_len - 1;
        }
    }

    return count;
}

int main(void) {
    const char *text = "This is a test. This test is only a test.";
    const char *substring = "test";
    int *positions = NULL;

    int count = find_substrings(text, substring, &positions);

    if (count < 0) {
        printf("Error occurred during search.\n");
        return 1;
    }

    printf("Found %d occurrence(s) of '%s' in '%s'\n", count, substring, text);

    for (int i = 0; i < count; i++) {
        printf("Occurrence %d at position: %d\n", i + 1, positions[i]);
    }

    free(positions);
    positions = NULL;

    count = find_substrings(text, "xyz", &positions);
    printf("\nFound %d occurrence(s) of 'xyz'\n", count);
    free(positions);
    positions = NULL;

    count = find_substrings(text, "", &positions);
    printf("Found %d occurrence(s) of empty string\n", count);
    free(positions);
    positions = NULL;

    return 0;
}