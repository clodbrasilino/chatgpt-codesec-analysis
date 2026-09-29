#include <stdio.h>
#include <stdlib.h>

void rearrange(int arr[], int n)
{
    if (arr == NULL || n <= 0)
    {
        return;
    }

    int i = 0;
    int j = n - 1;

    while (i <= j)
    {
        if (arr[i] < 0)
        {
            i++;
        }
        else if (arr[j] >= 0)
        {
            j--;
        }
        else
        {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    int neg = 0;
    int pos = i;

    while (pos < n && neg < pos && arr[neg] < 0)
    {
        int temp = arr[neg];
        arr[neg] = arr[pos];
        arr[pos] = temp;
        pos++;
        neg += 2;
    }
}

int main(void)
{
    int arr[] = {-5, -2, 5, 2, 4, 7, 1, 8, 0, -8};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    if (n == 0)
    {
        fprintf(stderr, "Invalid array size\n");
        return EXIT_FAILURE;
    }

    printf("Original array: ");
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    rearrange(arr, (int)n);

    printf("Rearranged array: ");
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}