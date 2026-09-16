#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int replace_chars_with_colon(char *str)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t offset;
    size_t len;

    if (str == NULL)
    {
        return -1;
    }

    ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0)
    {
        return -1;
    }

    len = strlen(str);
    offset = 0;

    while (offset < len)
    {
        ret = regexec(&regex, str + offset, 1, &match, 0);
        if (ret == REG_NOMATCH)
        {
            break;
        }
        if (ret != 0)
        {
            regfree(&regex);
            return -1;
        }
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so)
        {
            regfree(&regex);
            return -1;
        }
        str[offset + (size_t)match.rm_so] = ':';
        offset += (size_t)match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char str[] = "Hello, world. This is a test, with spaces. And dots, too.";

    if (replace_chars_with_colon(str) != 0)
    {
        fprintf(stderr, "Error: failed to process the string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", str);

    return EXIT_SUCCESS;
}