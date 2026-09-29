#include <stdio.h>
#include <string.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permute(char *str, int left, int right) {
    if (left == right) {
        printf("%s\n", str);
        return;
    }
    for (int i = left; i <= right; i++) {
        swap(&str[left], &str[i]);
        permute(str, left + 1, right);
        swap(&str[left], &str[i]);
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100] = {0};
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(str, sizeof(str));
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     *  Condition 'len>0' is always true
     */
    if (len > 0 && (int)(len - 1) >= 0) {
        permute(str, 0, (int)len - 1);
    }
    
    return 0;
}