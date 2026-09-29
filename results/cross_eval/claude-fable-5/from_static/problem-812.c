#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096U

char *abbreviate_road(const char *input);

char *abbreviate_road(const char *input)
{
    size_t len;
    size_t i = 0;
    size_t j = 0;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    while (i < len) {
        if ((len - i) >= 4U && strncmp(&input[i], "road", 4U) == 0) {
            result[j] = 'r';
            j++;
            result[j] = 'd';
            j++;
            result[j] = '.';
            j++;
            i += 4U;
        } else {
            result[j] = input[i];
            j++;
            i++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *text = "Take the main road until the road ends.";
    char *abbreviated;

    abbreviated = abbreviate_road(text);
    if (abbreviated == NULL) {
        (void)fprintf(stderr, "Error: failed to process string\n");
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
    abbreviated = NULL;

    return EXIT_SUCCESS;
}