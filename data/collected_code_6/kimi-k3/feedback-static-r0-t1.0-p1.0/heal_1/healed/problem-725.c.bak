#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100
#define MAX_MATCH_LEN 256

int extract_quoted_values(const char *input, char matches[][MAX_MATCH_LEN], int max_matches)
{
    regex_t regex;
    regmatch_t match[2];
    const char *cursor;
    int count;
    int ret;

    if (input == NULL || matches == NULL || max_matches <= 0)
    {
        return -1;
    }

    ret = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (ret != 0)
    {
        return -1;
    }

    cursor = input;
    count = 0;

    while (count < max_matches)
    {
        size_t len;

        ret = regexec(&regex, cursor, 2, match, 0);
        if (ret == REG_NOMATCH)
        {
            break;
        }
        else if (ret != 0)
        {
            regfree(&regex);
            return -1;
        }

        if (match[1].rm_so == -1 || match[1].rm_eo == -1)
        {
            break;
        }

        len = (size_t)(match[1].rm_eo - match[1].rm_so);
        if (len >= MAX_MATCH_LEN)
        {
            len = MAX_MATCH_LEN - 1;
        }

        memcpy(matches[count], cursor + match[1].rm_so, len);
        matches[count][len] = '\0';
        count++;

        if (match[0].rm_eo == 0)
        {
            break;
        }

        cursor += match[0].rm_eo;
    }

    regfree(&regex);
    return count;
}

int main(void)
{
    const char *input = "The quick \"brown fox\" jumps over the \"lazy dog\" and \"runs away\"";
    char matches[MAX_MATCHES][MAX_MATCH_LEN];
    int count;
    int i;

    count = extract_quoted_values(input, matches, MAX_MATCHES);
    if (count < 0)
    {
        fprintf(stderr, "Error extracting quoted values\n");
        return EXIT_FAILURE;
    }

    printf("Found %d quoted value(s):\n", count);
    for (i = 0; i < count; i++)
    {
        printf("[%d]: %s\n", i, matches[i]);
    }

    return EXIT_SUCCESS;
}