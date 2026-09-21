#include <stdio.h>
#include <stdlib.h>

char *remove_parenthesis_area(char *str) {
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

    size_t read_idx = 0;
    size_t write_idx = 0;
    int paren_count = 0;

    while (str[read_idx] != '\0') {
        if (str[read_idx] == '(') {
            paren_count++;
        } else if (str[read_idx] == ')' && paren_count > 0) {
            paren_count--;
        } else if (paren_count == 0) {
            result[write_idx++] = str[read_idx];
        }
        read_idx++;
    }
    
    result[write_idx] = '\0';

    return result;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            char *res = remove_parenthesis_area(argv[i]);
            if (res) {
                printf("%s\n", res);
                free(res);
            }
        }
    } else {
        char buffer[4096];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            size_t len = 0;
            while (buffer[len] != '\0') {
                if (buffer[len] == '\n' || buffer[len] == '\r') {
                    buffer[len] = '\0';
                    break;
                }
                len++;
            }
            char *res = remove_parenthesis_area(buffer);
            if (res) {
                printf("%s\n", res);
                free(res);
            }
        }
    }

    return 0;
}