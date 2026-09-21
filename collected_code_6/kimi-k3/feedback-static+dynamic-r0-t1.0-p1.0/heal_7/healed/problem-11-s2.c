#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_STRING_LEN 99

void removeFirstAndLastOccurrence(char *str, char ch) {
    if (str == NULL) {
        return;
    }

    size_t len = strnlen(str, MAX_STRING_LEN + 1);
    if (len == 0) {
        return;
    }

    size_t first = len;
    size_t last = len;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            if (first == len) {
                first = i;
            }
            last = i;
        }
    }

    if (first == len) {
        return;
    }

    if (first == last) {
        memmove(str + first, str + first + 1, len - first);
    } else {
        memmove(str + last, str + last + 1, len - last);
        memmove(str + first, str + first + 1, last - first);
    }
}

int main(void) {
    char *str = NULL;
    size_t str_size = 0;
    ssize_t bytes_read;
    char ch;
    int c;

    printf("Enter a string: ");
    
    bytes_read = getline(&str, &str_size, stdin);
    if (bytes_read == -1) {
        free(str);
        return 1;
    }

    if (bytes_read > 0 && str[bytes_read - 1] == '\n') {
        str[bytes_read - 1] = '\0';
        bytes_read--;
    }

    if (bytes_read > MAX_STRING_LEN) {
        fprintf(stderr, "Error: String too long (max %d characters)\n", MAX_STRING_LEN);
        free(str);
        return 1;
    }

    printf("Enter a character to remove: ");
    
    c = getchar();
    if (c == EOF || c == '\n') {
        free(str);
        return 1;
    }
    
    int next_char = getchar();
    if (next_char != EOF && next_char != '\n') {
        fprintf(stderr, "Error: Only single character allowed\n");
        free(str);
        return 1;
    }
    
    ch = (char)c;

    removeFirstAndLastOccurrence(str, ch);

    printf("Result: %s\n", str);

    free(str);
    return 0;
}