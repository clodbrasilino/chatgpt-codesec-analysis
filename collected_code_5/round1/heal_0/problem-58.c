#include <stdio.h>

int haveOppositeSigns(int x, int y) {
   return ((x ^ y) < 0);
}

int main() {
    int num1 = 10;
    int num2 = -20;
    if(haveOppositeSigns(num1, num2)) {
        printf("Numbers have opposite signs.\n");
    } else {
        printf("Numbers don't have opposite signs.\n");
    }
    
    return 0;
}