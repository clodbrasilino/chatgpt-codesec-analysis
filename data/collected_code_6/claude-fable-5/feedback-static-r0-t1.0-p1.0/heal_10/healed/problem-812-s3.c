#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

static char *abbreviate_road(const char *input)
{
    static const char pattern[] = "road";
    static const char replacement[] = "rd.";
    const size_t pattern_len = sizeof(pattern) - 1;
    const size_t replacement_len = sizeof(replacement) - 1;
    size_t input_len;
    size_t count;
    size_t result_len;
    size_t remaining;
    const char *p;
    char *result;
    char *dest;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    count = 0;
    p = input;
    while ((p = strstr(p, pattern)) != NULL) {
        count++;
        p += pattern_len;
    }

    if (count > input_len / pattern_len) {
        return NULL;
    }

    if (pattern_len < replacement_len) {
        return NULL;
    }

    result_len = input_len - count * (pattern_len - replacement_len);

    if (result_len >= SIZE_MAX) {
        return NULL;
    }

    result = malloc(result_len + 1);
    if (result == NULL) {
        return NULL;
    }

    dest = result;
    remaining = result_len;
    p = input;
    while (*p != '\0') {
        if (strncmp(p, pattern, pattern_len) == 0) {
            if (remaining < replacement_len) {
                free(result);
                return NULL;
            }
            if ((size_t)(dest - result) > result_len - replacement_len) {
                free(result);
                return NULL;
            }
            memcpy(dest, replacement, replacement_len);
            dest += replacement_len;
            remaining -= replacement_len;
            p += pattern_len;
        } else {
            if (remaining < 1) {
                free(result);
                return NULL;
            }
            if ((size_t)(dest - result) >= result_len) {
                free(result);
                return NULL;
            }
            *dest = *p;
            dest++;
            remaining--;
            p++;
        }
    }
    *dest = '\0';

    return result;
}

int main(void)
{
    const char *text = "Take the main road until the road forks near Elm road.";
    char *abbreviated;

    abbreviated = abbreviate_road(text);
    if (abbreviated == NULL) {
        fprintf(stderr, "Failed to abbreviate string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original:    %s\n", text) < 0) {
        free(abbreviated);
        return EXIT_FAILURE;
    }

    if (printf("Abbreviated: %s\n", abbreviated) < 0) {
        free(abbreviated);
        return EXIT_FAILURE;
    }

    free(abbreviated);
    return EXIT_SUCCESS;
}