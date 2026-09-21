#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define MAX_STRING_LENGTH 1024

int replace_whitespace_underscore(const char *input, size_t input_max_len, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t input_len;
    size_t output_pos = 0;
    size_t i;
    const char *pattern = "[ \t\n\r\f\v]|_";
    
    if (input == NULL || output == NULL || output_size == 0 || input_max_len == 0)
    {
        return -1;
    }
    
    input_len = strnlen(input, input_max_len);
    if (input_len == 0)
    {
        output[0] = '\0';
        return 0;
    }
    
    if (input_len == input_max_len && input[input_len - 1] != '\0')
    {
        return -1;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0)
    {
        return -1;
    }
    
    i = 0;
    while (i < input_len)
    {
        ret = regexec(&regex, input + i, 1, &match, 0);
        
        if (ret == REG_NOMATCH)
        {
            size_t remaining = input_len - i;
            if (remaining >= output_size - output_pos)
            {
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + output_pos, input + i, remaining);
            output_pos += remaining;
            break;
        }
        else if (ret != 0)
        {
            regfree(&regex);
            return -1;
        }
        
        if (match.rm_so >= output_size - output_pos - 1)
        {
            regfree(&regex);
            return -1;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + output_pos, input + i, match.rm_so);
        output_pos += match.rm_so;
        
        if (output_pos >= output_size)
        {
            regfree(&regex);
            return -1;
        }
        
        if (input[i + match.rm_so] == '_')
        {
            output[output_pos] = ' ';
        }
        else
        {
            output[output_pos] = '_';
        }
        output_pos++;
        
        i += match.rm_eo;
    }
    
    if (output_pos >= output_size)
    {
        regfree(&regex);
        return -1;
    }
    
    output[output_pos] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_STRING_LENGTH];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[MAX_STRING_LENGTH * 2];
    int result;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    result = replace_whitespace_underscore(input, sizeof(input), output, sizeof(output));
    if (result != 0)
    {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }
    
    printf("Original: %s\n", input);
    printf("Modified: %s\n", output);
    
    return 0;
}