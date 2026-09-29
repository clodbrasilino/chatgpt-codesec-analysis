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

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <decimal>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_decimal_with_precision_2(argv[1])) {
        puts("Valid");
        return EXIT_SUCCESS;
    }

    puts("Invalid");
    return EXIT_FAILURE;
}