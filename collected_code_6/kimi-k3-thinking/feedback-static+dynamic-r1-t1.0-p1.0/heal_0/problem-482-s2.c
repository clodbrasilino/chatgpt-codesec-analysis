#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int find_sequences(const char *str)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char errbuf[256];
    int ret;

    if (str == NULL)
    {
        fprintf(stderr, "Input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (ret != 0)
    {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Could not compile regex: %s\n", errbuf);
        return -1;
    }

    cursor = str;
    while (*cursor != '\0')
    {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH)
        {
            break;
        }
        if (ret != 0)
        {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex execution failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        printf("Found sequence: %.*s\n",
               (int)(match.rm_eo - match.rm_so),
               cursor + match.rm_so);

        cursor += match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "Hello World, this Is a Test String with Sequences Like ABCDef and Ghi.";

    if (find_sequences(input) != 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}