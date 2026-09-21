#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

bool first_last_equal(const char *str, size_t max_len)
{
    size_t len;

    if (str == NULL || max_len == 0) {
        return false;
    }

    len = strnlen(str, max_len);
    if (len == 0 || len == max_len) {
        return false;
    }

    return str[0] == str[len - 1];
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t len;

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0 || buffer[0] == '\0') {
        fprintf(stderr, "Empty string provided.\n");
        return 1;
    }

    if (first_last_equal(buffer, sizeof(buffer))) {
        printf("The first and last characters are equal.\n");
    } else {
        printf("The first and last characters are not equal.\n");
    }

    return 0;
}