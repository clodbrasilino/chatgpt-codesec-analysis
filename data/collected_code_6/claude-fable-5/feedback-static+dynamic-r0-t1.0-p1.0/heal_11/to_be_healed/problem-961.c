#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 64
#define MAX_DISCARD_GUARD 4096

static int roman_char_value(char c)
{
    switch (toupper((unsigned char)c)) {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return -1;
    }
}

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t i;

    if (s == NULL) {
        return 0U;
    }

    for (i = 0; i < max_len; i++) {
        if (s[i] == '\0') {
            break;
        }
    }
    return i;
}

static int roman_to_int(const char *roman, size_t max_len, int *result)
{
    size_t len;
    size_t i;
    int total;

    if (roman == NULL || result == NULL || max_len == 0U) {
        return -1;
    }

    len = bounded_strlen(roman, max_len);
    if (len == 0U || len >= max_len) {
        return -1;
    }

    total = 0;
    for (i = 0; i < len; i++) {
        int current = roman_char_value(roman[i]);
        int next = 0;

        if (current < 0) {
            return -1;
        }

        if ((i + 1U) < len) {
            next = roman_char_value(roman[i + 1U]);
            if (next < 0) {
                return -1;
            }
        }

        if (current < next) {
            total += next - current;
            i++;
        } else {
            total += current;
        }

        if (total < 0 || total > 3999) {
            return -1;
        }
    }

    *result = total;
    return 0;
}

static void discard_remaining_input(void)
{
    size_t guard;

    for (guard = 0U; guard < (size_t)MAX_DISCARD_GUARD; guard++) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == '\n' || ch == EOF) {
            break;
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    int value;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a Roman numeral: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = bounded_strlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    } else if (len == sizeof(buffer) - 1U) {
        discard_remaining_input();
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (roman_to_int(buffer, sizeof(buffer), &value) != 0) {
        fprintf(stderr, "Invalid Roman numeral\n");
        return EXIT_FAILURE;
    }

    printf("%s = %d\n", buffer, value);
    return EXIT_SUCCESS;
}