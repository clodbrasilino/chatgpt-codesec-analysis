/* Possible weaknesses found:
 *  unknown type name 'bool'
 *  'bool' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
 */
bool isIncreasing(int numbers[], int length) {
    for (int i = 1; i < length; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'numbers[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'numbers[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (numbers[i] <= numbers[i - 1]) {
            /* Possible weaknesses found:
             *  'false' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             *  'false' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
             */
            return false;
        }
    }
    /* Possible weaknesses found:
     *  'true' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
     *  'true' undeclared (first use in this function)
     */
    return true;
}