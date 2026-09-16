#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_word_at_beginning(const char *str, const char *word) {
    if (str == NULL || word == NULL) {
        return false;
    }

    size_t word_len = strlen(word);
    if (word_len == 0) {
        return false;
    }

    size_t str_len = strlen(str);
    if (str_len < word_len) {
        return false;
    }

    if (strncmp(str, word, word_len) == 0) {
        if (str_len == word_len) {
            return true;
        }
        
        char next_char = str[word_len];
        /* Possible weaknesses found:
         *  Condition 'next_char=='\0'' is always false [knownConditionTrueFalse]
         */
        if (next_char == ' ' || next_char == '\t' || next_char == '\n' || next_char == '\r' || next_char == '\0') {
            return true;
        }
    }

    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <word>\n", argv[0]);
        return 1;
    }

    bool result = match_word_at_beginning(argv[1], argv[2]);

    if (result) {
        printf("Match found.\n");
    } else {
        printf("No match found.\n");
    }

    return 0;
}