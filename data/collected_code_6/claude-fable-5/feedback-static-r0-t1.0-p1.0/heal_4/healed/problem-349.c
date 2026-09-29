#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

bool is_binary_string(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return false;
    }

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }

    if (i == max_len) {
        return false;
    }

    return true;
}

static void flush_stdin(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t len;

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        flush_stdin();
    }

    if (is_binary_string(buffer, sizeof(buffer))) {
        printf("\"%s\" is a binary string\n", buffer);
    } else {
        printf("\"%s\" is not a binary string\n", buffer);
    }

    return EXIT_SUCCESS;
}