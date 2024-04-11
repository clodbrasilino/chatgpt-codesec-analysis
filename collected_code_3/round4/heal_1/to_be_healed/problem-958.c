#include <stdio.h>
#include <stdlib.h>

char* intToRoman(int num) {
    char* result = (char*)malloc(sizeof(char) * 16);
    char* ptr = result;
    while(num != 0) {
        if(num >= 1000) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'M';
            num -= 1000;
        } else if(num >= 900) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'C';
            *ptr++ = 'M';
            num -= 900;
        } else if(num >= 500) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'D';
            num -= 500;
        } else if(num >= 400) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'C';
            *ptr++ = 'D';
            num -= 400;
        } else if(num >= 100) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'C';
            num -= 100;
        } else if(num >= 90) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'X';
            *ptr++ = 'C';
            num -= 90;
        } else if(num >= 50) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'L';
            num -= 50;
        } else if(num >= 40) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'X';
            *ptr++ = 'L';
            num -= 40;
        } else if(num >= 10) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'X';
            num -= 10;
        } else if(num >= 9) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'I';
            *ptr++ = 'X';
            num -= 9;
        } else if(num >= 5) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'V';
            num -= 5;
        } else if(num >= 4) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'I';
            *ptr++ = 'V';
            num -= 4;
        } else if(num >= 1) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *ptr++ = 'I';
            num -= 1;
        }
    }
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'ptr' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    *ptr = '\0';
    return result;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    char* roman = intToRoman(num);
    printf("Roman numeral: %s\n", roman);
    free(roman);
    return 0;
}