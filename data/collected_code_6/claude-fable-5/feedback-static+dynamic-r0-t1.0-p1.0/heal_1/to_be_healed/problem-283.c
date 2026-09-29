#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 64

bool digit_frequency_valid(const char *number)
{
    int counts[10] = {0};
    size_t i;
    size_t len;

    if (number == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(number);
    if (len == 0U) {
        return false;
    }

    for (i = 0U; i < len; i++) {
        if (!isdigit((unsigned char)number[i])) {
            return false;
        }
        counts[number[i] - '0']++;
    }

    for (i = 0U; i < 10U; i++) {
        if (counts[i] > (int)i) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT];
    size_t len;

    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0U && input[len - 1U] == '\n') {
        input[len - 1U] = '\0';
    }

    if (digit_frequency_valid(input)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}