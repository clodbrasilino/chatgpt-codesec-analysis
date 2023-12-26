/* Possible weaknesses found:
 *  unknown type name 'bool'
 *  'bool' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
 */
bool containsK(int tuples[], int k, int size) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuples[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (tuples[i] == k) {
            /* Possible weaknesses found:
             *  'true' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
             *  'true' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             */
            return true;
        }
    }
    /* Possible weaknesses found:
     *  'false' undeclared (first use in this function)
     *  'false' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
     */
    return false;
}