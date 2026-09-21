#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096U

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t n = 0U;

    while (n < max_len && s[n] != '\0') {
        n++;
    }

    return n;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['e', 'r', 'e'], got <no output>
  *  test case 0 failed: expected ['s', 'r', 's'], got <no output>
  *  test case 2 failed: expected ['a', 't', 'o'], got <no output>
  */

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

        len = bounded_strlen(strings[i], MAX_STR_LEN);
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
        fprintf(stderr, "Failed to extract rear elements\n");
        return EXIT_FAILURE;
    }

    if (printf("[") < 0) {
        free(rear);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; i++) {
        if (printf("'%c'%s", rear[i], (i + 1U < count) ? ", " : "") < 0) {
            free(rear);
            return EXIT_FAILURE;
        }
    }

    if (printf("]\n") < 0) {
        free(rear);
        return EXIT_FAILURE;
    }

    free(rear);
    return EXIT_SUCCESS;
}