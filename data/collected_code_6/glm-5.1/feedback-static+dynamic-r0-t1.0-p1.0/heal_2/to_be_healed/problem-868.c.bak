#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 0 failed: expected 8, got <no output>
  *  test case 1 failed: expected 3, got <no output>
  */

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }
    
    int len = strlen(s);
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
 */
int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    int result = lengthOfLastWord(argv[1]);
    printf("%d\n", result);
    
    return 0;
}