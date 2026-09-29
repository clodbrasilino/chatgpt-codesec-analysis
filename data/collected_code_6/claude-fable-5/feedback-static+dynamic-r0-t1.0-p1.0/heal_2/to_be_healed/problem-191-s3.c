#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 32

static int has_thirty_days(const char *month);
static void to_lower_string(char *dest, const char *src, size_t dest_size);

static void to_lower_string(char *dest, const char *src, size_t dest_size)
{
    size_t i;

    if (dest == NULL || src == NULL || dest_size == 0U) {
        return;
    }

    for (i = 0U; (i < dest_size - 1U) && (src[i] != '\0'); i++) {
        dest[i] = (char)tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return 0U;
    }

    for (i = 0U; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }

    return i;
}

static int has_thirty_days(const char *month)
{
    static const char *thirty_day_months[] = {
        "april",
        "june",
        "september",
        "november"
    };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lowered[MAX_INPUT_LEN];
    size_t i;
    size_t count;

    if (month == NULL) {
        return -1;
    }

    if (bounded_strlen(month, MAX_INPUT_LEN) >= MAX_INPUT_LEN) {
        return -1;
    }

    to_lower_string(lowered, month, sizeof(lowered));

    count = sizeof(thirty_day_months) / sizeof(thirty_day_months[0]);

    for (i = 0U; i < count; i++) {
        if (strcmp(lowered, thirty_day_months[i]) == 0) {
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
    char input[MAX_INPUT_LEN];
    size_t len;
    int result;

    printf("Enter a month name: ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1U] = '\0';

    len = bounded_strlen(input, sizeof(input));
    if (len > 0U && input[len - 1U] == '\n') {
        input[len - 1U] = '\0';
    } else {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    if (input[0] == '\0') {
        fprintf(stderr, "Empty input provided.\n");
        return EXIT_FAILURE;
    }

    result = has_thirty_days(input);

    if (result < 0) {
        fprintf(stderr, "Invalid month name provided.\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("%s has 30 days.\n", input);
    } else {
        printf("%s does not have 30 days.\n", input);
    }

    return EXIT_SUCCESS;
}