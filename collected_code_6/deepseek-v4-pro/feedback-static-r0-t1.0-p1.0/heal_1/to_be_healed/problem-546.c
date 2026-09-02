#include <stdio.h>
#include <string.h>

char *find_last_occurrence(const char *str, char ch)
{
    const char *last = NULL;
    const char *current = strchr(str, ch);
    
    while (current != NULL) {
        last = current;
        current = strchr(current + 1, ch);
    }
    
    return (char *)last;
}

int main(void)
{
    const char *test_string = "hello world, hello universe";
    char search_char = 'o';
    /* Possible weaknesses found:
     *  Variable 'result' can be declared as pointer to const [constVariablePointer]
     */
    char *result = find_last_occurrence(test_string, search_char);
    
    if (result != NULL) {
        /* Possible weaknesses found:
         *  %ld in format string (no. 2) requires 'long' but the argument type is 'ptrdiff_t {aka signed int}'. [invalidPrintfArgType_sint]
         */
        printf("Last occurrence of '%c' found at position: %ld\n", 
               search_char, result - test_string);
    } else {
        printf("Character '%c' not found in string\n", search_char);
    }
    
    return 0;
}