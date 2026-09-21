#include <stdio.h>
#include <string.h>
#include <stddef.h>

int is_even_length(const char *word) {
    if (word == NULL) {
        return 0;
    }
    
    size_t length = strlen(word);
    return length % 2 == 0;
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "world";
    const char *test3 = "C";
    const char *test4 = "";
    const char *test5 = NULL;
    
    printf("%s: %s\n", test1, is_even_length(test1) ? "even" : "odd");
    printf("%s: %s\n", test2, is_even_length(test2) ? "even" : "odd");
    printf("%s: %s\n", test3, is_even_length(test3) ? "even" : "odd");
    printf("%s: %s\n", test4, is_even_length(test4) ? "even" : "odd");
    printf("%s: %s\n", test5 ? test5 : "NULL", is_even_length(test5) ? "even" : "odd");
    
    return 0;
}