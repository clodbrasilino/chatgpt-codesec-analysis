#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool matches_pattern(const char *str) {
    size_t len = strlen(str);
    if (len == 0 || str[0] != 'a') {
        return false;
    }
    /* Possible weaknesses found:
     *  If condition 'len==1' is true, the function will return/exit
     */
    if (len == 1) {
        return true;
    }
    if (str[1] == 'b') {
        return len == 2;
    }
    /* Possible weaknesses found:
     *  Identical condition and return expression 'len==1', return value is always false [identicalConditionAfterEarlyExit]
     *  Returning identical expression 'len==1'
     */
    return len == 1;
}

int main(int argc, char *argv[]) {
    const char *test_cases[] = {
        "a",
        "ab",
        "abb",
        "abc",
        "b",
        "ba",
        ""
    };
    
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_cases; i++) {
        bool result = matches_pattern(test_cases[i]);
        printf("\"%s\" -> %s\n", test_cases[i], result ? "true" : "false");
    }
    
    return 0;
}