#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MONTH_BUF_SIZE 32
#define INPUT_BUF_SIZE 64

static int has_28_days(const char *month)
{
    char normalized[MONTH_BUF_SIZE];
    size_t len;
    size_t i;

    if (month == NULL) {
        return 0;
    }

    len = strnlen(month, sizeof(normalized));
    if (len == 0 || len >= sizeof(normalized)) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[len] = '\0';

    if (strcmp(normalized, "february") == 0) {
        return 1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_BUF_SIZE];
    size_t len;

    printf("Enter a month name: ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }

    if (has_28_days(input)) {
        printf("%s has 28 days.\n", input);
    } else {
        printf("%s does not have exactly 28 days.\n", input);
    }

    return EXIT_SUCCESS;
}