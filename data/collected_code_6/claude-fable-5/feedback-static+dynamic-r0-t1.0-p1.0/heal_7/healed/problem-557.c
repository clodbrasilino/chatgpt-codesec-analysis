#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i;

    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }

    return i;
}

void toggle_case(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return;
    }

    len = bounded_strlen(str, max_len);
    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isupper(c)) {
            str[i] = (char)tolower(c);
        } else if (islower(c)) {
            str[i] = (char)toupper(c);
        }
    }
}

int main(void)
{
    char *buffer;

    buffer = calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[BUFFER_SIZE - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    toggle_case(buffer, BUFFER_SIZE);

    if (printf("%s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}