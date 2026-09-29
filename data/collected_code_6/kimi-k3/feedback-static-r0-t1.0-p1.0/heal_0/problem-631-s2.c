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
    
    input_len = strlen(input);
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
            if (output_pos + (input_len - i) + 1 > output_size)
            {
                regfree(&regex);
                return -1;
            }
            memcpy(output + output_pos, input + i, input_len - i);
            output_pos += input_len - i;
            break;
        }
        else if (ret != 0)
        {
            regfree(&regex);
            return -1;
        }
        
        if (output_pos + match.rm_so + 2 > output_size)
        {
            regfree(&regex);
            return -1;
        }
        
        memcpy(output + output_pos, input + i, match.rm_so);
        output_pos += match.rm_so;
        
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
    
    output[output_pos] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    char input[MAX_STRING_LENGTH];
    char output[MAX_STRING_LENGTH * 2];
    int result;
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
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