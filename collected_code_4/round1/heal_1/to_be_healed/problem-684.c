#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

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
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     */
    printf("Character '%c' occurred %zu times.\n", c, count);

    return EXIT_SUCCESS;
}