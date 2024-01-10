#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* findFirstRepeatedWord(char* str) {
    char *word, *temp;
    char* words[100] = {NULL};
    int i = 0;
    
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    temp = (char*)malloc(strlen(str)+1);
    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(temp,str);
    word = strtok(temp, " ");
    
    while (word != NULL) {
        for (int j = 0; j < i; j++) {
            if (strcmp(words[j], word) == 0) {
                /* Possible weaknesses found:
                 *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
                 *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
                 *  include '<stdlib.h>' or provide a declaration of 'free'
                 */
                free(temp);
                return word;
            }
        }
        
        words[i++] = word;
        word = strtok(NULL, " ");
    }
    
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     */
    free(temp);
    return NULL;
}

int main() {
    char str[] = "This is a sample string with repeated words";
    char* repeatedWord = findFirstRepeatedWord(str);
    
    if (repeatedWord != NULL) {
        printf("First repeated word: %s\n", repeatedWord);
    } else {
        printf("No repeated word found\n");
    }
    
    return 0;
}