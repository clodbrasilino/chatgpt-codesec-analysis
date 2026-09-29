#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int areRotations(char *str1, char *str2)
{
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    void *ptr;
    char temp[2*size1+1];
   
    if (size1 != size2) {
        return 0;
    }
   
    temp[0] = '\0';

    strncat(temp, str1, size1);
    strncat(temp, str1, size1);

    ptr = strstr(temp, str2);

    if (ptr != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int main() 
{
    char str1[50];
    char str2[50];
    scanf("%s",str1);
    scanf("%s",str2);
    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other");
    } else {
        printf("Strings are not rotations of each other");
    }
    return 0;
}