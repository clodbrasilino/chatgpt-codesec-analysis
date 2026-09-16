#include <stdio.h>
#include <stdbool.h>

bool checkOddIndexOddNumber(const int* array, size_t length) {
    if (array == NULL && length > 0) {
        return false;
    }
    
    for (size_t i = 1; i < length; i += 2) {
        if (array[i] % 2 == 0) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int validList[] = {2, 3, 4, 5, 6, 7};
    size_t validListLength = sizeof(validList) / sizeof(validList[0]);
    
    if (checkOddIndexOddNumber(validList, validListLength)) {
        printf("Valid list: Every odd index contains an odd number.\n");
    } else {
        printf("Valid list: Condition not met.\n");
    }
    
    int invalidList[] = {2, 3, 4, 6, 6, 7};
    size_t invalidListLength = sizeof(invalidList) / sizeof(invalidList[0]);
    
    if (checkOddIndexOddNumber(invalidList, invalidListLength)) {
        printf("Invalid list: Every odd index contains an odd number.\n");
    } else {
        printf("Invalid list: Condition not met.\n");
    }
    
    return 0;
}