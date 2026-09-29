#include <stdlib.h>
#include <string.h>

size_t count_occurrences(const char* str, const char c){
    size_t count = 0;
    
    if (str == NULL) return count;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) count++;
    }
    
    return count;
}

int main() {
    const char* str = "hello, how are you";
    char c = 'o';

    size_t count = count_occurrences(str, c);

    /* Possible weaknesses found:
     *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
     *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    printf("Character '%c' occurred %zu times.\n", c, count);

    return EXIT_SUCCESS;
}