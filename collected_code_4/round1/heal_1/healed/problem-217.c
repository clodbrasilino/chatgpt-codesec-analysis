#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ASCII_SIZE 256

char findFirstRepeatedChar(char* str)
{
    bool charSet[ASCII_SIZE] = {0};
    for (int i=0; i<strlen(str); i++)
    {
        if(charSet[str[i]])
        {
            return str[i];
        }
        charSet[str[i]] = true;
    }
    return '\0';
}

int main()
{
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);
    char result = findFirstRepeatedChar(str);
    if(result != '\0')
    {
        printf("First repeated character: %c\n", result);
    }
    else
    {
        printf("No repeated characters\n");
    }
    return 0;
}