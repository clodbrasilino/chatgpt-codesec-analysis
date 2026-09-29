#include <stdbool.h>

bool checkEvenIndexHasEvenNumbers(int list[], int size) {
    for(int i = 0; i < size; i += 2) {
        if(list[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}