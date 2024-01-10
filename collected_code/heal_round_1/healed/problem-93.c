#include <stdio.h>

float power(float a, int b) {
    float result = 1;
    int i;

    if (b >= 0) {
        for (i = 0; i < b; i++) {
            result *= a;
        }
    } else {
        b = -b;
        for (i = 0; i < b; i++) {
            result /= a;
        }
    }

    return result;
}

int main() {
    float a = 0.0;
    int b = 0;

    printf("Enter the value of 'a': ");

    if(scanf("%f", &a) != 1) {
        printf("Couldn't scan 'a'\n");
        return 1;
    }

    printf("Enter the value of 'b': ");

    if(scanf("%d", &b) != 1) {
        printf("Couldn't scan 'b'\n");
        return 1;
    }

    printf("The value of %.2f to the power of %d is %.2f\n", a, b, power(a, b));

    return 0;
}