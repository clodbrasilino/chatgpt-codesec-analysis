#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char* leftRotateString(char *str, unsigned int d) {
    unsigned int len = strlen(str);
    if (d >= len) {
        return str;
    }

    char *tmp = (char*) malloc(sizeof(char) * len);
    if (!tmp) {
        perror("Failed to allocate memory");
        return NULL;
    }
    
    memmove(tmp, str + d, len - d);
    memmove(tmp + len - d, str, d);
    memmove(str, tmp, len);

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