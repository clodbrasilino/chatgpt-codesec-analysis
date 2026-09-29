#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_sequences(const char *text) {
    if (text == NULL) {
        return;
    }

    regex_t regex;
    int ret;
    const char *pattern = "[a-z]+_[a-z]+";
    regmatch_t pmatch[1];
    const char *p = text;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int length = pmatch[0].rm_eo - pmatch[0].rm_so;
        
        if (length > 0) {
            char *match = malloc((size_t)length + 1);
            if (match == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                regfree(&regex);
                return;
            }

            snprintf(match, (size_t)length + 1, "%.*s", length, p + pmatch[0].rm_so);
            
            printf("%s\n", match);

            free(match);
        }
        p += pmatch[0].rm_eo;
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "hello_world is a variable, so is foo_bar. But not Hello_world or foo__bar.";
    
    find_sequences(text);

    return 0;
}