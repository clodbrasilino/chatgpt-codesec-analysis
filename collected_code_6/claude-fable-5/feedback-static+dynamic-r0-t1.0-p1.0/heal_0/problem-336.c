#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int has_28_days(const char *month)
{
    char normalized[32];
    size_t len;
    size_t i;

    if (month == NULL) {
        return 0;
    }

    len = strlen(month);
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
    char input[64];
    size_t len;

    printf("Enter a month name: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (has_28_days(input)) {
        printf("%s has 28 days.\n", input);
    } else {
        printf("%s does not have exactly 28 days.\n", input);
    }

    return EXIT_SUCCESS;
}