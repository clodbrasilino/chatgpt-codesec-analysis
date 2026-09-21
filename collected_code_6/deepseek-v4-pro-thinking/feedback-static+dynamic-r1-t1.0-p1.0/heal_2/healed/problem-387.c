#include <stdio.h>
#include <stdlib.h>

int hex_is_even(const char *str, size_t len)
{
    size_t start = 0;
    size_t end = len;
    int last_value = 0;

    if (str == NULL) {
        return -1;
    }

    while (start < end &&
           (str[start] == ' ' || str[start] == '\t' ||
            str[start] == '\n' || str[start] == '\r')) {
        start++;
    }

    if (start < end && (str[start] == '+' || str[start] == '-')) {
        start++;
    }

    if (start + 1 < end && str[start] == '0' &&
        (str[start + 1] == 'x' || str[start + 1] == 'X')) {
        start += 2;
    }

    while (end > start &&
           (str[end - 1] == ' ' || str[end - 1] == '\t' ||
            str[end - 1] == '\n' || str[end - 1] == '\r')) {
        end--;
    }

    if (start == end) {
        return -1;
    }

    for (size_t i = start; i < end; i++) {
        char c = str[i];

        if (c >= '0' && c <= '9') {
            last_value = c - '0';
        } else if (c >= 'a' && c <= 'f') {
            last_value = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'F') {
            last_value = c - 'A' + 10;
        } else {
            return -1;
        }
    }

    return last_value % 2 == 0 ? 1 : 0;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    size_t length = 0;
    int c;

    buffer = malloc(128);
    if (buffer == NULL) {
        return 1;
    }
    buffer_size = 128;

    while ((c = getchar()) != EOF && c != '\n') {
        if (length + 1 >= buffer_size) {
            char *new_buffer;
            buffer_size *= 2;
            new_buffer = realloc(buffer, buffer_size);
            if (new_buffer == NULL) {
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
        }
        buffer[length++] = (char)c;
    }
    buffer[length] = '\0';

    if (length == 0 && c == EOF) {
        free(buffer);
        return 1;
    }

    int result = hex_is_even(buffer, length);
    free(buffer);

    if (result < 0) {
        printf("Invalid hexadecimal number\n");
    } else if (result == 1) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}