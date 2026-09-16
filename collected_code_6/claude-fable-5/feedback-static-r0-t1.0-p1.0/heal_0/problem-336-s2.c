#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT 32

int has_28_days(const char *month)
{
    char normalized[MAX_INPUT];
    size_t i;
    size_t len;

    if (month == NULL) {
        return -1;
    }

    len = strlen(month);
    if (len == 0 || len >= MAX_INPUT) {
        return -1;
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
    char input[MAX_INPUT];
    size_t len;
    int result;

    printf("Enter a month name: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    result = has_28_days(input);

    if (result == -1) {
        fprintf(stderr, "Invalid month name input.\n");
        return EXIT_FAILURE;
    }

    if (result == 1) {
        printf("%s contains 28 days.\n", input);
    } else {
        printf("%s does not contain exactly 28 days.\n", input);
    }

    return EXIT_SUCCESS;
}