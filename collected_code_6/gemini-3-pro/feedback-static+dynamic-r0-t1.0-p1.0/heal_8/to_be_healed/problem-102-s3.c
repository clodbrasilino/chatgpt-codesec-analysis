#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* snake_to_camel(const char* snake_str, size_t len) {
    if (snake_str == NULL) {
        return NULL;
    }

    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    int capitalize_next = 1;

    for (size_t i = 0; i < len; i++) {
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
    }
    camel_str[j] = '\0';

    return camel_str;
}

int main(void) {
    size_t capacity = 1024;
    size_t length = 0;
    char* buffer = (char*)malloc(capacity);
    
    if (buffer == NULL) {
        return 1;
    }

    int c;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stdin)) != EOF) {
        if (isspace(c)) {
            if (length > 0) {
                buffer[length] = '\0';
                char* camel = snake_to_camel(buffer, length);
                if (camel != NULL) {
                    printf("%s\n", camel);
                    free(camel);
                }
                length = 0;
            }
        } else {
            if (length >= capacity - 1) {
                size_t new_capacity = capacity * 2;
                if (new_capacity <= capacity) {
                    free(buffer);
                    return 1;
                }
                char* temp = (char*)realloc(buffer, new_capacity);
                if (temp == NULL) {
                    free(buffer);
                    return 1;
                }
                buffer = temp;
                capacity = new_capacity;
            }
            buffer[length++] = (char)c;
        }
    }

    if (length > 0) {
        buffer[length] = '\0';
        char* camel = snake_to_camel(buffer, length);
        if (camel != NULL) {
            printf("%s\n", camel);
            free(camel);
        }
    }

    free(buffer);
    return 0;
}