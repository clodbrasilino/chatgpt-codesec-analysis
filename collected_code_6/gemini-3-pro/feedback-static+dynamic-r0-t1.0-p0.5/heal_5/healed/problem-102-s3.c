#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LEN 65536

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (snake_str[len] != '\0') {
        len++;
    }

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

char* read_word(void) {
    int c;
    while ((c = fgetc(stdin)) != EOF && isspace(c)) {
    }
    
    if (c == EOF) {
        return NULL;
    }

    size_t capacity = 32;
    size_t size = 0;
    char* buf = (char*)malloc(capacity);
    if (!buf) {
        return NULL;
    }

    do {
        if (size + 1 >= capacity) {
            if (capacity >= MAX_WORD_LEN) {
                break;
            }
            capacity *= 2;
            char* new_buf = (char*)realloc(buf, capacity);
            if (!new_buf) {
                free(buf);
                return NULL;
            }
            buf = new_buf;
        }
        buf[size++] = (char)c;
    } while ((c = fgetc(stdin)) != EOF && !isspace(c));

    if (c != EOF && !isspace(c)) {
        while ((c = fgetc(stdin)) != EOF && !isspace(c)) {
        }
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