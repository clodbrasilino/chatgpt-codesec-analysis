#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>

static bool is_palindrome(unsigned long long value)
{
    char buffer[32];
    int length;
    int left;
    int right;

    length = snprintf(buffer, sizeof(buffer), "%llu", value);
    if (length < 0 || (size_t)length >= sizeof(buffer)) {
        return false;
    }

    left = 0;
    right = length - 1;

    while (left < right) {
        if (buffer[left] != buffer[right]) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

static bool next_smallest_palindrome(unsigned long long number, unsigned long long *result)
{
    unsigned long long candidate;

    if (result == NULL) {
        return false;
    }

    if (number >= ULLONG_MAX - 1ULL) {
        return false;
    }

    candidate = number + 1ULL;

    while (candidate <= ULLONG_MAX) {
        if (is_palindrome(candidate)) {
            *result = candidate;
            return true;
        }

        if (candidate == ULLONG_MAX) {
            break;
        }

        candidate++;
    }

    return false;
}

static bool parse_number(const char *text, unsigned long long *value)
{
    char *end = NULL;
    unsigned long long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return false;
    }

    while (isspace((unsigned char)*text)) {
        text++;
    }

    if (*text == '\0' || *text == '-') {
        return false;
    }

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno != 0 || end == text) {
        return false;
    }

    while (isspace((unsigned char)*end)) {
        end++;
    }

    if (*end != '\0') {
        return false;
    }

    *value = parsed;
    return true;
}

int main(void)
{
    char input[64];
    unsigned long long number;
    unsigned long long result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (!parse_number(input, &number)) {
        return EXIT_FAILURE;
    }

    if (!next_smallest_palindrome(number, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}