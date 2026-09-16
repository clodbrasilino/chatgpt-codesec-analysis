#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm_two(int a, int b) {
    return a / gcd(a, b) * b;
}

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int find_lcm(int *array, int n) {
    int result = array[0];
    for (int i = 1; i < n; ++i) {
        result = lcm_two(result, array[i]);
    }
    return result;
}

int main() {
    int array[] = {2, 7, 3};
    int n = sizeof(array) / sizeof(array[0]);
    int lcm = find_lcm(array, n);
    printf("The LCM is %d\n", lcm);
    return 0;
}