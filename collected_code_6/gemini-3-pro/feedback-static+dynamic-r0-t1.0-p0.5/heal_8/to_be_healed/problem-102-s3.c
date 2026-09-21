#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD_LEN 65536

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
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

char* read_word(void) {
    int c;
    
    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stdin);
    } while (c != EOF && isspace(c));
    
    if (c == EOF) {
        return NULL;
    }

    size_t capacity = 32;
    size_t size = 0;
    char* buf = (char*)malloc(capacity);
    if (!buf) {
        return NULL;
    }

    buf[size++] = (char)c;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stdin);
        if (c == EOF || isspace(c)) {
            break;
        }

        if (size + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            if (new_capacity > MAX_WORD_LEN) {
                new_capacity = MAX_WORD_LEN;
            }
            if (size + 1 >= new_capacity) {
                while (c != EOF && !isspace(c)) {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    c = fgetc(stdin);
                }
                break;
            }
            char* new_buf = (char*)realloc(buf, new_capacity);
            if (!new_buf) {
                free(buf);
                return NULL;
            }
            buf = new_buf;
            capacity = new_capacity;
        }
        buf[size++] = (char)c;
    }

    buf[size] = '\0';
    return buf;
}

int main(void) {
    char* word;
    
    while ((word = read_word()) != NULL) {
        char* camel = snake_to_camel(word);
        if (camel != NULL) {
            printf("%s\n", camel);
            free(camel);
        }
        free(word);
    }

    return 0;
}