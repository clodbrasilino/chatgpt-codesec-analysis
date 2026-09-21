#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ROMAN_LEN 64

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

    if (s == NULL || result == NULL) {
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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_ROMAN_LEN];
    int value = 0;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a Roman numeral: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\r\n")] = '\0';

    if (roman_to_int(buffer, sizeof(buffer), &value) != 0) {
        fprintf(stderr, "Invalid Roman numeral: %s\n", buffer);
        return EXIT_FAILURE;
    }

    printf("%s = %d\n", buffer, value);
    return EXIT_SUCCESS;
}