#include <stdbool.h>
 /* Possible weaknesses found:
  *  'NULL' is defined in header '<stddef.h>'; did you forget to '#include <stddef.h>'?
  */

bool matchString(const char* string) {
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'NULL' undeclared (first use in this function)
     */
    if (string == NULL) {
        return false;
    }

    bool foundA = false;
    int countB = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == 'a') {
            foundA = true;
        } else if (string[i] == 'b') {
            if (!foundA) {
                return false;
            }
            countB++;
        } else {
            return false;
        }
    }

    return countB > 0;
}