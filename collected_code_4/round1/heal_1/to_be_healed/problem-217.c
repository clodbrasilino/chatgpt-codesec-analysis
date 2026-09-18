#include <stdio.h>
#include <string.h>
/* Possible weaknesses found:
 *  'bool' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
 */
#define ASCII_SIZE 256

char findFirstRepeatedChar(char* str)
{
    /* Possible weaknesses found:
     *  unknown type name 'bool'
     */
    bool charSet[ASCII_SIZE] = {0};
    for (int i=0; i<strlen(str); i++)
    {
        /* Possible weaknesses found:
         *  'true' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  'true' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
         */
        if(charSet[str[i]] == true)
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