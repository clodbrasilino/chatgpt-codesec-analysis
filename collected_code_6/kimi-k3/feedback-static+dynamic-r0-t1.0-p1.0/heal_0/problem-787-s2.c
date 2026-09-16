#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_abbb(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    if (str[0] == 'a' && str[1] == 'b' && str[2] == 'b' && str[3] == 'b' && str[4] == '\0') {
        return true;
    }
    
    return false;
}

int main(void) {
    const char *test1 = "abbb";
    const char *test2 = "abb";
    const char *test3 = "abbbb";
    const char *test4 = "abc";
    
    printf("Test 1 (\"abbb\"): %s\n", match_abbb(test1) ? "Match" : "No match");
    printf("Test 2 (\"abb\"): %s\n", match_abbb(test2) ? "Match" : "No match");
    printf("Test 3 (\"abbbb\"): %s\n", match_abbb(test3) ? "Match" : "No match");
    printf("Test 4 (\"abc\"): %s\n", match_abbb(test4) ? "Match" : "No match");
    
    return 0;
}