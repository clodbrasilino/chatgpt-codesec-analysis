#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 32

static size_t bounded_length(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            return i;
        }
    }

    return max_len;
}

static bool normalize_month(const char *month, char *normalized, size_t normalized_size)
{
    size_t len;
    size_t i;

    if (month == NULL || normalized == NULL || normalized_size == 0) {
        return false;
    }

    len = bounded_length(month, normalized_size);
    if (len == 0 || len >= normalized_size) {
        return false;
    }

    for (i = 0; i < len; i++) {
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[len] = '\0';

    return true;
}

static bool has_thirty_days(const char *month)
{
    static const char *thirty_day_months[] = {
        "april", "june", "september", "november"
    };
    char normalized[MAX_INPUT_LEN];
    size_t i;

    if (!normalize_month(month, normalized, sizeof(normalized))) {
        return false;
    }

    for (i = 0; i < sizeof(thirty_day_months) / sizeof(thirty_day_months[0]); i++) {
        if (strcmp(normalized, thirty_day_months[i]) == 0) {
            return true;
        }
    }

    return false;
}

static bool is_valid_month(const char *month)
{
    static const char *all_months[] = {
        "january", "february", "march", "april", "may", "june",
        "july", "august", "september", "october", "november", "december"
    };
    char normalized[MAX_INPUT_LEN];
    size_t i;

    if (!normalize_month(month, normalized, sizeof(normalized))) {
        return false;
    }

    for (i = 0; i < sizeof(all_months) / sizeof(all_months[0]); i++) {
        if (strcmp(normalized, all_months[i]) == 0) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char input[MAX_INPUT_LEN];
    size_t len;

    printf("Enter a month name: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    input[sizeof(input) - 1] = '\0';

    len = bounded_length(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    if (!is_valid_month(input)) {
        fprintf(stderr, "Invalid month name: %s\n", input);
        return 1;
    }

    if (has_thirty_days(input)) {
        printf("%s has 30 days.\n", input);
    } else {
        printf("%s does not have 30 days.\n", input);
    }

    return 0;
}