#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

int arePermutation(char* str1, char* str2)
{
    int count1[NO_OF_CHARS] = {0};
    int count2[NO_OF_CHARS] = {0};
    int i;

    for (i = 0; str1[i] && str2[i];  i++)
    {
        count1[str1[i]]++;
        count2[str2[i]]++;
    }

    if (str1[i] || str2[i])
        return 0;

    for (i = 0; i < NO_OF_CHARS; i++)
        if (count1[i] != count2[i])
            return 0;

    return 1;
}

int main()
{
    char str1[100], str2[100];
    printf("Enter first string: ");
    scanf("%s", str1);
    printf("Enter second string: ");
    scanf("%s", str2);
    if (arePermutation(str1, str2))
        printf("Strings are permutations of each other\n");
    else
        printf("Strings are not permutations of each other\n");

    return 0;
}