#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Possible weaknesses found:
 *  expected ';' after top level declarator
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'sequences'
 *  variable has incomplete type 'void'
 */
void find sequences(const char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; ) {
        if (isupper(str[i])) {
            int start = i;
            i++;
            while (i < len && islower(str[i])) {
                i++;
            }
            if (i > start + 1) {
                printf("%.*s\n", i - start, &str[start]);
            } else {
                i = start + 1;
            }
        } else {
            i++;
        }
    }
}

int main() {
    const char *input = "ThisIsAnExample AbCdef Another ExampleA";
    /* Possible weaknesses found:
     *  call to undeclared function 'find_sequences'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'find_sequences' [-Wimplicit-function-declaration]
     */
    find_sequences(input);
    return 0;
}