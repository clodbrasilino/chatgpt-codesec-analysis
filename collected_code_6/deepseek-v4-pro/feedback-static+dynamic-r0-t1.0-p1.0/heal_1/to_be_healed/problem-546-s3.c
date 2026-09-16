#include <stdio.h>
#include <string.h>

char *find_last_occurrence(const char *str, char ch) {
    const char *last = NULL;
    while (*str) {
        if (*str == ch) {
            last = str;
        }
        str++;
    }
    return (char *)last;
}

int main(void) {
    const char *text = "hello world";
    char target = 'o';
    /* Possible weaknesses found:
     *  Variable 'result' can be declared as pointer to const [constVariablePointer]
     */
    char *result = find_last_occurrence(text, target);
    
    if (result) {
        /* Possible weaknesses found:
         *  %ld in format string (no. 2) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'. [invalidPrintfArgType_sint]
         */
        printf("Last occurrence of '%c' found at position: %ld\n", target, result - text);
    } else {
        printf("Character '%c' not found in string\n", target);
    }
    
    return 0;
}