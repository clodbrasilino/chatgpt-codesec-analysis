#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

void snakeToCamel(char* s)
{
    /* Possible weaknesses found:
     *  Cannot determine that 's[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(s);
    int i, j;
    
    for (i = 0; i < len-1; i++) {
        if (s[i] == '_') {
            for (j = i; j < len-1; j++) {
                s[j] = s[j+1];
            }
            len--;
            s[i] = s[i] & ~('a' - 'A'); // Convert lowercase to uppercase
        }
    }
}

int main()
{
    char str[] = "convert_snake_case_to_camel_case";
    
    snakeToCamel(str);
    
    /* Possible weaknesses found:
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     */
    printf("%s\n", str);
    
    return 0;
}