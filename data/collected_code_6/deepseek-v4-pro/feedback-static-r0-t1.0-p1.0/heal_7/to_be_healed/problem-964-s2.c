#include <stdio.h>
#include <string.h>

int is_even_length(const char *word) {
    if (word == NULL) {
        return -1;
    }
    return (int)(strnlen(word, 1024) % 2 == 0);
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
    
    printf("%s: %s\n", test1, is_even_length(test1) == 1 ? "even" : "odd");
    printf("%s: %s\n", test2, is_even_length(test2) == 1 ? "even" : "odd");
    printf("%s: %s\n", test3, is_even_length(test3) == 1 ? "even" : "odd");
    printf("%s: %s\n", test4, is_even_length(test4) == 1 ? "even" : "odd");
    
    /* Possible weaknesses found:
     *  Condition 'test5==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'test5==NULL' is always true
     */
    if (test5 == NULL) {
        printf("NULL: invalid input\n");
    } else {
        int result = is_even_length(test5);
        printf("NULL: %s\n", result == 1 ? "even" : "odd");
    }
    
    return 0;
}