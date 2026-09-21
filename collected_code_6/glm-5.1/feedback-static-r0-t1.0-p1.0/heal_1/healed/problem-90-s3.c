#include <stdio.h>
#include <string.h>
#include <ctype.h>

int find_longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;
    const char *p = str;

    while (*p != '\0') {
        if (isalpha((unsigned char)*p)) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        }
        p++;
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}

int main(void) {
    const char *text = "Hello world from C programming";
    int result = find_longest_word_length(text);
    printf("%d\n", result);
    return 0;
}