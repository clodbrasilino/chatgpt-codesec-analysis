#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_pattern(const char *text)
{
    regex_t regex;
    int ret;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error_buffer[256];

    ret = regcomp(&regex, "a.*b$", REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex compilation failed: %s\n", error_buffer);
        return -1;
    }

    ret = regexec(&regex, text, 0, NULL, 0);
    regfree(&regex);

    if (ret == 0) {
        return 1;
    } else if (ret == REG_NOMATCH) {
        return 0;
    } else {
        regerror(ret, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "Regex execution failed: %s\n", error_buffer);
        return -1;
    }
}

int main(void)
{
    const char *tests[] = {
        "acb",
        "ab",
        "axyzb",
        "a123b",
        "bca",
        "abc",
        "b",
        "a"
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    int result;

    for (i = 0; i < count; i++) {
        result = match_pattern(tests[i]);
        if (result < 0) {
            return EXIT_FAILURE;
        }
        if (result == 1) {
            printf("\"%s\" matches\n", tests[i]);
        } else {
            printf("\"%s\" does not match\n", tests[i]);
        }
    }

    return EXIT_SUCCESS;
}