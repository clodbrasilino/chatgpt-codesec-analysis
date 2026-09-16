#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected [1, 3, 5, 7, 9], got <no output>
  *  test case 1 failed: expected [45, 67, 93], got <no output>
  *  test case 2 failed: expected [5, 7, 9, 3], got <no output>
  */

int* filter_odd_numbers(const int* numbers, size_t count, size_t* return_count) {
    *return_count = 0;
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % 2 != 0) {
            (*return_count)++;
        }
    }

    int* result = malloc(*return_count * sizeof(int));
    if (!result) {
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] % 2 != 0) {
            result[idx] = numbers[i];
            idx++;
        }
    }

    return result;
}

int main() {
    int numbers1[] = {1, 3, 5, 7, 9};
    size_t count1 = sizeof(numbers1) / sizeof(numbers1[0]);
    size_t return_count1 = 0;
    int* odd_numbers1 = filter_odd_numbers(numbers1, count1, &return_count1);

    if (odd_numbers1) {
        for (size_t i = 0; i < return_count1; i++) {
            printf("%d ", odd_numbers1[i]);
        }
        free(odd_numbers1);
        printf("\n");
    } else {
        printf("Memory allocation failed.\n");
    }

    int numbers2[] = {45, 67, 93};
    size_t count2 = sizeof(numbers2) / sizeof(numbers2[0]);
    size_t return_count2 = 0;
    int* odd_numbers2 = filter_odd_numbers(numbers2, count2, &return_count2);

    if (odd_numbers2) {
        for (size_t i = 0; i < return_count2; i++) {
            printf("%d ", odd_numbers2[i]);
        }
        free(odd_numbers2);
        printf("\n");
    } else {
        printf("Memory allocation failed.\n");
    }

    int numbers3[] = {5, 7, 9, 3};
    size_t count3 = sizeof(numbers3) / sizeof(numbers3[0]);
    size_t return_count3 = 0;
    int* odd_numbers3 = filter_odd_numbers(numbers3, count3, &return_count3);

    if (odd_numbers3) {
        for (size_t i = 0; i < return_count3; i++) {
            printf("%d ", odd_numbers3[i]);
        }
        free(odd_numbers3);
        printf("\n");
    } else {
        printf("Memory allocation failed.\n");
    }

    int numbers4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count4 = sizeof(numbers4) / sizeof(numbers4[0]);
    size_t return_count4 = 0;
    int* odd_numbers4 = filter_odd_numbers(numbers4, count4, &return_count4);

    if (odd_numbers4) {
        for (size_t i = 0; i < return_count4; i++) {
            printf("%d ", odd_numbers4[i]);
        }
        free(odd_numbers4);
        printf("\n");
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}