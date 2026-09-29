#include <stdio.h>

void decode_run_length(char *encoded_list) {
    int length;
    char letter;
    
    /* Possible weaknesses found:
     *  Cannot determine that 'encoded_list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; encoded_list[i] != '\0'; i += 2) {
        /* Possible weaknesses found:
         *  Cannot determine that 'encoded_list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        length = encoded_list[i] - '0';
        /* Possible weaknesses found:
         *  Cannot determine that 'encoded_list[i+1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        letter = encoded_list[i + 1];
        
        for (int j = 0; j < length; j++) {
            printf("%c", letter);
        }
    }
}

int main() {
    char encoded_list[] = "3a5b2c";
    decode_run_length(encoded_list);
    
    return 0;
}