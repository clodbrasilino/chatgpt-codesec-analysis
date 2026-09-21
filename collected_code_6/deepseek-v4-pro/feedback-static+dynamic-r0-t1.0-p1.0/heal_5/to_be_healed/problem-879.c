#include <stdio.h>
#include <regex.h>
#include <string.h>

int match_pattern(const char *str) {
    regex_t regex;
    int ret;
    int match_result = 0;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char error_buffer[512];
    size_t errbuf_size = sizeof(error_buffer);
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (str == NULL || strlen(str) >= 512) {
        return 0;
    }
    
    memset(&regex, 0, sizeof(regex_t));
    
    ret = regcomp(&regex, "^a.*b$", REG_EXTENDED);
    if (ret) {
        regerror(ret, &regex, error_buffer, errbuf_size);
        error_buffer[errbuf_size - 1] = '\0';
        fprintf(stderr, "Regex compilation error: %s\n", error_buffer);
        return 0;
    }
    
    ret = regexec(&regex, str, 0, NULL, 0);
    if (!ret) {
        match_result = 1;
    } else if (ret == REG_NOMATCH) {
        match_result = 0;
    } else {
        regerror(ret, &regex, error_buffer, errbuf_size);
        error_buffer[errbuf_size - 1] = '\0';
        fprintf(stderr, "Regex error: %s\n", error_buffer);
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