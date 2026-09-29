#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 32

static bool has_thirty_days(const char *month)
{
    static const char *const thirty_day_months[] = {
        "april", "june", "september", "november"
    };
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

    for (i = 0; i < len && i < MAX_INPUT_LEN - 1; i++) {
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[i] = '\0';

    for (i = 0; i < sizeof(thirty_day_months) / sizeof(thirty_day_months[0]); i++) {
        if (strcmp(normalized, thirty_day_months[i]) == 0) {
            return true;
        }
    }

    return false;
}

static void discard_remaining_input(void)
{
    int ch = 0;

    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }
}

int main(void)
{
    char input[MAX_INPUT_LEN];
    size_t len;

    memset(input, 0, sizeof(input));

    printf("Enter a month name: ");
    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

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