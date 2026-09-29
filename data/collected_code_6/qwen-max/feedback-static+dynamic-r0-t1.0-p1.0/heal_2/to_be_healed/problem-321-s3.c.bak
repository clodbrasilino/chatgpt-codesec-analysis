#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long int get_demlo_number(int n) {
    if (n <= 0) return -1;
    if (n == 1) return 1;

    char num_str[20];
    sprintf(num_str, "%d", n);

    int len = strlen(num_str);
    char final_num[41] = "";

    for (int i = 0; i < len; ++i) {
        if (i == 0) {
            strncpy(final_num, num_str + i, 1);
        } else {
            char temp[41];
            strcpy(temp, final_num);
            strncat(temp, num_str + i, 1);
            strncat(temp, final_num, 1);
            for (int j = 0; j < i; j++) {
                strncat(temp, num_str + (len - j - 1), 1);
            }
            strcpy(final_num, temp);
        }
    }

    return atoll(final_num);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 4) on input id:000000,sig:04,src:000000,time:542,execs:231,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    long long int result = get_demlo_number(number);
    if (result != -1) {
        printf("Demlo number: %lld\n", result);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}