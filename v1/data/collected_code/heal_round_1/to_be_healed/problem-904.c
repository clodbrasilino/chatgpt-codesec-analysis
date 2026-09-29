/* Possible weaknesses found:
 *  unknown type name 'bool'
 *  'bool' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
 */
bool isEven(int number) {
    if (number % 2 == 0) {
        /* Possible weaknesses found:
         *  'true' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
         *  'true' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        return true;
    } else {
        /* Possible weaknesses found:
         *  'false' undeclared (first use in this function)
         *  'false' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
         */
        return false;
    }
}