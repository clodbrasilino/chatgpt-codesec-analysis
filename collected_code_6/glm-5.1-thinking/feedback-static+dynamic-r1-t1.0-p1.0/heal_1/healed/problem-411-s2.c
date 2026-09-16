#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "_([a-z])", REG_EXTENDED) != 0) {
        free(camel_str);
        return NULL;
    }

    regmatch_t matches[2];
    const char *current_ptr = snake_str;
    size_t dst_idx = 0;

    while (1) {
        int ret = regexec(&regex, current_ptr, 2, matches, 0);
        
        if (ret == REG_NOMATCH) {
            size_t remaining_len = strlen(current_ptr);
            memcpy(camel_str + dst_idx, current_ptr, remaining_len);
            dst_idx += remaining_len;
            break;
        }

        if (ret != 0) {
            regfree(&regex);
            free(camel_str);
            return NULL;
        }

        for (regoff_t i = 0; i < matches[0].rm_so; i++) {
            camel_str[dst_idx++] = current_ptr[i];
        }

        if (matches[1].rm_so != -1) {
            camel_str[dst_idx++] = toupper((unsigned char)current_ptr[matches[1].rm_so]);
        }

        current_ptr += matches[0].rm_eo;
    }

    camel_str[dst_idx] = '\0';
    regfree(&regex);
    
    if (dst_idx > 0) {
        camel_str[0] = toupper((unsigned char)camel_str[0]);
    }
    
    return camel_str;
}

int main(void) {
    const char *input1 = "convert_this_snake_case_string";
    char *output1 = snake_to_camel(input1);
    if (output1 != NULL) {
        printf("Input: %s\nOutput: %s\n", input1, output1);
        free(output1);
    }

    const char *input2 = "alreadycamelcase";
    char *output2 = snake_to_camel(input2);
    if (output2 != NULL) {
        printf("Input: %s\nOutput: %s\n", input2, output2);
        free(output2);
    }

    const char *input3 = NULL;
    const char *output3 = snake_to_camel(input3);
    if (output3 == NULL) {
        printf("NULL input handled safely.\n");
    }

    return 0;
}