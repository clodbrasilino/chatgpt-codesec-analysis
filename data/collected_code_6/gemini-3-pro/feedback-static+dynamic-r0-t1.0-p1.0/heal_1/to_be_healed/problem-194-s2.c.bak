#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

long long octalToDecimal(const char *octalStr) {
    if (octalStr == NULL) {
        return -1;
    }

    size_t len = strlen(octalStr);
    if (len == 0) {
        return -1;
    }

    long long decimalNumber = 0;
    int power = 0;

    for (int i = len - 1; i >= 0; i--) {
        if (!isdigit((unsigned char)octalStr[i]) || octalStr[i] == '8' || octalStr[i] == '9') {
            return -1;
        }
        int digit = octalStr[i] - '0';
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -2635249153387078803 + -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:2562,execs:1050,op:havoc,rep:3)
         * UBSan: 9.22337e+18 is outside the range of representable values of type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:2562,execs:1050,op:havoc,rep:3)
         * UBSan: signed integer overflow: 5 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000005,time:2562,execs:1050,op:havoc,rep:3)
         */
        decimalNumber += digit * (long long)pow(8, power);
        power++;
    }

    return decimalNumber;
}

int main(void) {
    char input[64];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        long long result = octalToDecimal(input);
        
        if (result != -1) {
            printf("%lld\n", result);
            return EXIT_SUCCESS;
        } else {
            return EXIT_FAILURE;
        }
    }

    return EXIT_FAILURE;
}