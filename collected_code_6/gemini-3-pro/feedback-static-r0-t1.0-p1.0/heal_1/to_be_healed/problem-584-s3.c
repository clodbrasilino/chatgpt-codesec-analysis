#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_adverbs(const char *sentence) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "\\b[A-Za-z]+ly\\b";
    
    if (sentence == NULL) {
        return;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE) != 0) {
        fprintf(stderr, "Failed to compile regex.\n");
        return;
    }

    const char *p = sentence;
    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        
        /* Possible weaknesses found:
         *  %ld in format string (no. 3) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'. [invalidPrintfArgType_sint]
         */
        printf("Adverb: '%.*s', Position: %ld\n", end - start, p + start, (p - sentence) + start);
        
        p += end;
    }

    regfree(&regex);
}

int main(void) {
    const char *sentence = "He quickly ran across the field and suddenly stopped, breathing heavily.";
    
    find_adverbs(sentence);
    
    return 0;
}