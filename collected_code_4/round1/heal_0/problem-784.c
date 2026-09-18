#include <stdio.h>

int find_product(int array[], int size)
{
    int first_even = -1;
    int first_odd = -1;
    for(int i = 0; i < size; i++)
    {
        if(array[i] % 2 == 0 && first_even == -1) {
            first_even = array[i];
        }
        else if(array[i] % 2 != 0 && first_odd == -1) {
            first_odd = array[i];
        }
        
        if(first_even != -1 && first_odd != -1) {
            break;
        }
    }
    
    if(first_even == -1 || first_odd == -1) {
        return -1;
    }
    return first_even * first_odd;
}

int main()
{
    int array[] = {1, 3, 5, 2, 4, 6};
    int size = sizeof(array)/sizeof(array[0]);
    int product = find_product(array, size);
    if(product == -1) {
        printf("Array doesn't have both even and odd number.");
    }
    else {
        printf("The product of first even and first odd number is: %d", product);
    }
    return 0;
}