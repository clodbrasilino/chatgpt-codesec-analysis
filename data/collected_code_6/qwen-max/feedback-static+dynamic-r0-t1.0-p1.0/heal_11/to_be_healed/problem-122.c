#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 273, got 0
  *  test case 2 failed: expected 2664, got 1
  *  test case 0 failed: expected 30, got 1
  */

bool is_smart_number(long num) {
    int count = 0;
    for (long i = 1; i * i <= num; i++) {
        if (num % i == 0) {
            if (i * i == num) {
                count++;
            } else {
                count += 2;
            }
        }
    }
    return (count & (count - 1)) == 0 && count > 0;
}

long nth_smart_number(int n) {
    long num = 1;
    int found = 0;
    while (true) {
        if (is_smart_number(num)) {
            found++;
            if (found == n) {
                return num;
            }
        }
        num++;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input\n");
        return 1;
    }
    long result = nth_smart_number(n);
    printf("%ld\n", result);
    return 0;
}