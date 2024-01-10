#include <regex.h>
 /* Possible weaknesses found:
  *  'NULL' is defined in header '<stddef.h>'; did you forget to '#include <stddef.h>'?
  *  include '<stdio.h>' or provide a declaration of 'snprintf'
  */

int checkPrecision(float decimal) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, "^[+-]?[0-9]+([.][0-9]{1,2})?$", REG_EXTENDED);
    if (reti) {
        return -1;
    }

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char buffer[20];
    /* Possible weaknesses found:
     *  include '<stdio.h>' or provide a declaration of 'snprintf'
     *  Cannot determine that 'buffer[0]' is initialized [premium-bughuntingUninit]
     *  implicit declaration of function 'snprintf' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'snprintf' [-Wbuiltin-declaration-mismatch]
     */
    snprintf(buffer, sizeof(buffer), "%.2f", decimal);

    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  'NULL' undeclared (first use in this function)
     */
    reti = regexec(&regex, buffer, 0, NULL, 0);
    regfree(&regex);

    return reti == 0 ? 1 : 0;
}