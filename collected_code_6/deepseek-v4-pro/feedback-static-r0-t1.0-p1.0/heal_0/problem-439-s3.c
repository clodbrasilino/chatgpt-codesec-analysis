#include <stdio.h>
#include <stdlib.h>

long long convert_list_to_int(int *list, int size) {
    long long result = 0;
    int sign = 1;
    int i = 0;

    if (list == NULL || size <= 0) {
        return 0;
    }

    if (list[0] < 0) {
        sign = -1;
        result = -(long long)list[0];
        i = 1;
    }

    for (; i < size; i++) {
        int num = list[i];
        if (num < 0) {
            num = -num;
        }
        long long temp = num;
        int digits = 0;
        do {
            digits++;
            temp /= 10;
        } while (temp != 0);

        for (int j = 0; j < digits; j++) {
            result *= 10;
        }
        result += num;
    }

    return result * sign;
}

int main(void) {
    int numbers1[] = {12, 34, 56};
    int size1 = sizeof(numbers1) / sizeof(numbers1[0]);
    long long result1 = convert_list_to_int(numbers1, size1);
    printf("%lld\n", result1);

    int numbers2[] = {-12, 34, 56};
    int size2 = sizeof(numbers2) / sizeof(numbers2[0]);
    long long result2 = convert_list_to_int(numbers2, size2);
    printf("%lld\n", result2);

    int numbers3[] = {5};
    int size3 = sizeof(numbers3) / sizeof(numbers3[0]);
    long long result3 = convert_list_to_int(numbers3, size3);
    printf("%lld\n", result3);

    return 0;
}