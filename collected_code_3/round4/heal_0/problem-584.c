#include <stdio.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100

void find_adverbs(char* sentence) {
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    char* pattern = "\\b\\w+ly\\b";
    int start, end, i;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        printf("Could not compile regex\n");
        return;
    }

    while (!regexec(&regex, sentence, MAX_MATCHES, matches, 0)) {
        for (i = 0; i < MAX_MATCHES && matches[i].rm_so != -1; i++) {
            start = matches[i].rm_so + (sentence - sentence);
            end = matches[i].rm_eo + (sentence - sentence);
            printf("Adverb found at position %d: ", start);
            printf("%.*s\n", (end - start), sentence + start);
        }
        sentence += matches[0].rm_eo;
    }

    regfree(&regex);
}

int main() {
    char sentence[] = "He quickly ran towards the slowly moving train.";
    find_adverbs(sentence);
    return 0;
}