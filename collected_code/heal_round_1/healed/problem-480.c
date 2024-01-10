#include <stdio.h>
#define ASCII_SIZE 256

char getMaxOccuringChar(const char *str)
{
    int count[ASCII_SIZE] = {0};
    int max = -1;
    char result = '\0';

    for (int i = 0; str[i]; i++)
    {
        count[(unsigned char)str[i]]++;

        if (count[(unsigned char)str[i]] > max)
        {
            max = count[(unsigned char)str[i]];
            result = str[i];
        }
    }

    return result;
}

int main()
{
    const char str[] = "test string";
    char maxChar = getMaxOccuringChar(str);

    printf("The maximum occurring character is '%c' \n", maxChar);

    return 0;
}