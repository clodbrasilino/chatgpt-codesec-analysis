#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return -1;
    }

    long long decimalValue = 0;
    int length = strlen(binaryString);

    for (int i = 0; i < length; i++) {
        if (binaryString[i] != '0' && binaryString[i] != '1') {
            return -1; 
        }
        
        int bit = binaryString[i] - '0';
        /* Possible weaknesses found:
         * UBSan: left shift of 9223091111130497024 by 1 places cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000006,time:8376,execs:3845,op:havoc,rep:3)
         */
        decimalValue = (decimalValue << 1) | bit;
    }

    return decimalValue;
}

int main() {
    char binaryString[65]; 

    if (fgets(binaryString, sizeof(binaryString), stdin) != NULL) {
        binaryString[strcspn(binaryString, "\n")] = '\0';

        long long result = binaryToDecimal(binaryString);

        if (result != -1) {
            printf("%lld\n", result);
        } else {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}