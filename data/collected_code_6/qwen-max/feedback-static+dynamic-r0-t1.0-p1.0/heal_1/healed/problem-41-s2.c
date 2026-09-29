#include <stdio.h>
#include <stdlib.h>

int* filter_even_numbers(const int* numbers, size_t count, size_t* result_count) {
    size_t even_count = 0;
    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] % 2 == 0) {
            even_count++;
        }
    }

    *result_count = even_count;
    if (even_count == 0) {
        return NULL;
    }

    int* filtered_numbers = (int*) malloc(even_count * sizeof(int));
    if (filtered_numbers == NULL) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] % 2 == 0) {
            filtered_numbers[index++] = numbers[i];
        }
    }

    return filtered_numbers;
}

void free_filtered_numbers(int* filtered_numbers) {
    free(filtered_numbers);
}

int main() {
    const int numbers1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t count1 = sizeof(numbers1) / sizeof(numbers1[0]);
    size_t result_count1;

    const int numbers2[] = {1, 3, 5, 7, 9};
    size_t count2 = sizeof(numbers2) / sizeof(numbers2[0]);
    size_t result_count2;

    const int numbers3[] = {2, 4, 6, 8};
    size_t count3 = sizeof(numbers3) / sizeof(numbers3[0]);
    size_t result_count3;

    const int numbers4[] = {10, 20, 84};
    size_t count4 = sizeof(numbers4) / sizeof(numbers4[0]);
    size_t result_count4;

    const int numbers5[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    size_t count5 = sizeof(numbers5) / sizeof(numbers5[0]);
    size_t result_count5;

    int* filtered_numbers1 = filter_even_numbers(numbers1, count1, &result_count1);
    int* filtered_numbers2 = filter_even_numbers(numbers2, count2, &result_count2);
    int* filtered_numbers3 = filter_even_numbers(numbers3, count3, &result_count3);
    int* filtered_numbers4 = filter_even_numbers(numbers4, count4, &result_count4);
    int* filtered_numbers5 = filter_even_numbers(numbers5, count5, &result_count5);

    if (filtered_numbers1 != NULL) {
        for (size_t i = 0; i < result_count1; ++i) {
            printf("%d ", filtered_numbers1[i]);
        }
        printf("\n");
        free_filtered_numbers(filtered_numbers1);
    } else {
        printf("Memory allocation failed\n");
    }

    if (filtered_numbers2 != NULL) {
        for (size_t i = 0; i < result_count2; ++i) {
            printf("%d ", filtered_numbers2[i]);
        }
        printf("\n");
        free_filtered_numbers(filtered_numbers2);
    } else {
        printf("No even numbers\n");
    }

    if (filtered_numbers3 != NULL) {
        for (size_t i = 0; i < result_count3; ++i) {
            printf("%d ", filtered_numbers3[i]);
        }
        printf("\n");
        free_filtered_numbers(filtered_numbers3);
    } else {
        printf("Memory allocation failed\n");
    }

    if (filtered_numbers4 != NULL) {
        for (size_t i = 0; i < result_count4; ++i) {
            printf("%d ", filtered_numbers4[i]);
        }
        printf("\n");
        free_filtered_numbers(filtered_numbers4);
    } else {
        printf("Memory allocation failed\n");
    }

    if (filtered_numbers5 != NULL) {
        for (size_t i = 0; i < result_count5; ++i) {
            printf("%d ", filtered_numbers5[i]);
        }
        printf("\n");
        free_filtered_numbers(filtered_numbers5);
    } else {
        printf("No even numbers\n");
    }

    return 0;
}