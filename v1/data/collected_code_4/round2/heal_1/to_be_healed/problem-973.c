#include<stdio.h>
#include<string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* leftRotateString(char *str, unsigned int d) {
    unsigned int len = strlen(str);
    if (d >= len) {
        return str;
    }

    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    char *tmp = (char*) malloc(sizeof(char) * len);
    if (!tmp) {
        perror("Failed to allocate memory");
        return NULL;
    }
    
    memmove(tmp, str + d, len - d);
    memmove(tmp + len - d, str, d);
    memmove(str, tmp, len);
    
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     */
    free(tmp);
    return str;
}

int main(){
    char str[] = "LoremIpsumDolor";
    int d = 5;
    printf("Before rotation: %s\n", str);
    char* res = leftRotateString(str, d);
    if (res != NULL) {
        printf("After rotation: %s\n", res);
    }
    return 0;
}