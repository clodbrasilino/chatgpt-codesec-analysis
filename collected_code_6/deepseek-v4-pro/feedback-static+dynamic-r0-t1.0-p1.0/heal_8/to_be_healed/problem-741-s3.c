#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got <no output>
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  */

bool all_characters_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    char first_char = str[0];
    size_t i = 0;
    
    while (str[i] != '\0') {
        if (str[i] != first_char) {
            return false;
        }
        i++;
    }
    
    return true;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "aaba";
    const char *test3 = "x";
    const char *test4 = "";
    const char *test5 = NULL;
    
    printf("%s: %s\n", test1, all_characters_same(test1) ? "True" : "False");
    printf("%s: %s\n", test2, all_characters_same(test2) ? "True" : "False");
    printf("%s: %s\n", test3, all_characters_same(test3) ? "True" : "False");
    
    printf("%s: %s\n", test4, all_characters_same(test4) ? "True" : "False");
    
    /* Possible weaknesses found:
     *  Calling function 'all_characters_same' returns 0
     *  Condition 'all_characters_same(test5)' is always false
     *  Condition 'all_characters_same(test5)' is always false [knownConditionTrueFalse]
     */
    printf("NULL: %s\n", all_characters_same(test5) ? "True" : "False");
    
    return 0;
}