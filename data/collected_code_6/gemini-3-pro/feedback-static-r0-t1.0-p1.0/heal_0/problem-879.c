#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int match_pattern(const char *input) {
    if (input == NULL) {
        return -1;
    }

    regex_t regex;
    int compile_status;
    int match_status;
    
    compile_status = regcomp(&regex, "^a.*b$", REG_EXTENDED);
    if (compile_status != 0) {
        return -1;
    }

    match_status = regexec(&regex, input, 0, NULL, 0);
    
    regfree(&regex);

    if (match_status == 0) {
        return 1;
    } else if (match_status == REG_NOMATCH) {
        return 0;
    } else {
        return -1;
    }
}

int main(void) {
    const char *test_strings[] = {
        "acb",
        "a_anything_b",
        "ab",
        "bca",
        "a test",
        "test b",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        int result = match_pattern(test_strings[i]);
        if (result == 1) {
            printf("Match: %s\n", test_strings[i]);
        } else if (result == 0) {
            printf("No match: %s\n", test_strings[i]);
        } else {
            printf("Error matching: %s\n", test_strings[i]);
        }
    }

    return 0;
}