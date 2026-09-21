#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_uppercase_substrings(const char *input, size_t max_len)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t result_len;
    size_t input_len;
    size_t offset;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, max_len);
    if (input_len == max_len && input[input_len] != '\0') {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    cursor = input;
    offset = 0;
    result_len = 0;

    while ((ret = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t prefix_len = (size_t)match.rm_so;
        
        if (prefix_len > 0) {
            if (prefix_len > input_len - result_len) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            memcpy(result + result_len, cursor, prefix_len);
        }
        
        result_len += prefix_len;
        cursor += match.rm_eo;
        offset += (size_t)match.rm_eo;
        
        if (offset > input_len) {
            break;
        }
    }

    if (ret != REG_NOMATCH && ret != 0) {
        regfree(&regex);
        free(result);
        return NULL;
    }

    {
        size_t remaining = input_len - offset;
        size_t tail_len = strnlen(cursor, remaining + 1);
        
        if (tail_len > remaining) {
            tail_len = remaining;
        }
        
        if (tail_len > 0) {
            if (tail_len > input_len - result_len) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            memcpy(result + result_len, cursor, tail_len);
        }
        
        result[result_len + tail_len] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *input = "HelloWORLDThisISATestLOWERCASEonly";
    char *output = remove_uppercase_substrings(input, 1024);

    if (output == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);
    return EXIT_SUCCESS;
}