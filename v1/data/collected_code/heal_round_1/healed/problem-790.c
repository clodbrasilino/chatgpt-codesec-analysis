#include <stdbool.h>

bool checkEvenIndexHasEvenNumbers(int list[], int size) {
    for(int i = 0; i < size; i += 2) {
        if(list[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int size = 10;
    int list[size];
    for (int i = 0; i < size; i++) {
        list[i] = i;
    }
    bool result = checkEvenIndexHasEvenNumbers(list, size);

    return 0;
}