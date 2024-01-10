#include <stdbool.h>

bool checkTuple(const int tuple[], int size) {
    for (int i = 0; i < size; i++) {
        if (tuple[i] < 0) {
            return false;
        }
    }
    return true;
}

int main(void){
    int array[] = {0, 1, 2, 3, 4};
    int n = sizeof(array) / sizeof(array[0]);

    bool result = checkTuple(array, n);
    return 0;
}