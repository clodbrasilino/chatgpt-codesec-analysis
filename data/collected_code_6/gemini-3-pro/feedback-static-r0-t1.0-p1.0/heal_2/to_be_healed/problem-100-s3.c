#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateNextPalindromeUtil(char *num, int n) {
    int mid = n / 2;
    int leftS = mid - 1;
    int rightS = n % 2 ? mid + 1 : mid;
    int i = leftS, j = rightS;
    int leftSmaller = 0;

    while (i >= 0 && num[i] == num[j]) {
        i--;
        j++;
    }

    if (i < 0 || num[i] < num[j]) {
        leftSmaller = 1;
    }

    while (i >= 0) {
        num[j] = num[i];
        j++;
        i--;
    }

    if (leftSmaller == 1) {
        int carry = 1;
        i = mid - 1;
        if (n % 2 == 1) {
            num[mid] += carry;
            carry = (num[mid] - '0') / 10;
            num[mid] = (num[mid] - '0') % 10 + '0';
            j = mid + 1;
        } else {
            j = mid;
        }

        while (i >= 0) {
            num[i] += carry;
            carry = (num[i] - '0') / 10;
            num[i] = (num[i] - '0') % 10 + '0';
            num[j++] = num[i--];
        }
    }
}

void findNextPalindrome(char *num) {
    if (num == NULL) return;
    
    int n = 0;
    /* Possible weaknesses found:
     *  Array index 'n' is used before limits check. [arrayIndexThenCheck]
     */
    while (num[n] != '\0' && n < 8192) {
        n++;
    }
    
    if (n == 0) return;

    int all9 = 1;
    for (int i = 0; i < n; i++) {
        if (num[i] != '9') {
            all9 = 0;
            break;
        }
    }

    if (all9) {
        char *new_num = (char *)malloc(n + 2);
        if (new_num == NULL) return;
        new_num[0] = '1';
        for (int i = 1; i < n; i++) {
            new_num[i] = '0';
        }
        new_num[n] = '1';
        new_num[n + 1] = '\0';
        printf("%s\n", new_num);
        free(new_num);
    } else {
        char *copy_num = strdup(num);
        if (copy_num == NULL) return;
        generateNextPalindromeUtil(copy_num, n);
        printf("%s\n", copy_num);
        free(copy_num);
    }
}

int main(void) {
    char num1[] = "94187978322";
    findNextPalindrome(num1);

    char num2[] = "999";
    findNextPalindrome(num2);

    char num3[] = "1234";
    findNextPalindrome(num3);

    return 0;
}