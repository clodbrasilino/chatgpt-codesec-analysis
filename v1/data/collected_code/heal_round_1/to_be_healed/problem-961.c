/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strlen'
 */
int romanToInt(char *s) {
    int result = 0;
    int i;
    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strlen'
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 's[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     */
    int length = strlen(s);

    for (i = 0; i < length; i++) {
        switch(s[i]) {
            case 'I':
                if (s[i + 1] == 'V' || s[i + 1] == 'X') {
                    result -= 1;
                } else {
                    result += 1;
                }
                break;
            case 'V':
                result += 5;
                break;
            case 'X':
                if (s[i + 1] == 'L' || s[i + 1] == 'C') {
                    result -= 10;
                } else {
                    result += 10;
                }
                break;
            case 'L':
                result += 50;
                break;
            case 'C':
                if (s[i + 1] == 'D' || s[i + 1] == 'M') {
                    result -= 100;
                } else {
                    result += 100;
                }
                break;
            case 'D':
                result += 500;
                break;
            case 'M':
                result += 1000;
                break;
        }
    }
    return result;
}