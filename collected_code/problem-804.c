#include <stdbool.h>

bool isProductEven(int num1, int num2) {
    int product = num1 * num2;
    
    if (product % 2 == 0) {
        return true;
    } else {
        return false;
    }
}