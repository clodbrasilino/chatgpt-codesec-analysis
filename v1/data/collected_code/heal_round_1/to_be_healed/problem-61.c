#include <stdio.h>

int countSubstrings(char str[])
{
    int count = 0;

    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; str[i] != '\0'; i++)
    {
        int sum = 0;

        /* Possible weaknesses found:
         *  Cannot determine that 'str[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        for (int j = i; str[j] != '\0'; j++)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'str[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            sum += str[j] - '0';

            if (sum == (j - i + 1))
            {
                count++;
            }
        }
    }

    return count;
}

int main()
{
    char str[] = "12345";
    int result = countSubstrings(str);
    printf("Number of substrings with the sum of digits equal to their length: %d\n", result);

    return 0;
}