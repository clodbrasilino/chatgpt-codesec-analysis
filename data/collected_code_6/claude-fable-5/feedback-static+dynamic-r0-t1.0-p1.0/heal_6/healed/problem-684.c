#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_INPUT 1024

static unsigned long long count_char_in_repeated_string(const char *str,
                                                        size_t str_len,
                                                        char target,
                                                        unsigned long long total_length)
{
    unsigned long long count_in_one;
    unsigned long long full_repeats;
    unsigned long long remainder;
    unsigned long long total_count;
    size_t i;

    if (str == NULL || str_len == 0U || total_length == 0ULL) {
        return 0ULL;
    }

    count_in_one = 0ULL;
    for (i = 0U; i < str_len; i++) {
        if (str[i] == target) {
            count_in_one++;
        }
    }

    full_repeats = total_length / (unsigned long long)str_len;
    remainder = total_length % (unsigned long long)str_len;

    if (count_in_one != 0ULL && full_repeats > ULLONG_MAX / count_in_one) {
        return ULLONG_MAX;
    }

    total_count = full_repeats * count_in_one;

    for (i = 0U; i < (size_t)remainder && i < str_len; i++) {
        if (str[i] == target) {
            if (total_count == ULLONG_MAX) {
                return ULLONG_MAX;
            }
            total_count++;
        }
    }

    return total_count;
}

static int discard_rest_of_line(void)
{
    int ch;
    size_t guard;

    guard = 0U;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        guard++;
        if (guard > (size_t)INT_MAX) {
            return -1;
        }
    }
    if (ch == EOF && guard == 0U) {
        return -1;
    }
    return 0;
}

static int read_line(char *buffer, size_t size, size_t *out_len)
{
    size_t len;

    if (buffer == NULL || size == 0U || size > (size_t)INT_MAX || out_len == NULL) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }
    buffer[size - 1U] = '\0';

    len = strnlen(buffer, size);
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    } else if (len == size - 1U) {
        if (discard_rest_of_line() != 0) {
            return -1;
        }
    }

    *out_len = len;
    return 0;
}

int main(void)
{
    char buffer[MAX_INPUT];
    char target;
    unsigned long long total_length;
    unsigned long long result;
    size_t len;
    int ch;

    memset(buffer, 0, sizeof(buffer));
    len = 0U;

    printf("Enter the string: ");
    fflush(stdout);
    if (read_line(buffer, sizeof(buffer), &len) != 0) {
        fprintf(stderr, "Error reading string input\n");
        return EXIT_FAILURE;
    }

    if (len == 0U) {
        fprintf(stderr, "Empty string is not allowed\n");
        return EXIT_FAILURE;
    }

    printf("Enter the character to count: ");
    fflush(stdout);
    ch = getchar();
    if (ch == EOF) {
        fprintf(stderr, "Error reading character input\n");
        return EXIT_FAILURE;
    }
    target = (char)ch;

    if (ch != '\n') {
        if (discard_rest_of_line() != 0) {
            fprintf(stderr, "Error reading character input\n");
            return EXIT_FAILURE;
        }
    }

    printf("Enter the total length of the repeated string: ");
    fflush(stdout);
    if (scanf("%llu", &total_length) != 1) {
        fprintf(stderr, "Error reading length input\n");
        return EXIT_FAILURE;
    }

    result = count_char_in_repeated_string(buffer, len, target, total_length);

    printf("The character '%c' occurs %llu times in the first %llu characters\n",
           target, result, total_length);

    return EXIT_SUCCESS;
}