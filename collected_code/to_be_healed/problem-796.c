#include <stdio.h>

int getSum(int dictionary[], int size){
    int sum = 0;
    
    for(int i = 0; i < size; i++){
        /* Possible weaknesses found:
         *  Cannot determine that 'dictionary[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum += dictionary[i];
    }
    
    return sum;
}

int main(){
    int dictionary[] = {1, 2, 3, 4, 5};
    int size = sizeof(dictionary) / sizeof(dictionary[0]);
    
    int sum = getSum(dictionary, size);
    
    printf("Sum of all items in the dictionary: %d\n", sum);
    
    return 0;
}