#include <stdio.h>
#include <math.h>

float roundAndSum(const int list[], int length) {
    float sum = 0;
    
    for (int i = 0; i < length; i++) {
        sum += round(list[i]);
    }
    
    return sum * length;
}

int main() {
    int list[] = {2, 4, 7, 9, 12};
    int length = sizeof(list) / sizeof(list[0]);
    
    float result = roundAndSum(list, length);
    printf("Result: %f\n", result);
    
    return 0;
}