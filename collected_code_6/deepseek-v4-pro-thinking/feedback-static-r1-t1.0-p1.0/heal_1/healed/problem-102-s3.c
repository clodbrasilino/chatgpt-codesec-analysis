#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

char *snake_to_camel(char *str) {
    size_t read, write;
    int capitalize_next;

    if (str == NULL) {
        return NULL;
    }

    write = 0;
    capitalize_next = 0;

    for (read = 0; str[read] != '\0'; ++read) {
        unsigned char c = (unsigned char)str[read];

        if (c == '_') {
            if (write > 0) {
                capitalize_next = 1;
            }
        } else if (write == 0) {
            str[write++] = (char)tolower(c);
        } else if (capitalize_next) {
            str[write++] = (char)toupper(c);
            capitalize_next = 0;
        } else {
            str[write++] = str[read];
        }
    }

    str[write] = '\0';
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