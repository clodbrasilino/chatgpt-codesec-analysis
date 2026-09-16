#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int match_a_anything_b(const char *text)
{
    regex_t re;
    int status;

    if (text == NULL) {
        return 0;
    }

    status = regcomp(&re, "^a.*b$", REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        return -1;
    }

    status = regexec(&re, text, 0, NULL, 0);
    regfree(&re);

    if (status == 0) {
        return 1;
    }
    if (status == REG_NOMATCH) {
        return 0;
    }
    return -1;
}

int main(void)
{
    const char *tests[] = { "ab", "axyzb", "a123b", "abc", "b", "a", "" };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    size_t i;
    int result;

    for (i = 0; i < count; i++) {
        result = match_a_anything_b(tests[i]);
        if (result < 0) {
            fprintf(stderr, "regex error while matching \"%s\"\n", tests[i]);
            return EXIT_FAILURE;
        }
        printf("\"%s\" -> %s\n", tests[i], result ? "match" : "no match");
    }

    return EXIT_SUCCESS;
}