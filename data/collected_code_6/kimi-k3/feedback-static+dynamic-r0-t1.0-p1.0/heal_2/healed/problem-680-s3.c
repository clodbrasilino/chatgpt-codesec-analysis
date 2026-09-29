#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isIncreasingTrend(const int sequence[], size_t length) {
    if (sequence == NULL || length < 2) {
        return false;
    }
    
    for (size_t i = 1; i < length; i++) {
        if (sequence[i] <= sequence[i - 1]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    int test1[] = {1, 2, 3, 4, 5};
    int test2[] = {5, 4, 3, 2, 1};
    int test3[] = {1, 3, 2, 4, 5};
    int test4[] = {1};
    int test5[] = {2, 2, 3};
    
    printf("%s\n", isIncreasingTrend(test1, 5) ? "True" : "False");
    printf("%s\n", isIncreasingTrend(test2, 5) ? "True" : "False");
    printf("%s\n", isIncreasingTrend(test3, 5) ? "True" : "False");
    printf("%s\n", isIncreasingTrend(test4, 1) ? "True" : "False");
    printf("%s\n", isIncreasingTrend(test5, 3) ? "True" : "False");
    
    return EXIT_SUCCESS;
}