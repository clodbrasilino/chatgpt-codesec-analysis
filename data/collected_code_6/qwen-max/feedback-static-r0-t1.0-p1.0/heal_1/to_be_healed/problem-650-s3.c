#include <stdbool.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  'size_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
  */

/* Possible weaknesses found:
 *  unknown type name 'size_t'
 */
bool are_arrays_equal(const uint32_t *array1, const uint32_t *array2, size_t length) {
    /* Possible weaknesses found:
     *  use of undeclared identifier 'i'
     *  use of undeclared identifier 'size_t'; did you mean 'sizeof'?
     */
    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'i'
         */
        if (array1[i] != array2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    uint32_t array1[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  Variable 'array2' can be declared as const array [constVariable]
     */
    uint32_t array2[] = {1, 2, 3, 4, 5};
    /* Possible weaknesses found:
     *  use of undeclared identifier 'size_t'; did you mean 'sizeof'?
     *  'size_t' is defined in header '<stddef.h>'; this is probably fixable by adding '#include <stddef.h>'
     *  unknown type name 'size_t'
     *  use of undeclared identifier 'length'
     */
    size_t length = sizeof(array1) / sizeof(array1[0]);

    /* Possible weaknesses found:
     *  implicit declaration of function 'are_arrays_equal' [-Wimplicit-function-declaration]
     *  use of undeclared identifier 'length'
     */
    bool result = are_arrays_equal(array1, array2, length);
    return (result ? 0 : 1);
}