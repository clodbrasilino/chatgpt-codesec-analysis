#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

static int is_valid_hex(const char *str, size_t max_len)
{
    size_t i = 0;
    size_t len;

    if (str == NULL) {
        return 0;
    }

    len = strnlen(str, max_len);

    if (len == 0 || len >= max_len) {
        return 0;
    }

    if (len > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        i = 2;
    }

    if (i >= len) {
        return 0;
    }

    for (; i < len; i++) {
        if (!isxdigit((unsigned char)str[i])) {
            return 0;
        }
    }

    return 1;
}

static int is_hex_even(const char *hex, size_t max_len, int *result)
{
    size_t len;
    char last;

    if (hex == NULL || result == NULL) {
        return -1;
    }

    if (!is_valid_hex(hex, max_len)) {
        return -1;
    }

    len = strnlen(hex, max_len);

    if (len == 0 || len >= max_len) {
        return -1;
    }

    last = hex[len - 1];

    if (last >= '0' && last <= '9') {
        *result = ((last - '0') % 2 == 0) ? 1 : 0;
    } else {
        last = (char)tolower((unsigned char)last);
        if (last < 'a' || last > 'f') {
            return -1;
        }
        *result = ((last - 'a' + 10) % 2 == 0) ? 1 : 0;
    }

    return 0;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t len;
    int even = 0;

    printf("Enter a hexadecimal number: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            ;
        }
    }

    if (is_hex_even(buffer, sizeof(buffer), &even) != 0) {
        fprintf(stderr, "Invalid hexadecimal input\n");
        return EXIT_FAILURE;
    }

    if (even) {
        printf("%s is even\n", buffer);
    } else {
        printf("%s is odd\n", buffer);
    }

    return EXIT_SUCCESS;
}