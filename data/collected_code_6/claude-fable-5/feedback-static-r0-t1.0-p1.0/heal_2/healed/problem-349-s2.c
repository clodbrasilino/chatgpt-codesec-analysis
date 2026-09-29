#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256U

static bool is_binary_string(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return false;
    }

    for (i = 0U; (i < max_len) && (str[i] != '\0'); i++) {
        if ((str[i] != '0') && (str[i] != '1')) {
            return false;
        }
    }

    if (i >= max_len) {
        return false;
    }

    return true;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t len;

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    if (is_binary_string(buffer, sizeof(buffer))) {
        printf("The string is a binary string\n");
    } else {
        printf("The string is not a binary string\n");
    }

    return 0;
}