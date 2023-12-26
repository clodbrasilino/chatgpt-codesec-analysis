/* Possible weaknesses found:
 *  unknown type name 'bool'
 *  'bool' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
 */
int countTrueBooleans(bool list[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list[i]) {
            count++;
        }
    }
    return count;
}