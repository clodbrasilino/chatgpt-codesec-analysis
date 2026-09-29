#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 4096

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strnlen(snake_str, MAX_LEN);
    if (len == MAX_LEN && snake_str[len] != '\0') {
        return NULL;
    }

    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_' && i + 1 < len && islower((unsigned char)snake_str[i + 1])) {
            camel_str[j++] = toupper((unsigned char)snake_str[i + 1]);
            i++;
        } else {
            camel_str[j++] = snake_str[i];
        }
    }
    camel_str[j] = '\0';

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

    /* Possible weaknesses found:
     * Flawfinder getenv: Environment variables are untrustable input if they can be set by an attacker. They can have any content and length, and the same variable can be set more than once (CWE-807, CWE-20). Check environment variables carefully before using them. (risk 3, buffer)
     */
    const char *input3 = getenv("NONEXISTENT_ENV_VAR_XYZ");
    if (input3 != NULL) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char safe_input[MAX_LEN + 1];
        snprintf(safe_input, sizeof(safe_input), "%s", input3);
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t env_len = strlen(safe_input);
        int valid = 1;
        
        for (size_t i = 0; i < env_len; i++) {
            if (!islower((unsigned char)safe_input[i]) && safe_input[i] != '_') {
                valid = 0;
                break;
            }
        }

        if (valid) {
            char *output3 = snake_to_camel(safe_input);
            if (output3 != NULL) {
                printf("Input: %s\nOutput: %s\n", safe_input, output3);
                free(output3);
            }
        } else {
            printf("Untrusted input rejected.\n");
        }
    } else {
        printf("NULL input handled safely.\n");
    }

    return 0;
}