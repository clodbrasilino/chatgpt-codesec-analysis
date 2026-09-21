#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Possible weaknesses found:
 *  variable has incomplete type 'void'
 *  expected '=', ',', ';', 'asm' or '__attribute__' before 'sequences'
 *  expected ';' after top level declarator
 */
void find sequences(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
     *  implicit declaration of function 'find_sequences' [-Wimplicit-function-declaration]
     *  call to undeclared function 'find_sequences'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    find_sequences(input);
    return 0;
}