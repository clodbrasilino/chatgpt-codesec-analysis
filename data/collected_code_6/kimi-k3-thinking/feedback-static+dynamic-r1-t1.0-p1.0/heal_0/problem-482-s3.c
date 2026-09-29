#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_sequences(const char *str)
{
    regex_t regex;
    regmatch_t match;
    char errbuf[128];
    size_t offset = 0;
    size_t len;
    int ret;
    int count = 0;

    if (str == NULL)
    {
        fprintf(stderr, "Invalid input: string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (ret != 0)
    {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Could not compile regex: %s\n", errbuf);
        return -1;
    }

    len = strlen(str);

    while (offset <= len)
    {
        ret = regexec(&regex, str + offset, 1, &match, 0);

        if (ret == REG_NOMATCH)
        {
            break;
        }
        else if (ret != 0)
        {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex execution failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so)
        {
            break;
        }

        printf("Found sequence: %.*s at position %lld\n",
               (int)(match.rm_eo - match.rm_so),
               str + offset + match.rm_so,
               (long long)(offset + (size_t)match.rm_so));

        count++;
        offset += (size_t)match.rm_eo;
    }

    regfree(&regex);
    return count;
}

int main(void)
{
    const char *input = "Hello World this Is a Test String With some Sequences Like Abc and Xyz";
    int result;

    printf("Input string: %s\n", input);

    result = find_sequences(input);

    if (result < 0)
    {
        fprintf(stderr, "Failed to find sequences\n");
        return EXIT_FAILURE;
    }

    printf("Total sequences found: %d\n", result);

    return EXIT_SUCCESS;
}