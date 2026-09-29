#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }

    return i;
}

static int is_valid_hex(const char *str, size_t max_len)
{
    size_t i = 0;
    size_t len;

    if (str == NULL) {
        return 0;
    }

    len = bounded_strlen(str, max_len);

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

    len = bounded_strlen(hex, max_len);

    if (len == 0) {
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

static void flush_stdin(void)
{
    int c;
    size_t guard = 0;
    const size_t guard_limit = 1000000;

    do {
        c = getchar();
        guard++;
    } while (c != '\n' && c != EOF && guard < guard_limit);
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1] = '\0';

    len = bounded_strlen(buffer, size);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return 0;
    }

    if (len == size - 1) {
        flush_stdin();
        return -2;
    }

    return 0;
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    int even = 0;
    int status;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a hexadecimal number: ");

    status = read_line(buffer, sizeof(buffer));

    if (status == -1) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (status == -2) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
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