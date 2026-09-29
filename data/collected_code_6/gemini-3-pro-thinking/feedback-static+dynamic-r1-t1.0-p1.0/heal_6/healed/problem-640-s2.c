#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis_area(const char *str) {
    if (!str) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char *result = (char *)malloc(len + 1);
    if (!result) {
        return NULL;
    }

    size_t write_idx = 0;
    int paren_count = 0;

    for (size_t read_idx = 0; read_idx < len; read_idx++) {
        if (str[read_idx] == '(') {
            paren_count++;
        } else if (str[read_idx] == ')') {
            if (paren_count > 0) {
                paren_count--;
            } else {
                result[write_idx++] = str[read_idx];
            }
        } else if (paren_count == 0) {
            result[write_idx++] = str[read_idx];
        }
    }
    
    result[write_idx] = '\0';

    return result;
}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            char *res = remove_parenthesis_area(argv[i]);
            if (res) {
                printf("%s\n", res);
                free(res);
            }
        }
    } else {
        size_t size = 1024;
        size_t len = 0;
        char *buffer = (char *)malloc(size);
        if (!buffer) {
            return 1;
        }

        while (fgets(buffer + len, size - len, stdin)) {
            size_t current_len = len;
            while (buffer[current_len] != '\0') {
                current_len++;
            }

            if (current_len > 0 && (buffer[current_len - 1] == '\n' || buffer[current_len - 1] == '\r')) {
                while (current_len > 0 && (buffer[current_len - 1] == '\n' || buffer[current_len - 1] == '\r')) {
                    buffer[current_len - 1] = '\0';
                    current_len--;
                }
                char *res = remove_parenthesis_area(buffer);
                if (res) {
                    printf("%s\n", res);
                    free(res);
                }
                len = 0;
            } else {
                len = current_len;
                if (len >= size - 1) {
                    size *= 2;
                    char *new_buffer = (char *)realloc(buffer, size);
                    if (!new_buffer) {
                        free(buffer);
                        return 1;
                    }
                    buffer = new_buffer;
                }
            }
        }

        if (len > 0) {
            buffer[len] = '\0';
            char *res = remove_parenthesis_area(buffer);
            if (res) {
                printf("%s\n", res);
                free(res);
            }
        }

        free(buffer);
    }

    return 0;
}