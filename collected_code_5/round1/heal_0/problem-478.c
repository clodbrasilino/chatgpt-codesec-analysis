#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeLowercaseSubstrings(const char *src) {
    size_t n = strlen(src);
    char *dst = malloc(n + 1);
    if (dst != NULL) {
        char *ptr = dst;
        while (*src) {
            if (!islower((unsigned char)*src)) {
                *ptr++ = *src;
            }
            src++;
        }
        *ptr = 0;
    }
    return dst;
}

int main(void) {
    char str[] = "Hello World!";
    char* modifiedStr = removeLowercaseSubstrings(str);
    if(modifiedStr!=NULL){
        printf("%s \n", modifiedStr);
        free(modifiedStr);
    }else{
       fprintf(stderr, "Failed to allocate memory\n");
    }
    return 0;
}