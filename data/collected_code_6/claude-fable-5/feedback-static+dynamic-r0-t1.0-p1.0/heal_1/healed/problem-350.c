#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_INPUT_LEN 1024

static size_t bounded_strlen(const char *s, size_t maxlen)
{
    size_t n = 0;

    while (n < maxlen && s[n] != '\0') {
        n++;
    }
    return n;
}

char *minimize_string(const char *input, size_t maxlen)
{
    size_t len;
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t i;
    size_t max_count = 0;
    int target = -1;
    char *result;
    size_t j = 0;

    if (input == NULL) {
        return NULL;
    }

    len = bounded_strlen(input, maxlen);

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)input[i];
        counts[c]++;
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            target = (int)i;
        }
    }

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if ((int)(unsigned char)input[i] != target) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char buffer[MAX_INPUT_LEN];
    char *minimized;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    minimized = minimize_string(buffer, sizeof(buffer));
    if (minimized == NULL) {
        fprintf(stderr, "Error minimizing string\n");
        return EXIT_FAILURE;
    }

    if (printf("Original: %s\n", buffer) < 0) {
        free(minimized);
        return EXIT_FAILURE;
    }

    if (printf("Minimized: %s\n", minimized) < 0) {
        free(minimized);
        return EXIT_FAILURE;
    }

    if (printf("Length reduced from %zu to %zu\n",
               bounded_strlen(buffer, sizeof(buffer)),
               bounded_strlen(minimized, sizeof(buffer))) < 0) {
        free(minimized);
        return EXIT_FAILURE;
    }

    free(minimized);
    minimized = NULL;

    return EXIT_SUCCESS;
}