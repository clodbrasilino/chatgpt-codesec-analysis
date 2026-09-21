#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int ends_with_alphanumeric(const char *str)
{
    regex_t regex;
    int ret;

    if (str == NULL) {
        return 0;
    }

    ret = regcomp(&regex, "[a-zA-Z0-9]$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[128];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
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
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    int result;

    for (i = 0; i < count; i++) {
        result = ends_with_alphanumeric(tests[i]);
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