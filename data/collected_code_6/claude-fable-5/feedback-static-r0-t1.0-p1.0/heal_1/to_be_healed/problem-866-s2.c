#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 32

static bool has_31_days(const char *month)
{
    static const char *months_31[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lowered[MAX_INPUT_LEN];
    size_t len;
    size_t i;

    if (month == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(month);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        return false;
    }

    for (i = 0; i < len; i++) {
        lowered[i] = (char)tolower((unsigned char)month[i]);
    }
    lowered[len] = '\0';

    for (i = 0; i < sizeof(months_31) / sizeof(months_31[0]); i++) {
        if (strcmp(lowered, months_31[i]) == 0) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    size_t len;

    printf("Enter a month name: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (has_31_days(input)) {
        printf("%s has 31 days.\n", input);
    } else {
        printf("%s does not have 31 days.\n", input);
    }

    return 0;
}