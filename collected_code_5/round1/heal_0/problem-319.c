#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <regex.h>

#define MAX_WORD_LENGTH 5

void find_five_letter_words(char *str) {
    regex_t regex;
    int reti;
    char msgbuf[100];
    
    reti = regcomp(&regex, "\\b\\w{5}\\b", REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    regmatch_t matches[1]; 
    while (regexec(&regex, str, 1, matches, 0) == 0) {
        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        char word[MAX_WORD_LENGTH + 1] = {0};
        strncpy(word, str + start, MAX_WORD_LENGTH);
        printf("Found : %s\n", word);

        str += end;
    }
    regfree(&regex);
}

int main() {
    char src[] = "Hello, this is an example sentence.";
    find_five_letter_words(src);
    
    return 0;
}