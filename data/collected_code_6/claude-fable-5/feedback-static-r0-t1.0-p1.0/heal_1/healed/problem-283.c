#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 64

static bool digit_frequency_valid(const char *number, size_t max_len)
{
    int counts[10] = {0};
    size_t i;
    size_t len = 0U;

    if (number == NULL) {
        return false;
    }

    while (len < max_len && number[len] != '\0') {
        len++;
    }

    if (len == 0U || len >= max_len) {
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
    char input[MAX_INPUT];
    size_t len = 0U;

    printf("Enter a number: ");
    fflush(stdout);

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[sizeof(input) - 1U] = '\0';

    while (len < sizeof(input) && input[len] != '\0') {
        len++;
    }

    if (len > 0U && input[len - 1U] == '\n') {
        input[len - 1U] = '\0';
    }

    if (digit_frequency_valid(input, sizeof(input))) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}