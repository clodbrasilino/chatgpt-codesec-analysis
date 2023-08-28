#include <stdio.h>
#define ASCII_SIZE 256

char getMaxOccuringChar(char *str)
{
    int count[ASCII_SIZE] = {0};
    int max = -1;
    char result;

    for (int i = 0; str[i]; i++)
    {
        count[str[i]]++;
        if (count[str[i]] > max)
        {
            max = count[str[i]];
            result = str[i];
        }
    }

    return result;
}

int main()
{
    char str[] = "test string";
    char maxChar = getMaxOccuringChar(str);

    printf("The maximum occurring character is '%c' \n", maxChar);

    return 0;
}