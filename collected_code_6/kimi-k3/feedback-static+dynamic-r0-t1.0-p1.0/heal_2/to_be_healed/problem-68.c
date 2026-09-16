#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

bool isMonotonic(const int arr[], int size)
{
    bool increasing = true;
    bool decreasing = true;
    int i;

    if (arr == NULL || size < 0)
    {
        return false;
    }

    if (size <= 1)
    {
        return true;
    }

    for (i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            increasing = false;
        }
        if (arr[i] < arr[i + 1])
        {
            decreasing = false;
        }
    }

    return increasing || decreasing;
}

int main(void)
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {5, 4, 3, 2, 1};
    int arr3[] = {1, 3, 2, 4, 5};
    int arr4[] = {1, 1, 1, 1, 1};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    int size4 = sizeof(arr4) / sizeof(arr4[0]);

    printf("%s\n", isMonotonic(arr1, size1) ? "True" : "False");
    printf("%s\n", isMonotonic(arr2, size2) ? "True" : "False");
    printf("%s\n", isMonotonic(arr3, size3) ? "True" : "False");
    printf("%s\n", isMonotonic(arr4, size4) ? "True" : "False");

    return 0;
}