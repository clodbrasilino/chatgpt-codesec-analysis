#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int match_end_word(const char *str, const char *word) {
    int len_str = strlen(str);
    int len_word = strlen(word);

    if (len_str < len_word)
        return 0;

    const char *ptr_str_end = str + len_str - 1;
    const char *ptr_word_end = word + len_word - 1;

    while (ptr_str_end >= str && ptr_word_end >= word) {
        if (isalnum(*ptr_str_end) && isalnum(*ptr_word_end)) {
            if (*ptr_str_end != *ptr_word_end)
                return 0;

            ptr_word_end--;
        }

        ptr_str_end--;
    }

    return ptr_word_end < word;
}

int main() {
    if (match_end_word("Hello, world!", "world")) {
        printf("Match found!\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}