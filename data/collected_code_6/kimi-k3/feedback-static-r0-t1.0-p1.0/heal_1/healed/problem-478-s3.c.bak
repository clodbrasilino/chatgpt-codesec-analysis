#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

static bool is_all_lowercase(const char *start, size_t len)
{
    size_t i;
    
    if (len == 0) {
        return false;
    }
    
    for (i = 0; i < len; i++) {
        if (!islower((unsigned char)start[i])) {
            return false;
        }
    }
    
    return true;
}

char *remove_lowercase_substrings(const char *input)
{
    size_t input_len;
    size_t i;
    size_t j;
    size_t result_idx;
    char *result;
    
    if (input == NULL) {
        return NULL;
    }
    
    input_len = strlen(input);
    result = malloc(input_len + 1);
    
    if (result == NULL) {
        return NULL;
    }
    
    result_idx = 0;
    i = 0;
    
    while (i < input_len) {
        if (islower((unsigned char)input[i])) {
            j = i;
            while (j < input_len && islower((unsigned char)input[j])) {
                j++;
            }
            if (!is_all_lowercase(input + i, j - i)) {
                memcpy(result + result_idx, input + i, j - i);
                result_idx += (j - i);
            }
            i = j;
        } else {
            result[result_idx] = input[i];
            result_idx++;
            i++;
        }
    }
    
    result[result_idx] = '\0';
    
    return result;
}

int main(void)
{
    char test1[] = "HelloWORLDthisISaTEST";
    char test2[] = "abcDEFghi";
    char test3[] = "ALLUPPERCASE";
    char test4[] = "alllowercase";
    const char test5[] = "";
    char *result;
    
    result = remove_lowercase_substrings(test1);
    if (result != NULL) {
        printf("Input: %s\n", test1);
        printf("Output: %s\n\n", result);
        free(result);
    }
    
    result = remove_lowercase_substrings(test2);
    if (result != NULL) {
        printf("Input: %s\n", test2);
        printf("Output: %s\n\n", result);
        free(result);
    }
    
    result = remove_lowercase_substrings(test3);
    if (result != NULL) {
        printf("Input: %s\n", test3);
        printf("Output: %s\n\n", result);
        free(result);
    }
    
    result = remove_lowercase_substrings(test4);
    if (result != NULL) {
        printf("Input: %s\n", test4);
        printf("Output: %s\n\n", result);
        free(result);
    }
    
    result = remove_lowercase_substrings(test5);
    if (result != NULL) {
        printf("Input: (empty)\n");
        printf("Output: %s\n\n", result);
        free(result);
    }
    
    return 0;
}