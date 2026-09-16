#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t result_len;
    size_t input_len;
    size_t offset;
    int ret;

    if (input == NULL)
    {
        return NULL;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0)
    {
        return NULL;
    }

    input_len = strlen(input);
    result = malloc(input_len + 1);
    if (result == NULL)
    {
        regfree(&regex);
        return NULL;
    }

    result_len = 0;
    offset = 0;

    while (offset < input_len)
    {
        ret = regexec(&regex, input + offset, 1, &match, 0);

        if (ret == 0)
        {
            if (match.rm_so > 0)
            {
                memcpy(result + result_len, input + offset, (size_t)match.rm_so);
                result_len += (size_t)match.rm_so;
            }
            offset += (size_t)match.rm_eo;
        }
        else if (ret == REG_NOMATCH)
        {
            memcpy(result + result_len, input + offset, input_len - offset);
            result_len += input_len - offset;
            break;
        }
        else
        {
            free(result);
            regfree(&regex);
            return NULL;
        }
    }

    result[result_len] = '\0';
    regfree(&regex);

    return result;
}

int main(void)
{
    const char *input = "Hello World ABCdef GHIjkl MNO";
    char *result = remove_lowercase_substrings(input);

    if (result == NULL)
    {
        fprintf(stderr, "Error: failed to process the input string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Result:   %s\n", result);

    free(result);

    return EXIT_SUCCESS;
}