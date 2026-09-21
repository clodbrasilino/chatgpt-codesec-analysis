#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extract_rear_elements(const char *const *strings, size_t count)
{
    char *result = NULL;
    size_t i;

    if (strings == NULL || count == 0U) {
        return NULL;
    }

    result = (char *)malloc(count + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0U; i < count; i++) {
        size_t len;

        if (strings[i] == NULL) {
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
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

int main(void)
{
    const char *const words[] = { "Mers", "for", "Vers" };
    size_t count = sizeof(words) / sizeof(words[0]);
    char *rears;
    size_t i;

    rears = extract_rear_elements(words, count);
    if (rears == NULL) {
        (void)fprintf(stderr, "Failed to extract rear elements\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("%c\n", rears[i]) < 0) {
            free(rears);
            return EXIT_FAILURE;
        }
    }

    free(rears);
    return EXIT_SUCCESS;
}