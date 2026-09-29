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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    char *minimized;
    size_t original_len;
    size_t minimized_len;

    memset(buffer, 0, sizeof(buffer));

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

    original_len = strnlen(buffer, sizeof(buffer));
    minimized_len = strnlen(minimized, sizeof(buffer));

    if (printf("Original: %s\n", buffer) < 0) {
        free(minimized);
        return EXIT_FAILURE;
    }

    if (printf("Minimized: %s\n", minimized) < 0) {
        free(minimized);
        return EXIT_FAILURE;
    }

    if (printf("Length reduced from %zu to %zu\n",
               original_len, minimized_len) < 0) {
        free(minimized);
        return EXIT_FAILURE;
    }

    free(minimized);
    minimized = NULL;

    return EXIT_SUCCESS;
}