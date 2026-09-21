#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_STRING_LENGTH 1024

int replace_whitespace_underscore(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t input_len;
    size_t output_pos = 0;
    size_t i;
    const char *pattern = "[ \t\n\r\f\v]|_";
    
    if (input == NULL || output == NULL || output_size == 0)
    {
        return -1;
    }
    
    input_len = strnlen(input, MAX_STRING_LENGTH);
    if (input_len == 0)
    {
        output[0] = '\0';
        return 0;
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
            /* Possible weaknesses found:
             *  Assuming that condition 'output_pos+remaining+1>output_size' is not redundant
             */
            if (output_pos + remaining + 1 > output_size)
            {
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             *  Condition 'output_pos+remaining>output_size' is always false [knownConditionTrueFalse]
             *  Condition 'output_pos+remaining>output_size' is always false
             */
            if (output_pos + remaining > output_size)
            {
                regfree(&regex);
                return -1;
            }
            memmove(output + output_pos, input + i, remaining);
            output_pos += remaining;
            break;
        }
        else if (ret != 0)
        {
            regfree(&regex);
            return -1;
        }
        
        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_so > match.rm_eo)
        {
            regfree(&regex);
            return -1;
        }
        
        size_t prefix_len = (size_t)match.rm_so;
        
        /* Possible weaknesses found:
         *  Assuming that condition 'output_pos+prefix_len+2>output_size' is not redundant
         */
        if (output_pos + prefix_len + 2 > output_size)
        {
            regfree(&regex);
            return -1;
        }
        
        if (prefix_len > 0)
        {
            /* Possible weaknesses found:
             *  Condition 'output_pos+prefix_len>output_size' is always false
             *  Condition 'output_pos+prefix_len>output_size' is always false [knownConditionTrueFalse]
             */
            if (output_pos + prefix_len > output_size)
            {
                regfree(&regex);
                return -1;
            }
            memmove(output + output_pos, input + i, prefix_len);
            output_pos += prefix_len;
        }
        
        if (i + match.rm_so >= input_len)
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
        
        i += (size_t)match.rm_eo;
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
    char input[MAX_STRING_LENGTH + 1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[MAX_STRING_LENGTH * 2 + 1];
    int result;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
    }
    
    result = replace_whitespace_underscore(input, output, sizeof(output));
    if (result != 0)
    {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }
    
    printf("Original: %s\n", input);
    printf("Modified: %s\n", output);
    
    return 0;
}