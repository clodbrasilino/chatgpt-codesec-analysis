#include <regex.h>
#include <stdbool.h>
#include <stdio.h>

static int contains_only_allowed_characters(const char *text, bool *matches)
{
    regex_t regex;
    int status;

    if (text == NULL || matches == NULL) {
        return REG_BADPAT;
    }

    status = regcomp(&regex, "^[A-Za-z0-9]+$", REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return status;
    }

    status = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (status == 0) {
        *matches = true;
        return 0;
    }

    if (status == REG_NOMATCH) {
        *matches = false;
        return 0;
    }

    return status;
}

int main(int argc, const char *const argv[])
{
    bool matches = false;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return 2;
    }

    status = contains_only_allowed_characters(argv[1], &matches);
    if (status != 0) {
        fprintf(stderr, "Regex operation failed with error code %d\n", status);
        return 1;
    }

    puts(matches ? "valid" : "invalid");
    return matches ? 0 : 1;
}