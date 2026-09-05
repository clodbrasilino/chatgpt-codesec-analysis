#include <stdio.h>
#include <string.h>
#include <ctype.h>

int find_longest_word_length(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_length = 0;
    int current_length = 0;
    size_t i = 0;
    size_t len = strlen(str);

    while (i < len) {
        if (isalpha((unsigned char)str[i])) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        }
        i++;
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