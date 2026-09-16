#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char *minimize_string(const char *input)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t len;
    size_t i;
    size_t j;
    size_t max_count = 0;
    int target = -1;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);

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

    j = 0;
    for (i = 0; i < len; i++) {
        if ((unsigned char)input[i] != (unsigned char)target) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char buffer[1024];
    char *minimized;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    minimized = minimize_string(buffer);
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

    if (printf("Minimum length: %zu\n", strlen(minimized)) < 0) {
        free(minimized);
        return EXIT_FAILURE;
    }

    free(minimized);
    return EXIT_SUCCESS;
}