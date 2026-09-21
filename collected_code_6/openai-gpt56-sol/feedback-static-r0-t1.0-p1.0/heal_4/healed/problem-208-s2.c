#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_decimal_with_precision_2(const char *value)
{
    static const char pattern[] = "^[+-]?[0-9]+\\.[0-9]{2}$";
    regex_t regex;

    if (value == NULL) {
        return false;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return false;
    }

    const int result = regexec(&regex, value, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

int main(int argc, const char *const argv[])
{
    if (argc != 2) {
        const char *program_name = "program";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s <decimal>\n", program_name);
        return EXIT_FAILURE;
    }

    const bool valid = is_decimal_with_precision_2(argv[1]);
    puts(valid ? "valid" : "invalid");

    return valid ? EXIT_SUCCESS : EXIT_FAILURE;
}