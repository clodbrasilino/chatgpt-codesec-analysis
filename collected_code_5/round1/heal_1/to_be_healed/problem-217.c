#include <stdio.h>
#include <string.h>
#define ASCII_SIZE 256

char findFirstRepeatedChar(char* str)
{
    /* Possible weaknesses found:
     *  use of undeclared identifier 'bool'
     */
    bool charSet[ASCII_SIZE] = {0};
    for (int i=0; i<strlen(str); i++)
    {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'true'
         *  use of undeclared identifier 'charSet'
         */
        if(charSet[str[i]] == true)
        {
            return str[i];
        }
        /* Possible weaknesses found:
         *  use of undeclared identifier 'true'
         *  use of undeclared identifier 'charSet'
         */
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