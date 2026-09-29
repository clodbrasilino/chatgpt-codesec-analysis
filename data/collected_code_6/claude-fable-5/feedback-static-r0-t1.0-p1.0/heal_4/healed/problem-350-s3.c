#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1024

char *minimize_string(const char *input, size_t max_len);

char *minimize_string(const char *input, size_t max_len)
{
    size_t counts[256] = {0};
    size_t len;
    size_t i;
    size_t j;
    size_t max_count = 0;
    unsigned char target = 0;
    char *result;

    if (input == NULL || max_len == 0) {
        return NULL;
    }

    len = strnlen(input, max_len);

    for (i = 0; i < len; i++) {
        counts[(unsigned char)input[i]]++;
    }

    for (i = 0; i < 256; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            target = (unsigned char)i;
        }
    }

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if ((unsigned char)input[i] != target || max_count == 0) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char *buffer;
    char *minimized;

    buffer = calloc(MAX_INPUT_LEN, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failure\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, MAX_INPUT_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[MAX_INPUT_LEN - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    minimized = minimize_string(buffer, MAX_INPUT_LEN);
    if (minimized == NULL) {
        fprintf(stderr, "Error processing string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("Minimized string: %s\n", minimized) < 0) {
        free(minimized);
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("New length: %zu\n", strnlen(minimized, MAX_INPUT_LEN)) < 0) {
        free(minimized);
        free(buffer);
        return EXIT_FAILURE;
    }

    free(minimized);
    free(buffer);
    return EXIT_SUCCESS;
}