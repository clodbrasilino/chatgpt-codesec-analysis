#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 32

static bool has_thirty_days(const char *month)
{
    static const char *thirty_day_months[] = {
        "april", "june", "september", "november"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[MAX_INPUT_LEN];
    size_t len;
    size_t i;

    if (month == NULL) {
        return false;
    }

    len = strnlen(month, MAX_INPUT_LEN);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        return false;
    }

    for (i = 0; i < len; i++) {
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[len] = '\0';

    for (i = 0; i < sizeof(thirty_day_months) / sizeof(thirty_day_months[0]); i++) {
        if (strcmp(normalized, thirty_day_months[i]) == 0) {
            return true;
        }
    }

    return false;
}

static void discard_remaining_input(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    size_t len;

    printf("Enter a month name: ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        discard_remaining_input();
    }

    if (input[0] == '\0') {
        fprintf(stderr, "No month name provided.\n");
        return EXIT_FAILURE;
    }

    if (has_thirty_days(input)) {
        printf("%s has 30 days.\n", input);
    } else {
        printf("%s does not have 30 days.\n", input);
    }

    return EXIT_SUCCESS;
}