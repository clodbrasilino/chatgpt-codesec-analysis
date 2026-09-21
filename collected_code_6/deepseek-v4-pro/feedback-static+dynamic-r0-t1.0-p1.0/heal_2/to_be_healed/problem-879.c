#include <stdio.h>
#include <regex.h>
#include <string.h>

int match_pattern(const char *str) {
    regex_t regex;
    int ret;
    int match_result = 0;
    
    ret = regcomp(&regex, "^a.*b$", REG_EXTENDED);
    if (ret) {
        return 0;
    }
    
    ret = regexec(&regex, str, 0, NULL, 0);
    if (!ret) {
        match_result = 1;
    } else if (ret == REG_NOMATCH) {
        match_result = 0;
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_buffer[512];
        regerror(ret, &regex, error_buffer, sizeof(error_buffer) - 1);
        /* Possible weaknesses found:
         *  Variable 'error_buffer[sizeof(error_buffer)-1]' is assigned a value that is never used. [unreadVariable]
         */
        error_buffer[sizeof(error_buffer) - 1] = '\0';
        match_result = 0;
    }
    
    regfree(&regex);
    return match_result;
}

int main(void) {
    const char *test_strings[] = {
        "ab",
        "a123b",
        "aXYZb",
        "acb",
        "b",
        "a",
        "ba",
        "abc",
        "a_b",
        ""
    };
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int result = match_pattern(test_strings[i]);
        if (result) {
            printf("'%s' matches\n", test_strings[i]);
        } else {
            printf("'%s' does not match\n", test_strings[i]);
        }
    }
    
    return 0;
}