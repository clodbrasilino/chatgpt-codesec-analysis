#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int find_lowercase_underscore_sequences(const char *input) {
    regex_t regex;
    regmatch_t match;
    int ret;
    const char *cursor = input;
    int found = 0;

    ret = regcomp(&regex, "[a-z]+_[a-z]+", REG_EXTENDED);
    if (ret) {
        return 0;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        printf("%.*s\n", (int)(match.rm_eo - match.rm_so), cursor + match.rm_so);
        cursor += match.rm_eo;
        found = 1;
    }

    regfree(&regex);
    return found;
}

int main(int argc, char *argv[]) {
    const char *test_string = "hello_world test_case abc_def_ghi not_matching 123_abc x_y_z";
    
    if (argc > 1) {
        test_string = argv[1];
    }
    
    printf("Input: %s\n", test_string);
    printf("Matches:\n");
    int result = find_lowercase_underscore_sequences(test_string);
    
    if (!result) {
        printf("No matches found\n");
    }
    
    return 0;
}