#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

int find_shortest_word_length(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int min_length = INT_MAX;
    int current_length = 0;
    int found_word = 0;

    while (*str != '\0') {
        if (isspace((unsigned char)*str)) {
            if (current_length > 0) {
                if (current_length < min_length) {
                    min_length = current_length;
                }
                found_word = 1;
                current_length = 0;
            }
        } else {
            current_length++;
        }
        str++;
    }

    if (current_length > 0) {
        if (current_length < min_length) {
            min_length = current_length;
        }
        found_word = 1;
    }

    if (!found_word) {
        return 0;
    }

    return min_length;
}

int main(void) {
    const char *test_string = "The quick brown fox jumps over the lazy dog";
    int result = find_shortest_word_length(test_string);

    if (result >= 0) {
        printf("Shortest word length: %d\n", result);
    } else {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }

    return 0;
}