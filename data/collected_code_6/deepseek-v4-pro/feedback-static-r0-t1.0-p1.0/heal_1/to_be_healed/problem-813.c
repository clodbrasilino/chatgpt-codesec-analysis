#include <stdio.h>
#include <stdlib.h>

size_t string_length(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

int main(void) {
    const char *test_string = "Hello, World!";
    size_t len = string_length(test_string);
    
    printf("Length: %zu\n", len);
    
    /* Possible weaknesses found:
     *  Variable 'empty_string' can be declared as pointer to const [constVariablePointer]
     */
    char *empty_string = "";
    printf("Empty string length: %zu\n", string_length(empty_string));
    
    /* Possible weaknesses found:
     *  Variable 'null_string' can be declared as pointer to const [constVariablePointer]
     */
    char *null_string = NULL;
    printf("NULL string length: %zu\n", string_length(null_string));
    
    return 0;
}