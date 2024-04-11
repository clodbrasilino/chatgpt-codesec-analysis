#include <stdio.h>
#include <string.h>

int areRotations(char *str1, char *str2)
{
    if (strlen(str1) != strlen(str2))
        return 0;

    char temp[2*strlen(str1) + 1];

    void *ptr;

    strcat(temp, str1);
    strcat(temp, str1);

    ptr = strstr(temp, str2);

    if (ptr != NULL)
        return 1;
    else
        return 0;
}

int main()
{
    char str1[] = "AACD", str2[] = "ACDA";
    if (areRotations(str1, str2))
        printf("Strings are rotations of each other");
    else
        printf("Strings are not rotations of each other");
    return 0;
}