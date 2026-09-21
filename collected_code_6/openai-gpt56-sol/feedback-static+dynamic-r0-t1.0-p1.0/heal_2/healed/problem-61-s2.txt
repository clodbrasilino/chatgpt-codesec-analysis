#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_substrings(const char *digits, uint64_t *result)
{
    uint64_t counts[9] = {0};
    uint64_t total = 0;
    unsigned int prefix = 0;

    if (digits == NULL || result == NULL) {
        return -1;
    }

    counts[0] = 1;

    for (const unsigned char *p = (const unsigned char *)digits;
         *p != '\0';
         ++p) {
        unsigned int digit;

        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return -1;
        }

        digit = (unsigned int)(*p - (unsigned char)'0');
        prefix = (prefix + digit) % 9U;

        if (total > UINT64_MAX - counts[prefix]) {
            return -1;
        }

        total += counts[prefix];

        if (counts[prefix] == UINT64_MAX) {
            return -1;
        }

        ++counts[prefix];
    }

    *result = total;
    return 0;
}

static int read_line(char **line)
{
    char *buffer;
    size_t capacity = 64U;
    size_t length = 0U;

    if (line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            continue;
        }

        if (length >= capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *digits = NULL;
    uint64_t answer;
    int status = EXIT_FAILURE;

    if (read_line(&digits) != 0) {
        goto cleanup;
    }

    if (count_substrings(digits, &answer) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", answer) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(digits);
    return status;
}