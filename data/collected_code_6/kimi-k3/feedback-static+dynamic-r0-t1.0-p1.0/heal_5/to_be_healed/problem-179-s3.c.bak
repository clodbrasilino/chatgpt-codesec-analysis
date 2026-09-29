#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

int isKeith(int num) {
    if (num < 10) {
        return 0;
    }
    
    int temp = num;
    int count = 0;
    
    while (temp > 0) {
        temp /= 10;
        count++;
    }
    
    int *arr = (int *)malloc(count * sizeof(int));
    if (arr == NULL) {
        return 0;
    }
    
    temp = num;
    for (int i = count - 1; i >= 0; i--) {
        arr[i] = temp % 10;
        temp /= 10;
    }
    
    int nextTerm = 0;
    int i = count;
    
    while (nextTerm < num) {
        nextTerm = 0;
        for (int j = 1; j <= count; j++) {
            nextTerm += arr[i - j];
        }
        
        if (nextTerm == num) {
            free(arr);
            return 1;
        }
        
        for (int j = 0; j < count - 1; j++) {
            arr[j] = arr[j + 1];
        }
        arr[count - 1] = nextTerm;
        i++;
    }
    
    free(arr);
    return 0;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    int num = atoi(argv[1]);
    
    if (isKeith(num)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}