#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 4096

char *snake_to_camel(const char *snake_str);

char *snake_to_camel(const char *snake_str) {
    if (!snake_str) {
        return NULL;
    }

    size_t len = 0;
    
    /* Possible weaknesses found:
     *  Either the condition 'len<4096' is redundant or the array 'snake_str[28]' is accessed at index 4095, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Array index out of bounds
     *  Assuming that condition 'len<4096' is not redundant
     */
    while (len < MAX_STR_LEN && snake_str[len] != '\0') {
        len++;
    }

    char *camel_str = malloc(len + 1);
    if (!camel_str) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int capitalize_next = 0;

    while (i < len) {
        if (snake_str[i] == '_') {
            if (j > 0) {
                capitalize_next = 1;
            }
        } else {
            if (capitalize_next) {
                camel_str[j++] = (char)toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                camel_str[j++] = (char)tolower((unsigned char)snake_str[i]);
            }
        }
        i++;
    }
    camel_str[j] = '\0';

    return camel_str;
}

int main(void) {
    const char *test_str = "this_is_a_snake_case_string";
    char *camel_str = snake_to_camel(test_str);

    if (camel_str) {
        printf("%s\n", camel_str);
        free(camel_str);
    }

    return 0;
}