#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void find_words(const char *str) {
    if (str == NULL) {
        return;
    }

    int in_word = 0;
    int print_word = 0;
    const char *current = str;

    while (*current != '\0') {
        if (isalpha((unsigned char)*current)) {
            if (!in_word) {
                in_word = 1;
                char lower_c = tolower((unsigned char)*current);
                if (lower_c == 'a' || lower_c == 'e') {
                    print_word = 1;
                }
            }
            if (print_word) {
                putchar(*current);
            }
        } else {
            if (in_word) {
                if (print_word) {
                    putchar('\n');
                }
                in_word = 0;
                print_word = 0;
            }
        }
        current++;
    }

    if (in_word && print_word) {
        putchar('\n');
    }
}

int main(void) {
    const char *test_string = "An apple a day keeps the doctor away. Every elephant enjoys eating apples.";
    find_words(test_string);
    return 0;
}