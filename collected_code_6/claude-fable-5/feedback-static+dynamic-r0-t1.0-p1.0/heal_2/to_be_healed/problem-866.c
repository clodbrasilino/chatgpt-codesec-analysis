#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_MONTH_LEN 32

static int has_31_days(const char *month)
{
    static const char *months_31[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[MAX_MONTH_LEN];
    size_t i;
    size_t len;

    if (month == NULL) {
        return -1;
    }

    len = strnlen(month, MAX_MONTH_LEN);
    if (len == 0 || len >= MAX_MONTH_LEN) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[len] = '\0';

    for (i = 0; i < sizeof(months_31) / sizeof(months_31[0]); i++) {
        if (strcmp(normalized, months_31[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_MONTH_LEN];
    int result;

    printf("Enter a month name: ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\r\n")] = '\0';

    result = has_31_days(input);

    if (result == -1) {
        fprintf(stderr, "Invalid month name provided\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("%s has 31 days\n", input);
    } else {
        printf("%s does not have 31 days\n", input);
    }

    return EXIT_SUCCESS;
}