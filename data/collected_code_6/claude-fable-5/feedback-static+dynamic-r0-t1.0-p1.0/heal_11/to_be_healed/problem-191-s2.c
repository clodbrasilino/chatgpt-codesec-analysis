#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_INPUT_LEN 32
#define MAX_DISCARD_ITERATIONS 4096

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
        if (!isalpha((unsigned char)month[i])) {
            return false;
        }
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[len] = '\0';

    return true;
}

static bool has_thirty_days(const char *month)
{
    static const char *const thirty_day_months[] = {
        "april", "june", "september", "november"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[MAX_INPUT_LEN] = {0};
    size_t i;

    if (!normalize_month(month, normalized, sizeof(normalized))) {
        return false;
    }

    for (i = 0; i < sizeof(thirty_day_months) / sizeof(thirty_day_months[0]); i++) {
        if (strncmp(normalized, thirty_day_months[i], sizeof(normalized)) == 0) {
            return true;
        }
    }

    return false;
}

static bool is_valid_month(const char *month)
{
    static const char *const all_months[] = {
        "january", "february", "march", "april", "may", "june",
        "july", "august", "september", "october", "november", "december"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[MAX_INPUT_LEN] = {0};
    size_t i;

    if (!normalize_month(month, normalized, sizeof(normalized))) {
        return false;
    }

    for (i = 0; i < sizeof(all_months) / sizeof(all_months[0]); i++) {
        if (strncmp(normalized, all_months[i], sizeof(normalized)) == 0) {
            return true;
        }
    }

    return false;
}

static void discard_remaining_input(void)
{
    int ch;
    size_t guard = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < MAX_DISCARD_ITERATIONS);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN] = {0};
    size_t len;

    printf("Enter a month name: ");
    if (fflush(stdout) != 0) {
        return 1;
    }

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    input[sizeof(input) - 1] = '\0';

    len = bounded_length(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        discard_remaining_input();
    }

    if (!is_valid_month(input)) {
        fprintf(stderr, "Invalid month name: %.31s\n", input);
        return 1;
    }

    if (has_thirty_days(input)) {
        printf("%.31s has 30 days.\n", input);
    } else {
        printf("%.31s does not have 30 days.\n", input);
    }

    return 0;
}