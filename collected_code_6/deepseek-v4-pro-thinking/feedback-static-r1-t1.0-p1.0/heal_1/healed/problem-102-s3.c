#include <ctype.h>
#include <stdio.h>

char *snake_to_camel(char *str) {
    if (str == NULL) {
        return NULL;
    }

    unsigned char *src = (unsigned char *)str;
    unsigned char *dst = (unsigned char *)str;
    int capitalize_next = 0;
    int first = 1;

    while (*src) {
        unsigned char c = *src++;

        if (c == '_') {
            if (!first) {
                capitalize_next = 1;
            }
        } else {
            if (first) {
                *dst++ = (unsigned char)tolower(c);
                first = 0;
            } else if (capitalize_next) {
                *dst++ = (unsigned char)toupper(c);
                capitalize_next = 0;
            } else {
                *dst++ = c;
            }
        }
    }

    *dst = '\0';
    return str;
}

int main(void) {
    char test1[] = "hello_world";
    char test2[] = "this_is_snake_case";
    char test3[] = "_leading_underscore";

    printf("%s\n", snake_to_camel(test1));
    printf("%s\n", snake_to_camel(test2));
    printf("%s\n", snake_to_camel(test3));

    return 0;
}