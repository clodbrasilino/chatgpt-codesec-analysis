#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int hex_digit_value(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

static int is_hex_even(const char *hex)
{
    size_t len;
    size_t i;
    size_t start = 0;
    int last;

    if (hex == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(hex);

    if (len > 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
        start = 2;
    }

    if (len - start == 0) {
        return -1;
    }

    for (i = start; i < len; i++) {
        if (hex_digit_value(hex[i]) < 0) {
            return -1;
        }
    }

    last = hex_digit_value(hex[len - 1]);
    return (last % 2 == 0) ? 1 : 0;
}

static char *read_line(FILE *stream)
{
    size_t capacity = 128;
    size_t length = 0;
    size_t new_capacity;
    char *buffer;
    char *new_buffer;
    int ch;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length] = (char)ch;
        length++;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *buffer;
    int result;

    printf("Enter a hexadecimal number: ");

    buffer = read_line(stdin);
    if (buffer == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return 1;
    }

    result = is_hex_even(buffer);

    free(buffer);

    if (result < 0) {
        fprintf(stderr, "Error: invalid hexadecimal number\n");
        return 1;
    }

    printf("The hexadecimal number is %s\n", result == 1 ? "even" : "odd");

    return 0;
}