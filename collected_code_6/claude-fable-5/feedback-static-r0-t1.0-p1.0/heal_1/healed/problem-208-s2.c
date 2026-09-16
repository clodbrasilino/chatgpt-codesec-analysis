#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int is_decimal_with_precision_two(const char *input);

int is_decimal_with_precision_two(const char *input)
{
    regex_t regex;
    int result;

    if (input == NULL) {
        return 0;
    }

    result = regcomp(&regex, "^[+-]?[0-9]+\\.[0-9]{2}$", REG_EXTENDED | REG_NOSUB);
    if (result != 0) {
        return -1;
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
        "+10.00",
        "123.456",
        "123.4",
        "abc.12",
        "123",
        ".45"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int status = is_decimal_with_precision_two(tests[i]);
        if (status < 0) {
            if (fprintf(stderr, "Regex compilation failed\n") < 0) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
        if (printf("%s -> %s\n", tests[i], status == 1 ? "valid" : "invalid") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}