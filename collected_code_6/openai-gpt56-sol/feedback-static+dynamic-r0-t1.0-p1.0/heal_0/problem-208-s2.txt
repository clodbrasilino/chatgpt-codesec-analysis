#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_decimal_with_precision_2(const char *value)
{
    regex_t regex;
    const char *pattern = "^[+-]?([0-9]+\\.[0-9]{2})$";
    int compile_result;
    int match_result;

    if (value == NULL) {
        return false;
    }

    compile_result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (compile_result != 0) {
        return false;
    }

    match_result = regexec(&regex, value, 0, NULL, 0);
    regfree(&regex);

    return match_result == 0;
}

int main(int argc, char *argv[])
{
    bool valid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <decimal>\n", argv[0]);
        return EXIT_FAILURE;
    }

    valid = is_decimal_with_precision_2(argv[1]);
    printf("%s\n", valid ? "valid" : "invalid");

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}