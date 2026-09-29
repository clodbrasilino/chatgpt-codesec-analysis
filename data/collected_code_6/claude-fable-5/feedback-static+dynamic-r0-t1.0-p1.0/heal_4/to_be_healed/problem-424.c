#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096U

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len = 0U;

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['e', 'r', 'e'], got <no output>
  *  test case 0 failed: expected ['s', 'r', 's'], got <no output>
  *  test case 2 failed: expected ['a', 't', 'o'], got <no output>
  */

static char *extract_rear(const char *const *strings, size_t count)
{
    char *result = NULL;
    size_t i;

    if (strings == NULL || count == 0U || count >= SIZE_MAX) {
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

        len = bounded_strlen(strings[i], MAX_STRING_LEN);
        if (len >= MAX_STRING_LEN) {
            free(result);
            return NULL;
        }

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
    char *rear = extract_rear(words, count);
    size_t i;

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

    free(rear);
    return EXIT_SUCCESS;
}