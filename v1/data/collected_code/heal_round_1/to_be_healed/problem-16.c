#include <stdio.h>

void find_sequential_lowercase(char* input_string) {
    int start = -1, end = -1;
    /* Possible weaknesses found:
     *  Cannot determine that 'input_string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (int i = 0; input_string[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'input_string[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (input_string[i] >= 'a' && input_string[i] <= 'z') {
            if (start == -1) {
                start = i;
            }
            end = i;
        }
        else {
            if (start != -1 && end != -1) {
                for (int j = start; j <= end; j++) {
                    /* Possible weaknesses found:
                     *  Cannot determine that 'input_string[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
                     */
                    printf("%c", input_string[j]);
                }
                printf("\n");
                start = end = -1;
            }
        }
    }
    if (start != -1 && end != -1) {
        for (int j = start; j <= end; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'input_string[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%c", input_string[j]);
        }
        printf("\n");
    }
}

int main() {
    char* input = "this_is_a_test_string";
    find_sequential_lowercase(input);
    return 0;
}