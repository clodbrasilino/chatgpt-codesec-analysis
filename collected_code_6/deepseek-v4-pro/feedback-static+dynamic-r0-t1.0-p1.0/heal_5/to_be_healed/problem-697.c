#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 3, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

int count_even(const int *list, int size) {
    if (list == NULL || size <= 0) {
        return 0;
    }
    
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5, 6};
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int result1 = count_even(list1, size1);
    printf("Even count: %d\n", result1);
    
    int list2[] = {2, 4, 6, 8};
    int size2 = sizeof(list2) / sizeof(list2[0]);
    int result2 = count_even(list2, size2);
    printf("Even count: %d\n", result2);
    
    int result3 = count_even(NULL, 5);
    printf("Even count: %d\n", result3);
    
    int list4[] = {1, 3, 5, 7};
    int size4 = sizeof(list4) / sizeof(list4[0]);
    int result4 = count_even(list4, size4);
    printf("Even count: %d\n", result4);
    
    return 0;
}