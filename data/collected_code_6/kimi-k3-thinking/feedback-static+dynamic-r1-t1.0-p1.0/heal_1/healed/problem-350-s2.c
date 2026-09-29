#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SET_SIZE 256
#define BUFFER_SIZE 1024

static char find_most_frequent_char(const char *str, size_t len)
{
    size_t freq[CHAR_SET_SIZE] = {0};
    char most_frequent = '\0';
    size_t max_count = 0;
    size_t i;

    if (len == 0) {
        return '\0';
    }

    most_frequent = str[0];

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        freq[c]++;
        if (freq[c] > max_count) {
            max_count = freq[c];
            most_frequent = (char)c;
        }
    }

    return most_frequent;
}

char *minimize_string(const char *str, size_t max_len)
{
    char *result;
    char target;
    size_t len;
    size_t i;
    size_t j = 0;

    if (str == NULL || max_len == 0) {
        return NULL;
    }

    len = strnlen(str, max_len);

    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (len == 0) {
        result[0] = '\0';
        return result;
    }

    target = find_most_frequent_char(str, len);

    for (i = 0; i < len; i++) {
        if (str[i] != target) {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char *minimized;
    size_t input_len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    if (memchr(buffer, '\n', sizeof(buffer)) == NULL &&
        strnlen(buffer, sizeof(buffer)) == sizeof(buffer) - 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Warning: input too long, truncated to %zu characters\n",
                strnlen(buffer, sizeof(buffer)));
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (buffer[0] == '\0') {
        fprintf(stderr, "Empty string provided\n");
        return EXIT_FAILURE;
    }

    minimized = minimize_string(buffer, sizeof(buffer));
    if (minimized == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    input_len = strnlen(buffer, sizeof(buffer));

    printf("Minimized string: %s\n", minimized);
    printf("Original length: %zu\n", input_len);
    printf("Minimized length: %zu\n", strnlen(minimized, input_len + 1));

    free(minimized);
    minimized = NULL;

    return EXIT_SUCCESS;
}