#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void match_and_print(const char *pattern, const char *string, const char *label) {
    regex_t regex;
    int ret;
    regmatch_t pmatch[1];
    const char *p = string;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    printf("%s: ", label);
    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        int len = pmatch[0].rm_eo - pmatch[0].rm_so;
        printf("%.*s ", len, p + pmatch[0].rm_so);
        p += pmatch[0].rm_eo;
    }
    printf("\n");

    regfree(&regex);
}

void analyze_string(const char *input) {
    if (input == NULL) {
        return;
    }

    match_and_print("[A-Z]+", input, "Uppercase");
    match_and_print("[a-z]+", input, "Lowercase");
    match_and_print("[0-9]+", input, "Numeric");
    match_and_print("[^A-Za-z0-9 \t\n]+", input, "Special");
}

int main(void) {
    const char *test_str = "HelloWorld! 123 @#Test";

    analyze_string(test_str);

    return 0;
}