#include <stdio.h>
#include <regex.h>

int find_sequences(const char *str, regex_t *compiled_regex) {
    int status;
    regmatch_t matches[1];
    
    status = regexec(compiled_regex, str, 1, matches, 0);
    
    if (status == 0) {
        for (int i = 0; matches[i].rm_so != -1; ++i) {
            printf("Match: %.*s\n", matches[i].rm_eo - matches[i].rm_so, str + matches[i].rm_so);
        }
    } else if (status != REG_NOMATCH) {
        fprintf(stderr, "Regex error occurred while matching string\n");
        return -1;
    }
    
    return 0;
}

int main() {
    const char *pattern = "[A-Z][a-z]+";
    const char *test_str = "Example String With Several Matches Like Abc and Defg";
    regex_t compiled_regex;
    int status;

    status = regcomp(&compiled_regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (status != 0) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    status = find_sequences(test_str, &compiled_regex);
    if (status == -1) {
        return 1;
    }

    regfree(&compiled_regex);

    return 0;
}