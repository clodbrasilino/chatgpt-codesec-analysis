#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_INPUT_LEN 1024

char *minimize_string(const char *input, size_t max_len)
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

    len = strnlen(input, max_len);
    if (len >= max_len) {
        return NULL;
    }

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
    char *buffer;
    char *minimized;
    size_t original_len;
    size_t minimized_len;

    buffer = calloc(MAX_INPUT_LEN, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Error allocating memory\n");
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
        fprintf(stderr, "Error minimizing string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    original_len = strnlen(buffer, MAX_INPUT_LEN);
    minimized_len = strnlen(minimized, MAX_INPUT_LEN);

    if (printf("Original: %s\n", buffer) < 0) {
        free(minimized);
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("Minimized: %s\n", minimized) < 0) {
        free(minimized);
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("Length reduced from %zu to %zu\n",
               original_len, minimized_len) < 0) {
        free(minimized);
        free(buffer);
        return EXIT_FAILURE;
    }

    free(minimized);
    minimized = NULL;
    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}