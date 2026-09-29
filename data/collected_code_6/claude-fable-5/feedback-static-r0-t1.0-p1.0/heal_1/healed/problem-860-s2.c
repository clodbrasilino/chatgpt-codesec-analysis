#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static void print_regex_error(int errcode, const regex_t *regex)
{
    size_t needed = regerror(errcode, regex, NULL, 0);
    char *errbuf = malloc(needed);

    if (errbuf != NULL) {
        regerror(errcode, regex, errbuf, needed);
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        free(errbuf);
    } else {
        fprintf(stderr, "Regex compilation failed and error buffer allocation failed\n");
    }
}

int ends_with_alphanumeric(const char *str)
{
    regex_t regex;
    int ret;

    if (str == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "[a-zA-Z0-9]$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        print_regex_error(ret, &regex);
        return -1;
    }

    ret = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        fprintf(stderr, "Regex execution failed\n");
        return -1;
    }
}

int main(void)
{
    const char *tests[] = {
        "hello123",
        "world!",
        "test_string9",
        "endswithspace ",
        "abcXYZ",
        ""
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        int result = ends_with_alphanumeric(tests[i]);
        if (result == 1) {
            printf("\"%s\" ends with an alphanumeric character.\n", tests[i]);
        } else if (result == 0) {
            printf("\"%s\" does not end with an alphanumeric character.\n", tests[i]);
        } else {
            fprintf(stderr, "Error processing \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}