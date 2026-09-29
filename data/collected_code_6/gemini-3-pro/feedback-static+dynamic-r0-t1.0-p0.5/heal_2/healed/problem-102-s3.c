#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int capitalize_next = 1;

    while (snake_str[i] != '\0') {
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
    size_t capacity = 1024;
    char *buffer = (char*)malloc(capacity);
    if (buffer == NULL) {
        return 1;
    }

    while (1) {
        size_t index = 0;
        int c;

        while ((c = getchar()) != EOF && isspace(c)) {
        }

        if (c == EOF) {
            break;
        }

        do {
            if (index + 1 >= capacity) {
                capacity *= 2;
                char *new_buffer = (char*)realloc(buffer, capacity);
                if (new_buffer == NULL) {
                    free(buffer);
                    return 1;
                }
                buffer = new_buffer;
            }
            buffer[index++] = (char)c;
            c = getchar();
        } while (c != EOF && !isspace(c));

        buffer[index] = '\0';

        char* camel = snake_to_camel(buffer);
        if (camel) {
            printf("%s\n", camel);
            free(camel);
        }
    }

    free(buffer);
    return 0;
}