#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static void report_regex_error(int errcode, const regex_t *regex)
{
    size_t needed;
    char *errbuf;

    needed = regerror(errcode, regex, NULL, 0);
    if (needed == 0)
    {
        fprintf(stderr, "unknown regex error (code %d)\n", errcode);
        return;
    }

    errbuf = malloc(needed);
    if (errbuf == NULL)
    {
        fprintf(stderr, "regex error (code %d); could not allocate message buffer\n",
                errcode);
        return;
    }

    regerror(errcode, regex, errbuf, needed);
    fprintf(stderr, "%s\n", errbuf);
    free(errbuf);
}

int find_sequences(const char *str)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int ret;
    int status;

    if (str == NULL)
    {
        fprintf(stderr, "Input string is NULL\n");
        return -1;
    }

    ret = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (ret != 0)
    {
        fprintf(stderr, "Could not compile regex: ");
        report_regex_error(ret, &regex);
        return -1;
    }

    status = 0;
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
            fprintf(stderr, "Regex execution failed: ");
            report_regex_error(ret, &regex);
            status = -1;
            break;
        }

        if ((long)match.rm_so < 0 || (long)match.rm_eo < (long)match.rm_so)
        {
            fprintf(stderr, "Invalid match offsets returned by regex engine\n");
            status = -1;
            break;
        }

        printf("Found sequence: %.*s\n",
               (int)(match.rm_eo - match.rm_so),
               cursor + match.rm_so);

        cursor += (match.rm_eo > 0) ? match.rm_eo : 1;
    }

    regfree(&regex);
    return status;
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