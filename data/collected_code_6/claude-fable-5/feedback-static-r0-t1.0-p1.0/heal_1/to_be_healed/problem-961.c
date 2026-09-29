#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 64

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

static int roman_to_int(const char *roman, int *result)
{
    size_t len;
    size_t i;
    int total;

    if (roman == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(roman);
    if (len == 0U) {
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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    int value;
    size_t len;

    printf("Enter a Roman numeral: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    } else {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    if (roman_to_int(buffer, &value) != 0) {
        fprintf(stderr, "Invalid Roman numeral: %s\n", buffer);
        return EXIT_FAILURE;
    }

    printf("%s = %d\n", buffer, value);
    return EXIT_SUCCESS;
}