#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void find_adverbs(const char *sentence) {
    regex_t regex;
    regmatch_t matches[2];
    int result;

    const char *pattern = "\\b\\w+ly\\b";
    
    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) return;

    const char *p = sentence;
    while (regexec(&regex, p, 2, matches, 0) == 0) {
        size_t start = matches[0].rm_so + (p - sentence);
        size_t end = matches[0].rm_eo + (p - sentence);
        printf("Adverb: %.*s at position %zu-%zu\n", (int)(end - start), sentence + start, start, end - 1);
        p += matches[0].rm_eo;
    }

    regfree(&regex);
}

int main() {
    const char *sentence = "He quickly and quietly walked away.";
    find_adverbs(sentence);
    return 0;
}