#include <stdio.h>
#include <stdlib.h>

static int rearrange(int *arr, size_t n)
{
    size_t i;
    size_t j;
    int temp;

    if (arr == NULL)
    {
        return -1;
    }

    j = 0U;
    for (i = 0U; i < n; i++)
    {
        if (arr[i] < 0)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            j++;
        }
    }

    return 0;
}

static void print_array(const int *arr, size_t n)
{
    size_t i;

    if (arr == NULL)
    {
        return;
    }

    for (i = 0U; i < n; i++)
    {
        (void)printf("%d ", arr[i]);
    }
    (void)printf("\n");
}

int main(void)
{
    int data[] = { 12, -7, 5, -3, 0, -9, 8, -1, 6 };
    size_t n = sizeof(data) / sizeof(data[0]);

    (void)printf("Before: ");
    print_array(data, n);

    if (rearrange(data, n) != 0)
    {
        (void)fprintf(stderr, "Error: invalid array\n");
        return EXIT_FAILURE;
    }

    (void)printf("After:  ");
    print_array(data, n);

    return EXIT_SUCCESS;
}