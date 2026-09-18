#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAXIMUM_WORD_LENGTH 1000

void find_words_of_length(char *text) {
    regex_t regex;
    regmatch_t pmatch[1];
    char pattern[] = "\\w{4,}";
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        printf("Failed to compile regex\n");
        return;
    }

    char *word = malloc(sizeof(char) * MAXIMUM_WORD_LENGTH);
    const char *cursor = text;
    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        int length = pmatch[0].rm_eo - pmatch[0].rm_so;

        if (length > MAXIMUM_WORD_LENGTH - 1) {
            length = MAXIMUM_WORD_LENGTH - 1;
        }

        strncpy(word, cursor + pmatch[0].rm_so, length);
        word[length] = '\0';
        printf("%s\n", word);

        cursor += pmatch[0].rm_eo;
    }

    regfree(&regex);
    free(word);
}

int main() {
    char text[] = "This is a C program to find all words which are at least 4 characters long in a string";
    find_words_of_length(text);
    return 0;
}