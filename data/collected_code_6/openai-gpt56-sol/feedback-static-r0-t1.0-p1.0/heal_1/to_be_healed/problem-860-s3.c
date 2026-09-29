#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

static int ends_with_alphanumeric(const char *string, bool *result)
{
    regex_t regex;
    int status;

    if (string == NULL || result == NULL) {
        return -1;
    }

    status = regcomp(&regex, "[[:alnum:]]+$", REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    if (status == 0) {
        *result = true;
        return 0;
    }

    if (status == REG_NOMATCH) {
        *result = false;
        return 0;
    }

    return -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    bool result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    if (ends_with_alphanumeric(input, &result) != 0) {
        return 1;
    }

    puts(result ? "true" : "false");
    return 0;
}