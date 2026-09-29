#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 4096

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Either the condition 'len>=4096' is redundant or the array 'snake_str[12]' is accessed at index 4096, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Array index out of bounds
     */
    while (snake_str[len] != '\0') {
        /* Possible weaknesses found:
         *  Assuming that condition 'len>=4096' is not redundant
         */
        if (len >= MAX_STR_LEN) {
            return NULL;
        }
        /* Possible weaknesses found:
         *  len is incremented', new value is 4096
         */
        len++;
    }

    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int capitalize_next = 1;

    while (i < len) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel_str[j++] = toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                camel_str[j++] = tolower((unsigned char)snake_str[i]);
            }
        }
        i++;
    }
    camel_str[j] = '\0';

    return camel_str;
}

int main(void) {
    const char* snake1 = "hello_world";
    const char* snake2 = "this_is_a_test";
    const char* snake3 = "_leading_underscore";
    const char* snake4 = "trailing_underscore_";

    char* camel1 = snake_to_camel(snake1);
    char* camel2 = snake_to_camel(snake2);
    char* camel3 = snake_to_camel(snake3);
    char* camel4 = snake_to_camel(snake4);

    if (camel1) {
        printf("%s -> %s\n", snake1, camel1);
        free(camel1);
    }
    if (camel2) {
        printf("%s -> %s\n", snake2, camel2);
        free(camel2);
    }
    if (camel3) {
        printf("%s -> %s\n", snake3, camel3);
        free(camel3);
    }
    if (camel4) {
        printf("%s -> %s\n", snake4, camel4);
        free(camel4);
    }

    return 0;
}