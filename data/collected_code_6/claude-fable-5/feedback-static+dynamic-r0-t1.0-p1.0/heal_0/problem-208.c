#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int is_decimal_precision_two(const char *input);

int is_decimal_precision_two(const char *input)
{
    regex_t regex;
    int result;
    const char *pattern = "^[+-]?[0-9]+\\.[0-9]{2}$";

    if (input == NULL) {
        return 0;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return 0;
    }

    result = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);

    if (result == 0) {
        return 1;
    }

    return 0;
}

int main(void)
{
    const char *tests[] = {
        "123.45",
        "-0.99",
        "+3.14",
        "123.456",
        "123",
        "abc.12",
        "12.3",
        ".45"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (is_decimal_precision_two(tests[i]) == 1) {
            if (printf("%s: valid\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("%s: invalid\n", tests[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}