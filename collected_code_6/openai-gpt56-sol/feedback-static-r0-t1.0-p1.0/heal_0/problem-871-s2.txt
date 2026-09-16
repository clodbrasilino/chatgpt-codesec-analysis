#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool are_rotations(const char *first, const char *second)
{
    size_t length;
    char *doubled;
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

    doubled = malloc((2U * length) + 1U);
    if (doubled == NULL) {
        return false;
    }

    memcpy(doubled, first, length);
    memcpy(doubled + length, first, length);
    doubled[2U * length] = '\0';

    result = strstr(doubled, second) != NULL;
    free(doubled);

    return result;
}

int main(void)
{
    char first[1024];
    char second[1024];

    if (fgets(first, sizeof(first), stdin) == NULL ||
        fgets(second, sizeof(second), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    first[strcspn(first, "\r\n")] = '\0';
    second[strcspn(second, "\r\n")] = '\0';

    puts(are_rotations(first, second) ? "Yes" : "No");

    return EXIT_SUCCESS;
}