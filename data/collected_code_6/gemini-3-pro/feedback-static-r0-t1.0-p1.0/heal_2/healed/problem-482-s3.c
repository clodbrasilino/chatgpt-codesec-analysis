#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void find_camel_case_sequences(const char *str) {
    if (str == NULL) {
        return;
    }

    regex_t regex;
    int reti;
    regmatch_t pmatch[1];
    const char *p = str;

    reti = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (reti) {
        return;
    }

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int start = pmatch[0].rm_so;
        int end = pmatch[0].rm_eo;
        int len = end - start;
        
        printf("%.*s\n", len, p + start);
        
        p += end;
    }

    regfree(&regex);
}

int main(void) {
    const char *test_str = "This is a Test String with CamelCase and another Example.";
    find_camel_case_sequences(test_str);
    return 0;
}