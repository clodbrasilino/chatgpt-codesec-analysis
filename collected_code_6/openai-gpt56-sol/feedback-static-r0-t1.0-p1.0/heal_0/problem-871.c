#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static bool are_rotations(const char *first, const char *second)
{
    size_t length;
    char *combined;
    bool result;

    if (first == NULL || second == NULL) {
        return false;
    }

    length = strlen(first);
    if (length != strlen(second)) {
        return false;
    }

    if (length == 0U) {
        return true;
    }

    if (length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    combined = malloc((2U * length) + 1U);
    if (combined == NULL) {
        return false;
    }

    memcpy(combined, first, length);
    memcpy(combined + length, first, length);
    combined[2U * length] = '\0';

    result = strstr(combined, second) != NULL;
    free(combined);

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

    first[strcspn(first, "\r\n")] = '\0';
    second[strcspn(second, "\r\n")] = '\0';

    if (are_rotations(first, second)) {
        puts("The strings are rotations of each other.");
    } else {
        puts("The strings are not rotations of each other.");
    }

    return EXIT_SUCCESS;
}