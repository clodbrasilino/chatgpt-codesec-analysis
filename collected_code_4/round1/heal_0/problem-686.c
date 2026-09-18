#include <stdio.h>

void findFrequency(int arr[], int n)
{
    int count[10] = {0};

    for (int i=0; i<n; i++) {
        count[arr[i]]++;
    }

    for (int i=0; i<10; i++) {
        if (count[i] != 0) {
            printf("%d occurs %d times\n", i, count[i]);
        }
    }
}

int main()
{
    int arr[] = {1, 2, 2, 3, 3, 3, 4};
    int n = sizeof(arr)/sizeof(arr[0]);

    findFrequency(arr, n);

    return 0;
}