#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extract_rear(const char *const *strings, size_t count)
{
    char *result = NULL;
    size_t i;

    if (strings == NULL || count == 0U) {
        return NULL;
    }

    result = malloc(count + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        size_t len;

        if (strings[i] == NULL) {
            free(result);
            return NULL;
        }

        len = strlen(strings[i]);
        if (len == 0U) {
            result[i] = ' ';
        } else {
            result[i] = strings[i][len - 1U];
        }
    }

    result[count] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    const char *const default_words[] = { "Mers", "for", "Vers" };
    size_t default_count = sizeof(default_words) / sizeof(default_words[0]);
    const char *const *strings = NULL;
    size_t count = 0U;
    char *rear = NULL;
    size_t i;

    if (argc > 1) {
        strings = (const char *const *)&argv[1];
        count = (size_t)(argc - 1);
    } else {
        strings = default_words;
        count = default_count;
    }

    rear = extract_rear(strings, count);
    if (rear == NULL) {
        (void)fprintf(stderr, "Extraction failed\n");
        return EXIT_FAILURE;
    }

    if (printf("[") < 0) {
        free(rear);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("'%c'", rear[i]) < 0) {
            free(rear);
            return EXIT_FAILURE;
        }
        if (i + 1U < count) {
            if (printf(", ") < 0) {
                free(rear);
                return EXIT_FAILURE;
            }
        }
    }

    if (printf("]\n") < 0) {
        free(rear);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        free(rear);
        return EXIT_FAILURE;
    }

    free(rear);
    return EXIT_SUCCESS;
}