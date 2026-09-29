#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_valid_triangle(int angle1, int angle2, int angle3) {
    if (angle1 <= 0 || angle2 <= 0 || angle3 <= 0) {
        return false;
    }
    
    if (angle1 >= 180 || angle2 >= 180 || angle3 >= 180) {
        return false;
    }
    
    if (angle1 + angle2 + angle3 == 180) {
        return true;
    }
    
    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int angle1 = atoi(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int angle2 = atoi(argv[2]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int angle3 = atoi(argv[3]);
    
    if (is_valid_triangle(angle1, angle2, angle3)) {
        printf("Valid triangle\n");
    } else {
        printf("Invalid triangle\n");
    }
    
    return 0;
}