#include <stdio.h>
#include <regex.h>
#include <string.h>

static int starts_and_ends_with_same_character(const char *string, int *result)
{
    regex_t regex;
    const char *pattern = "^(.)(.*\\1)?$";
    int status;

    if (string == NULL || result == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (status == 0) {
        *result = 1;
        return 0;
    }

    if (status == REG_NOMATCH) {
        *result = 0;
        return 0;
    }

    return -1;
}

int main(void)
{
    char input[1024];
    int result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (starts_and_ends_with_same_character(input, &result) != 0) {
        return 1;
    }

    printf("%s\n", result ? "Yes" : "No");
    return 0;
}