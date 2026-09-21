#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 32U

static int has_thirty_days(const char *month);
static void to_lower_string(char *dest, const char *src, size_t dest_size);
static int read_line(char *buffer, size_t buffer_size);

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

    if (strnlen(month, sizeof(lowered)) >= sizeof(lowered)) {
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

static int read_line(char *buffer, size_t buffer_size)
{
    size_t len;

    if (buffer == NULL || buffer_size == 0U) {
        return -1;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return -1;
    }

    buffer[buffer_size - 1U] = '\0';

    len = strnlen(buffer, buffer_size);
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    } else {
        int ch;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    int result;

    printf("Enter a month name: ");

    if (read_line(input, sizeof(input)) != 0) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
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