#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static bool are_rotations(const char *first, const char *second)
{
    if (first == NULL || second == NULL) {
        return false;
    }

    size_t first_length = strlen(first);
    size_t second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    if (first_length == 0U) {
        return true;
    }

    if (first_length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    size_t buffer_size = (first_length * 2U) + 1U;
    char *doubled = malloc(buffer_size);

    if (doubled == NULL) {
        return false;
    }

    memcpy(doubled, first, first_length);
    memcpy(doubled + first_length, first, first_length);
    doubled[first_length * 2U] = '\0';

    bool result = strstr(doubled, second) != NULL;
    free(doubled);

    return result;
}

int main(void)
{
    char first[1024];
    char second[1024];

    if (fgets(first, sizeof(first), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(second, sizeof(second), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t first_length = strlen(first);
    size_t second_length = strlen(second);

    if (first_length > 0U && first[first_length - 1U] == '\n') {
        first[first_length - 1U] = '\0';
    } else if (!feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return EXIT_FAILURE;
    }

    if (second_length > 0U && second[second_length - 1U] == '\n') {
        second[second_length - 1U] = '\0';
    } else if (!feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return EXIT_FAILURE;
    }

    printf("%s\n", are_rotations(first, second) ? "Yes" : "No");

    return EXIT_SUCCESS;
}