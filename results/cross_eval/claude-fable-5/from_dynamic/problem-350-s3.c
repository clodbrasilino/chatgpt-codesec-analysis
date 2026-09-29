#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *minimize_string(const char *input);

char *minimize_string(const char *input)
{
    size_t counts[256] = {0};
    size_t len;
    size_t i;
    size_t j;
    size_t max_count = 0;
    unsigned char target = 0;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strlen(input);

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
    char buffer[1024];
    char *minimized;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    minimized = minimize_string(buffer);
    if (minimized == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimized string: %s\n", minimized) < 0) {
        free(minimized);
        return EXIT_FAILURE;
    }

    if (printf("New length: %zu\n", strlen(minimized)) < 0) {
        free(minimized);
        return EXIT_FAILURE;
    }

    free(minimized);
    return EXIT_SUCCESS;
}