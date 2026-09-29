#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define MAX_INPUT_SIZE 256U

static int find_min_rotations(const char *str, size_t max_len)
{
    size_t len;
    size_t i;
    size_t doubled_size;
    char *doubled;
    int result;

    if (str == NULL || max_len == 0U) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == 0U || len == max_len) {
        return -1;
    }

    if (len > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    if (len > (size_t)INT_MAX) {
        return -1;
    }

    doubled_size = (2U * len) + 1U;

    doubled = calloc(doubled_size, sizeof(char));
    if (doubled == NULL) {
        return -1;
    }

    if (len > doubled_size - 1U) {
        free(doubled);
        return -1;
    }
    memcpy(doubled, str, len);

    if (len > doubled_size - len - 1U) {
        free(doubled);
        return -1;
    }
    memcpy(doubled + len, str, len);

    doubled[2U * len] = '\0';

    result = -1;
    for (i = 1U; i <= len; i++) {
        if (strncmp(doubled + i, str, len) == 0) {
            result = (int)i;
            break;
        }
    }

    free(doubled);
    return result;
}

int main(void)
{
    char buffer[MAX_INPUT_SIZE];
    size_t len;
    int rotations;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len >= sizeof(buffer)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    }

    if (len == 0U) {
        fprintf(stderr, "Empty string provided\n");
        return EXIT_FAILURE;
    }

    rotations = find_min_rotations(buffer, sizeof(buffer));
    if (rotations < 0) {
        fprintf(stderr, "Failed to compute rotations\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum rotations required: %d\n", rotations) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}