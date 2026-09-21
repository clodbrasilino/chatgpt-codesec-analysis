#include <stdio.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'str' can be declared as pointer to const [constParameterPointer]
 */
int countFlipsToAlternate(char *str) {
    int flipsFor01 = 0, flipsFor10 = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if ((i % 2 == 0 && str[i] != '0') || (i % 2 != 0 && str[i] != '1')) {
            flipsFor01++;
        } else if ((i % 2 == 0 && str[i] != '1') || (i % 2 != 0 && str[i] != '0')) {
            flipsFor10++;
        }
    }
    return flipsFor01 < flipsFor10 ? flipsFor01 : flipsFor10;
}

int main() {
    char binaryStr[] = "00101010";
    /* Possible weaknesses found:
     *  Value stored to 'length' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'length' is assigned a value that is never used. [unreadVariable]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(binaryStr);
    int minFlips = countFlipsToAlternate(binaryStr);
    printf("Minimum number of flips: %d\n", minFlips);
    return 0;
}