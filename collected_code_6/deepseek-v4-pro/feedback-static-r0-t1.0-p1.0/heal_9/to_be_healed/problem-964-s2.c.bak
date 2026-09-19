#include <stdio.h>
#include <string.h>

int is_even_length(const char *word) {
    if (word == NULL) {
        return 0;
    }
    return strlen(word) % 2 == 0;
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "world";
    const char *test3 = "C";
    const char *test4 = "";
    /* Possible weaknesses found:
     *  Assignment 'test5=NULL', assigned value is 0
     */
    const char *test5 = NULL;
    
    printf("%s: %s\n", test1, is_even_length(test1) ? "even" : "odd");
    printf("%s: %s\n", test2, is_even_length(test2) ? "even" : "odd");
    printf("%s: %s\n", test3, is_even_length(test3) ? "even" : "odd");
    printf("%s: %s\n", test4, is_even_length(test4) ? "even" : "odd");
    
    /* Possible weaknesses found:
     *  Condition 'test5!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'test5!=NULL' is always false
     */
    if (test5 != NULL) {
        printf("NULL: %s\n", is_even_length(test5) ? "even" : "odd");
    } else {
        printf("NULL: odd\n");
    }
    
    return 0;
}