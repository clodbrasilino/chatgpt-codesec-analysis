#include <stdio.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void add_spaces_between_capital_words(char *input) {
    regex_t reg;
    regmatch_t matches[1];
    const char *pattern = "([A-Z][^ ]*)";

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) return;

    int offset = 0, added_chars = 0;
    size_t len = strlen(input);
    while (regexec(&reg, input + offset, 1, matches, 0) == 0) {
        size_t start = matches[0].rm_so + offset + added_chars;
        memmove(input + start + 1, input + start, len - start + 1 - added_chars);
        input[start] = ' ';
        offset = start + 1 - added_chars;
        added_chars++;
    }

    regfree(&reg);
}

int main() {
    char str[] = "HelloWorldThisIsATestString";
    size_t initial_len = strlen(str);
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char *new_str = (char *)malloc(initial_len * 2 + 1); // Allocate space for max possible length
    if (new_str == NULL) return 1; // Check for allocation failure
    strcpy(new_str, str);
    add_spaces_between_capital_words(new_str);
    printf("%s\n", new_str);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(new_str);
    return 0;
}