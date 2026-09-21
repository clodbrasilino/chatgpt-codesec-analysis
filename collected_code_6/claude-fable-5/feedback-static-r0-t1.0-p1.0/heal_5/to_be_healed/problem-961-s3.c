#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ROMAN_LEN 64
#define MAX_DISCARD 4096

static int roman_char_value(char c)
{
    switch (toupper((unsigned char)c)) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default:  return -1;
    }
}

static int roman_to_int(const char *s, size_t max_len, int *result)
{
    size_t len;
    size_t i;
    int total = 0;

    if (s == NULL || result == NULL || max_len == 0) {
        return -1;
    }

    len = strnlen(s, max_len);
    if (len == 0 || len >= max_len) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        int current = roman_char_value(s[i]);
        if (current < 0) {
            return -1;
        }

        if (i + 1 < len) {
            int next = roman_char_value(s[i + 1]);
            if (next < 0) {
                return -1;
            }
            if (current < next) {
                total += next - current;
                i++;
                continue;
            }
        }
        total += current;
    }

    *result = total;
    return 0;
}

static int discard_remaining_input(void)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;
    size_t discarded = 0;

    while (discarded < MAX_DISCARD) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            return 0;
        }
        discarded++;
    }
    return -1;
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size < 2) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1] = '\0';
    len = strnlen(buffer, size);

    if (memchr(buffer, '\n', len) == NULL && len == size - 1) {
        if (discard_remaining_input() != 0) {
            return -3;
        }
        return -2;
    }

    buffer[strcspn(buffer, "\r\n")] = '\0';
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_ROMAN_LEN];
    int value = 0;
    int rc;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a Roman numeral: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    rc = read_line(buffer, sizeof(buffer));
    if (rc == -2 || rc == -3) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    if (rc != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (roman_to_int(buffer, sizeof(buffer), &value) != 0) {
        fprintf(stderr, "Invalid Roman numeral: %s\n", buffer);
        return EXIT_FAILURE;
    }

    printf("%s = %d\n", buffer, value);
    return EXIT_SUCCESS;
}