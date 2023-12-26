#include <stdio.h>
#define MAX_SIZE 100

int findMaxFrequency(int arr[], int size)
{
    int maxFreq = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'arr[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int maxFreqItem = arr[0];

    for (int i = 0; i < size; i++)
    {
        int freq = 1;
        for (int j = i + 1; j < size; j++)
        {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[j] == arr[i])
                freq++;
        }

        if (freq > maxFreq)
        {
            maxFreq = freq;
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            maxFreqItem = arr[i];
        }
    }

    return maxFreqItem;
}

int main()
{
    int arr[MAX_SIZE];
    int size;

    printf("Enter the size of the list: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'size' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &size);

    printf("Enter the elements of the list:\n");
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    /* Possible weaknesses found:
     *  Calling function 'findMaxFrequency', 1st argument 'arr' value is <Uninit>
     */
    int maxFreqItem = findMaxFrequency(arr, size);
    printf("The item with maximum frequency is: %d\n", maxFreqItem);

    return 0;
}