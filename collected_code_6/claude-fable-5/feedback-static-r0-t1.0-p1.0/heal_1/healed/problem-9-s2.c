#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096U

int find_min_rotations(const char *str, size_t *result)
{
    size_t len;
    size_t i;
    char *temp;

    if (str == NULL || result == NULL) {
        return -1;
    }

    len = strnlen(str, MAX_INPUT_LEN + 1U);
    if (len == 0U || len > MAX_INPUT_LEN) {
        return -1;
    }

    if (len > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    temp = (char *)malloc((2U * len) + 1U);
    if (temp == NULL) {
        return -1;
    }

    if (snprintf(temp, (2U * len) + 1U, "%s%s", str, str) < 0) {
        free(temp);
        return -1;
    }

    for (i = 1U; i <= len; i++) {
        if (strncmp(str, &temp[i], len) == 0) {
            *result = i;
            free(temp);
            return 0;
        }
    }

    free(temp);
    return -1;
}

int main(void)
{
    const char *input = "abcabc";
    size_t rotations = 0U;

    if (find_min_rotations(input, &rotations) == 0) {
        if (printf("Minimum rotations for \"%s\": %zu\n", input, rotations) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "Error: could not compute rotations\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}