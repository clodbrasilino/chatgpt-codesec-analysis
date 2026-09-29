#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int hex_is_even(const char *str, size_t len)
{
    size_t start = 0;
    size_t end = len;
    int last_value = 0;

    if (str == NULL) {
        return -1;
    }

    while (start < end && isspace((unsigned char)str[start])) {
        start++;
    }

    if (start < end && (str[start] == '+' || str[start] == '-')) {
        start++;
    }

    if (start + 1 < end && str[start] == '0' &&
        (str[start + 1] == 'x' || str[start + 1] == 'X')) {
        start += 2;
    }

    while (end > start && isspace((unsigned char)str[end - 1])) {
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

char *read_line(size_t *len)
{
    size_t capacity = 256;
    char *buf = malloc(capacity);
    if (!buf) {
        return NULL;
    }

    size_t i = 0;
    int c;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (i + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
                free(buf);
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            char *newbuf = realloc(buf, new_capacity);
            if (!newbuf) {
                free(buf);
                return NULL;
            }
            buf = newbuf;
            capacity = new_capacity;
        }
        buf[i++] = (char)c;
    }

    if (c == EOF && i == 0) {
        free(buf);
        return NULL;
    }

    buf[i] = '\0';
    *len = i;
    return buf;
}

int main(void)
{
    size_t len;
    char *input = read_line(&len);
    if (input == NULL) {
        return 1;
    }

    int result = hex_is_even(input, len);

    if (result < 0) {
        printf("Invalid hexadecimal number\n");
    } else if (result == 1) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    free(input);
    return 0;
}