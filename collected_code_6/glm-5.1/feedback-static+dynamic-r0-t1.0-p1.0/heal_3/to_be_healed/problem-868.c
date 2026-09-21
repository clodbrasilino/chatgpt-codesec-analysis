#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 8, got <no output>
  *  test case 2 failed: expected 0, got <no output>
  *  test case 1 failed: expected 3, got <no output>
  */

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }
    
    int len = 0;
    while (s[len] != '\0') {
        len++;
    }
    
    int i = len - 1;
    
    while (i >= 0 && s[i] == ' ') {
        i--;
    }
    
    if (i < 0) {
        return 0;
    }
    
    int count = 0;
    while (i >= 0 && s[i] != ' ') {
        count++;
        i--;
    }
    
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc < 2) {
        return 1;
    }
    
    int result = lengthOfLastWord(argv[1]);
    printf("%d\n", result);
    
    return 0;
}