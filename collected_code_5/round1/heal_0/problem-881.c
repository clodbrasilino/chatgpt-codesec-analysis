#include <stdio.h>

int sumOfFirstEvenAndOdd(int list[], int len) {
    int i, even = -1, odd = -1;
    for(i = 0; i < len; i++) {
        if(list[i] % 2 == 0 && even == -1)
            even = list[i];
        else if(list[i] % 2 == 1 && odd == -1)
            odd = list[i];
            
        if(even != -1 && odd != -1)
            break;
    }
    
    if(even == -1 || odd == -1)
        return -1;
    
    return even + odd;
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int result;
    
    result = sumOfFirstEvenAndOdd(arr, 5);
    
    if(result != -1)
        printf("The sum of the first even and odd number is %d\n", result);
    else
        printf("Invalid input. No sum possible.\n");

    return 0;
}