#include <stdio.h>
#include <stdbool.h>

bool is_sum_of_divisors_same(int num1, int num2) {
    int sum1 = 0, sum2 = 0;
    for (int i = 1; i * i <= num1; ++i) {
        if (num1 % i == 0) {
            sum1 += i;
            if (i != num1 / i) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1478708443 + 739354220 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1601,execs:478,op:havoc,rep:3)
                 */
                sum1 += num1 / i;
            }
        }
    }
    for (int i = 1; i * i <= num2; ++i) {
        if (num2 % i == 0) {
            sum2 += i;
            if (i != num2 / i) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: 1890882366 + 420196080 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000001,time:14550,execs:4104,op:havoc,rep:3)
                 * UBSan: signed integer overflow: 1842981511 + 614327169 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:9631,execs:2724,op:havoc,rep:7)
                 */
                sum2 += num2 / i;
            }
        }
    }
    return sum1 == sum2;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:12,execs:16,op:(null),pos:0; likely memory-safety defect
  */

int main() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    if (is_sum_of_divisors_same(a, b)) {
        printf("The sum of divisors is the same.\n");
    } else {
        printf("The sum of divisors is not the same.\n");
    }
    return 0;
}