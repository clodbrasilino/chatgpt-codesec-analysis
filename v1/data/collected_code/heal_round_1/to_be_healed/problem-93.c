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
    float a;
    int b;

    printf("Enter the value of 'a': ");
    /* Possible weaknesses found:
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &a);

    printf("Enter the value of 'b': ");
    /* Possible weaknesses found:
     *  Cannot determine that 'b' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &b);

    /* Possible weaknesses found:
     *  Cannot determine that 'a' is initialized [premium-bughuntingUninit]
     */
    printf("The value of %.2f to the power of %d is %.2f\n", a, b, power(a, b));

    return 0;
}