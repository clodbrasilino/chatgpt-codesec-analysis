#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define MAX_MATCHES 100
#define MAX_MATCH_LEN 256

static int extract_quoted_values(const char *input, char matches[][MAX_MATCH_LEN], size_t max_matches)
{
    regex_t regex;
    regmatch_t match[2];
    const char *cursor;
    size_t count;
    int ret;

    if (input == NULL || matches == NULL || max_matches == 0 || max_matches > MAX_MATCHES)
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

    /* Possible weaknesses found:
     *  outer condition: count<max_matches
     */
    while (count < max_matches)
    {
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

        {
            size_t len = (size_t)(match[1].rm_eo - match[1].rm_so);
            if (len >= MAX_MATCH_LEN)
            {
                len = MAX_MATCH_LEN - 1;
            }

            if (len > 0)
            {
                /* Possible weaknesses found:
                 *  opposite inner condition: count>=max_matches
                 *  Opposite inner 'if' condition leads to a dead code block. [oppositeInnerCondition]
                 */
                if (count >= max_matches)
                {
                    regfree(&regex);
                    return -1;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(matches[count], cursor + match[1].rm_so, len);
                matches[count][len] = '\0';
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
    return (int)count;
}

int main(void)
{
    const char *input = "The quick \"brown fox\" jumps over the \"lazy dog\" and \"runs away\"";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char (*matches)[MAX_MATCH_LEN] = NULL;
    int count;
    int i;

    matches = calloc(MAX_MATCHES, sizeof(*matches));
    if (matches == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    count = extract_quoted_values(input, matches, MAX_MATCHES);
    if (count < 0)
    {
        fprintf(stderr, "Error extracting quoted values\n");
        free(matches);
        return EXIT_FAILURE;
    }

    printf("Found %d quoted value(s):\n", count);
    for (i = 0; i < count && i < MAX_MATCHES; i++)
    {
        printf("[%d]: %s\n", i, matches[i]);
    }

    free(matches);
    return EXIT_SUCCESS;
}