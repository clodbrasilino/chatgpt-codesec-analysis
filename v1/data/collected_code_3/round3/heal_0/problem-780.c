#include <stdio.h>

void findCombinations(int arr[], int index, int num, int reducedNum, int sum)
{
    if (reducedNum < 0)
        return;

    if (reducedNum == 0)
    {
        for (int i = 0; i < index; i++)
            printf("%d ", arr[i]);
        printf("\n");
        return;
    }

    int prev = (index == 0) ? 1 : arr[index - 1];

    for (int k = prev; k <= num ; k++)
    {
        arr[index] = k;
        findCombinations(arr, index + 1, num, reducedNum - k, sum);
    }
}

void findCombinationsUtil(int n, int sum)
{
    int arr[sum];
    findCombinations(arr, 0, n, sum, sum);
}

int main()
{
    int n = 5;
    int sum = 10;
    findCombinationsUtil(n, sum);
    return 0;
}