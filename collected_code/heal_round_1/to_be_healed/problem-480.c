#include <stdio.h>
#define ASCII_SIZE 256

char getMaxOccuringChar(char *str)
{
    int count[ASCII_SIZE] = {0};
    int max = -1;
    char result;

    /* Possible weaknesses found:
     *  Assuming condition is false
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; str[i]; i++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        count[str[i]]++;
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (count[str[i]] > max)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            max = count[str[i]];
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            result = str[i];
        }
    }

    /* Possible weaknesses found:
     *  use of uninitialized value 'result' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    return result;
}

int main()
{
    char str[] = "test string";
    char maxChar = getMaxOccuringChar(str);

    printf("The maximum occurring character is '%c' \n", maxChar);

    return 0;
}