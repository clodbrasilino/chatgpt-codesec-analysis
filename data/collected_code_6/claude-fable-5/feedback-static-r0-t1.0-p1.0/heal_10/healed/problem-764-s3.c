#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

size_t count_numeric(const char *str)
{
    size_t count;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    count = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (isdigit((unsigned char)str[i])) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t result;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = count_numeric(buffer);

    if (printf("Numeric characters: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}