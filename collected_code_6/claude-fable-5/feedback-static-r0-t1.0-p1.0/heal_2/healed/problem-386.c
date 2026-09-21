#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1024

static long min_swaps_for_balancing(const char *str, size_t len);
static int validate_input(const char *str, size_t len);
static char *read_input_line(size_t *out_len);

static int validate_input(const char *str, size_t len)
{
    size_t i;
    size_t open_count = 0;
    size_t close_count = 0;

    if (str == NULL) {
        return -1;
    }

    if (len == 0U || (len % 2U) != 0U) {
        return -1;
    }

    for (i = 0U; i < len; i++) {
        if (str[i] == '[') {
            open_count++;
        } else if (str[i] == ']') {
            close_count++;
        } else {
            return -1;
        }
    }

    if (open_count != close_count) {
        return -1;
    }

    return 0;
}

static long min_swaps_for_balancing(const char *str, size_t len)
{
    size_t i;
    long open_seen = 0L;
    long close_seen = 0L;
    long imbalance = 0L;
    long swaps = 0L;

    for (i = 0U; i < len; i++) {
        if (str[i] == '[') {
            open_seen++;
            if (imbalance > 0L) {
                swaps += imbalance;
                imbalance--;
            }
        } else {
            close_seen++;
            imbalance = close_seen - open_seen;
        }
    }

    return swaps;
}

static char *read_input_line(size_t *out_len)
{
    char *buffer;
    size_t capacity = (size_t)MAX_INPUT_LEN + 1U;
    size_t len;
    char *newline;

    if (out_len == NULL) {
        return NULL;
    }

    buffer = calloc(capacity, sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return NULL;
    }

    buffer[capacity - 1U] = '\0';

    newline = memchr(buffer, '\n', capacity);
    if (newline == NULL) {
        len = strnlen(buffer, capacity - 1U);
        if (len == capacity - 1U) {
            free(buffer);
            return NULL;
        }
    } else {
        *newline = '\0';
        len = (size_t)(newline - buffer);
    }

    *out_len = len;
    return buffer;
}

int main(void)
{
    char *buffer;
    size_t len = 0U;
    long result;

    buffer = read_input_line(&len);
    if (buffer == NULL) {
        (void)fprintf(stderr, "Error: failed to read input or input too long\n");
        return EXIT_FAILURE;
    }

    if (validate_input(buffer, len) != 0) {
        (void)fprintf(stderr, "Error: invalid input string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    result = min_swaps_for_balancing(buffer, len);
    free(buffer);

    if (printf("Minimum number of swaps: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}