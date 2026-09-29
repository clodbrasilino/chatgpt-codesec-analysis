#include <stdio.h>
#include <math.h>
#include <limits.h>

int countDigits(int n) {
    if (n == 0) return 1;
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    return count;
}

int isArmstrong(int number) {
    int result = 0, n = 0, originalNumber = number;

    while (originalNumber != 0) {
        ++n;
        originalNumber /= 10;
    }

    originalNumber = number;
    while (originalNumber != 0) {
        int remainder = originalNumber % 10;
        if (remainder > 0 && INT_MAX / pow(remainder, n-1) < remainder) {
            return 0;
        }
        /* Possible weaknesses found:
         * UBSan: 3.48678e+09 is outside the range of representable values of type 'int' (AFL crash: id:000003,sig:06,src:000004,time:7114,execs:3055,op:havoc,rep:7)
         * UBSan: 2.32648e+09 is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000004,time:5213,execs:2257,op:havoc,rep:12)
         * UBSan: 4.1122e+09 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000004,time:1157,execs:507,op:havoc,rep:15)
         * UBSan: 2.32674e+09 is outside the range of representable values of type 'int' (AFL crash: id:000002,sig:06,src:000004,time:5863,execs:2537,op:havoc,rep:15)
         */
        result += pow(remainder, n);
        originalNumber /= 10;
    }

    return result == number;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    if (isArmstrong(num)) {
        printf("%d is an Armstrong number.\n", num);
    } else {
        printf("%d is not an Armstrong number.\n", num);
    }

    return 0;
}