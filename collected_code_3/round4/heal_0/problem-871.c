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
    char str1[100], str2[100];
    printf("Enter first string: ");
    scanf("%s", str1);
    printf("Enter second string: ");
    scanf("%s", str2);

    if (areRotations(str1, str2))
        printf("Strings are rotations of each other\n");
    else
        printf("Strings are not rotations of each other\n");

    return 0;
}