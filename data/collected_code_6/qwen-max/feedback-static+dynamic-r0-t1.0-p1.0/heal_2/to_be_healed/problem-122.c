#include <stdio.h>
#include <stdbool.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 30, got 0
  *  test case 1 failed: expected 273, got 1
  *  test case 2 failed: expected 2664, got 0
  */

bool is_smart_number(long num) {
    int count = 0;
    for (int i = 2; i <= (int)sqrt(num); i++) {
        if (num % i == 0) {
            if (i == num / i) {
                count++;
            } else {
                count += 2;
            }
        }
    }
    return count > 0 && (count & (count - 1)) == 0;
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
    scanf("%d", &n);
    printf("%ld\n", nth_smart_number(n));
    return 0;
}