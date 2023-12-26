#include <stdio.h>

void extractUniqueValues(int *dictionary, int dictLength, int *uniqueValues, int *uniqueCount)
{
    int i, j, count;
    *uniqueCount = 0;

    for (i = 0; i < dictLength; i++)
    {
        count = 0;
        for (j = i + 1; j < dictLength; j++)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'dictionary[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'dictionary[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (dictionary[i] == dictionary[j])
            {
                count++;
                break;
            }
        }

        if (count == 0)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'dictionary[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            uniqueValues[*uniqueCount] = dictionary[i];
            (*uniqueCount)++;
        }
    }
}

int main()
{
    int dictionary[] = {1, 2, 3, 2, 4, 5, 1, 6, 3};
    int dictLength = sizeof(dictionary) / sizeof(int);
    int uniqueValues[dictLength];
    int uniqueCount;

    /* Possible weaknesses found:
     *  Cannot determine that 'uniqueCount' is initialized [premium-bughuntingUninit]
     */
    extractUniqueValues(dictionary, dictLength, uniqueValues, &uniqueCount);

    printf("Unique Values: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'uniqueCount' is initialized [premium-bughuntingUninit]
     */
    for (int i = 0; i < uniqueCount; i++)
    {
        /* Possible weaknesses found:
         *  Cannot determine that 'uniqueValues[i]' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", uniqueValues[i]);
    }

    return 0;
}