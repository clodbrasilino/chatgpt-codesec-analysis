#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_INPUT_LEN 128

static bool is_decimal_precision_two(const char *str, size_t max_len)
{
    size_t len;
    size_t i = 0;
    size_t digits_before = 0;
    size_t digits_after = 0;
    bool dot_found = false;

    if (str == NULL || max_len == 0) {
        return false;
    }

    len = strnlen(str, max_len);
    if (len == 0 || len == max_len) {
        return false;
    }

    if (str[i] == '+' || str[i] == '-') {
        i++;
        if (i == len) {
            return false;
        }
    }

    for (; i < len; i++) {
        if (isdigit((unsigned char)str[i])) {
            if (dot_found) {
                digits_after++;
            } else {
                digits_before++;
            }
        } else if (str[i] == '.') {
            if (dot_found) {
                return false;
            }
            dot_found = true;
        } else {
            return false;
        }
    }

    if (digits_before == 0) {
        return false;
    }

    if (dot_found && (digits_after == 0 || digits_after > 2)) {
        return false;
    }

    return true;
}

static bool read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size < 2) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }

    buffer[size - 1] = '\0';

    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return true;
    }

    if (len == size - 1) {
        int ch;
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
        return false;
    }

    return true;
}

int main(void)
{
    char buffer[MAX_INPUT_LEN];

    printf("Enter a number: ");
    fflush(stdout);

    if (!read_line(buffer, sizeof(buffer))) {
        fprintf(stderr, "Input error or input too long\n");
        return 1;
    }

    if (is_decimal_precision_two(buffer, sizeof(buffer))) {
        printf("Valid decimal with precision of 2: %s\n", buffer);
    } else {
        printf("Invalid decimal with precision of 2: %s\n", buffer);
    }

    return 0;
}