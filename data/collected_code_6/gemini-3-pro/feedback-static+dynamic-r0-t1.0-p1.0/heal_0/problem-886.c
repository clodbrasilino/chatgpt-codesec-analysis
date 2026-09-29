#include <stdio.h>
#include <stdlib.h>

double calculate_average(const int *list, size_t length) {
    if (list == NULL || length == 0) {
        return 0.0;
    }

    long long sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += list[i];
    }

    return (double)sum / (double)length;
}

int main(void) {
    int my_list[] = {10, 20, 30, 40, 50};
    size_t length = sizeof(my_list) / sizeof(my_list[0]);

    double average = calculate_average(my_list, length);
    
    printf("The average is: %.2f\n", average);

    return EXIT_SUCCESS;
}