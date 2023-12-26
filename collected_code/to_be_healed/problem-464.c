#include <stdio.h>
#include <stdbool.h>

bool checkAllValuesSame(int dictionary[], int size) {
    if (size == 0) {
        return true;
    }
    
    /* Possible weaknesses found:
     *  Cannot determine that 'dictionary[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int firstValue = dictionary[0];
    
    for (int i = 1; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'dictionary[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (dictionary[i] != firstValue) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int dictionary[] = {5, 5, 5, 5};
    int size = sizeof(dictionary) / sizeof(dictionary[0]);
    
    if (checkAllValuesSame(dictionary, size)) {
        printf("All values are the same.\n");
    } else {
        printf("Values are different.\n");
    }
    
    return 0;
}