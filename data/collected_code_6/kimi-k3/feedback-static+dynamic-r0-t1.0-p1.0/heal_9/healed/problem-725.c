#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define MAX_MATCHES 100
#define MAX_MATCH_LEN 256

int extract_quoted_values(const char *input, char matches[][MAX_MATCH_LEN], int max_matches)
{
    regex_t regex;
    regmatch_t match[2];
    const char *cursor;
    int count;
    int ret;
    char errbuf[256];

    if (input == NULL || matches == NULL || max_matches <= 0)
    {
        return -1;
    }

    ret = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (ret != 0)
    {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return -1;
    }

    cursor = input;
    count = 0;

    while (count < max_matches && cursor != NULL && *cursor != '\0')
    {
        ret = regexec(&regex, cursor, 2, match, 0);
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

        if (match[1].rm_so == -1 || match[1].rm_eo == -1 || 
            match[0].rm_so == -1 || match[0].rm_eo == -1)
        {
            break;
        }

        {
            size_t len = (size_t)(match[1].rm_eo - match[1].rm_so);
            size_t max_len = MAX_MATCH_LEN - 1;
            
            if (len > max_len)
            {
                len = max_len;
            }

            if (len > 0)
            {
                size_t copy_len = len;
                if (copy_len > max_len)
                {
                    copy_len = max_len;
                }
                memcpy(matches[count], cursor + match[1].rm_so, copy_len);
                matches[count][copy_len] = '\0';
            }
            else
            {
                matches[count][0] = '\0';
            }
        }

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

    memset(matches, 0, sizeof(matches));

    count = extract_quoted_values(input, matches, MAX_MATCHES);
    if (count < 0)
    {
        fprintf(stderr, "Error extracting quoted values\n");
        return EXIT_FAILURE;
    }

    if (count > MAX_MATCHES)
    {
        count = MAX_MATCHES;
    }

    printf("Found %d quoted value(s):\n", count);
    for (i = 0; i < count && i < MAX_MATCHES; i++)
    {
        if (matches[i][0] != '\0')
        {
            printf("[%d]: %s\n", i, matches[i]);
        }
        else
        {
            printf("[%d]: (empty)\n", i);
        }
    }

    return EXIT_SUCCESS;
}