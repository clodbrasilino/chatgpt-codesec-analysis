#include <stdbool.h>

bool isEven(int number) {
    if (number % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int testNumber = 10;
    bool result = isEven(testNumber);

    return 0; 
}