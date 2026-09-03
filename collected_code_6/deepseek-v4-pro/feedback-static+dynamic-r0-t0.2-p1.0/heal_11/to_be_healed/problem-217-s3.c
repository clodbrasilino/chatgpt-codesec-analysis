#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char first_repeated_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }
    
    bool seen[256] = {false};
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return str[i];
        }
        seen[c] = true;
    }
    
    return '\0';
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "abcdef";
    const char *test3 = "aabbcc";
    const char *test4 = "";
    const char *test5 = NULL;
    
    char result1 = first_repeated_char(test1);
    char result2 = first_repeated_char(test2);
    char result3 = first_repeated_char(test3);
    char result4 = first_repeated_char(test4);
    
    printf("First repeated in \"%s\": %c\n", test1, result1 != '\0' ? result1 : '-');
    printf("First repeated in \"%s\": %c\n", test2, result2 != '\0' ? result2 : '-');
    printf("First repeated in \"%s\": %c\n", test3, result3 != '\0' ? result3 : '-');
    printf("First repeated in \"%s\": %c\n", test4, result4 != '\0' ? result4 : '-');
    
    /* Possible weaknesses found:
     *  Assignment 'result5=first_repeated_char(test5)', assigned value is 0
     *  Calling function 'first_repeated_char' returns 0
     */
    char result5 = first_repeated_char(test5);
    /* Possible weaknesses found:
     *  Condition 'result5!='\0'' is always false
     *  Condition 'result5!='\0'' is always false [knownConditionTrueFalse]
     */
    printf("First repeated in NULL: %c\n", result5 != '\0' ? result5 : '-');
    
    return 0;
}