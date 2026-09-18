#include <stdio.h>
#include <string.h>

int areRotations(char* str1, char* str2)
{
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    char temp[2*size1+1]; 

    /* Check if sizes of two strings are same */
    if (size1 != size2)
      return 0;

    /* Create a temp string with value str1.str1 */
    temp[0] = '\0';
    strcat(temp, str1);
    strcat(temp, str1);

    /* Now check if str2 is a substring of temp */
    return (strstr(temp, str2) != NULL);
}

/* Driver program to test areRotations */
int main()
{
    char str1[] = "AACD", str2[] = "ACDA";
    if (areRotations(str1, str2))
       printf("Strings are rotations of each other");
    else
      printf("Strings are not rotations of each other");

    return 0;
}