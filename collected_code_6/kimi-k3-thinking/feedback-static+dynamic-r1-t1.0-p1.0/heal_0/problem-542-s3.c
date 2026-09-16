#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int replace_with_colon(char *str)
{
    regex_t regex;
    regmatch_t pmatch[1];
    size_t offset;
    int rc;
    int result;

    if (str == NULL)
    {
        return -1;
    }

    rc = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (rc != 0)
    {
        return -1;
    }

    result = 0;
    offset = 0;

    while (str[offset] != '\0')
    {
        rc = regexec(&regex, str + offset, 1, pmatch, 0);
        if (rc == 0)
        {
            str[offset + (size_t)pmatch[0].rm_so] = ':';
            offset += (size_t)pmatch[0].rm_eo;
        }
        else if (rc == REG_NOMATCH)
        {
            break;
        }
        else
        {
            result = -1;
            break;
        }
    }

    regfree(&regex);

    return result;
}

int main(void)
{
    char str[] = "Hello, World. How are you today?";
    int rc;

    printf("Original: %s\n", str);

    rc = replace_with_colon(str);
    if (rc != 0)
    {
        fprintf(stderr, "Error: string replacement failed\n");
        return EXIT_FAILURE;
    }

    printf("Modified: %s\n", str);

    return EXIT_SUCCESS;
}