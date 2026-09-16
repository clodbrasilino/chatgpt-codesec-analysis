#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void find_words_starting_with_a_or_e(const char *str) {
    if (str == NULL) {
        return;
    }

    char *str_copy = strdup(str);
    if (str_copy == NULL) {
        return;
    }

    char *context = NULL;
    char *token = strtok_r(str_copy, " \t\n\r\f\v", &context);

    while (token != NULL) {
        if (tolower((unsigned char)token[0]) == 'a' || tolower((unsigned char)token[0]) == 'e') {
            printf("%s\n", token);
        }
        token = strtok_r(NULL, " \t\n\r\f\v", &context);
    }

    free(str_copy);
}

int main(void) {
    const char *text = "An apple a day keeps the doctor away, even everyday.";
    find_words_starting_with_a_or_e(text);
    return 0;
}