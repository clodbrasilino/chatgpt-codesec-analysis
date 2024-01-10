#include <stdio.h>
#include <stdbool.h>

bool checkAllValuesSame(const int dictionary[], int size) {
    if (size == 0) {
        return true;
    }
    
    int firstValue = dictionary[0];
    
    for (int i = 1; i < size; i++) {
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