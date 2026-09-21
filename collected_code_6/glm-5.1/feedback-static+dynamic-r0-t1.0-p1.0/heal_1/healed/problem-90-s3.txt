#include <stdio.h>
#include <ctype.h>

int find_longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;

    while (*str) {
        if (isalpha((unsigned char)*str)) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        }
        str++;
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