#include <stdio.h>

int sum_positives(int *data, int size)
{
    int sum = 0;
    if(data == NULL || size <= 0)
        return sum;

    for(int i=0; i<size; i++)
    {
        if(data[i] > 0)
            sum += data[i];
    }

    return sum;
}

int main()
{
    int data[] = {1, -2, 3, 4, -5};
    int size = sizeof(data)/sizeof(data[0]);

    printf("Sum of positive numbers: %d\n", sum_positives(data, size));

    return 0;
}