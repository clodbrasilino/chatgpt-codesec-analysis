#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

static bool contains_only_allowed_characters(const char *string)
{
    static const char pattern[] = "^[A-Za-z0-9]+$";
    regex_t regex;
    int status;

    if (string == NULL) {
        return false;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return false;
    }

    status = regexec(&regex, string, 0, NULL, 0);
    regfree(&regex);

    return status == 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
        }
        return 1;
    }

    size_t length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (input[length] != '\0') {
        return 1;
    }

    puts(contains_only_allowed_characters(input) ? "valid" : "invalid");
    return 0;
}