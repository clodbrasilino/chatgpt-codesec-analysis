#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t digit_sum(uint64_t value)
{
    uint64_t sum = 0;

    do {
        sum += value % UINT64_C(10);
        value /= UINT64_C(10);
    } while (value != 0);

    return sum;
}

static void divide_max_digit_sum(uint64_t number,
                                 uint64_t *first,
                                 uint64_t *second)
{
    uint64_t power = UINT64_C(1);

    while (power <= number / UINT64_C(10)) {
        power *= UINT64_C(10);
    }

    *first = power - UINT64_C(1);
    *second = number - *first;
}

static int read_line(char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (length > 0 && buffer[length - 1] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_number(uint64_t *number)
{
    char *buffer = NULL;
    char *start;
    char *end;
    uintmax_t value;

    if (number == NULL || !read_line(&buffer)) {
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || value == 0 ||
        value > UINT64_MAX) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *number = (uint64_t)value;
    free(buffer);
    return 1;
}

int main(void)
{
    uint64_t number;
    uint64_t first;
    uint64_t second;

    if (!read_number(&number)) {
        return EXIT_FAILURE;
    }

    divide_max_digit_sum(number, &first, &second);

    if (printf("%" PRIu64 " %" PRIu64 "\n", first, second) < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n",
               digit_sum(first) + digit_sum(second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}