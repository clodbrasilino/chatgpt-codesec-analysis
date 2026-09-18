#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* findCommonSubsequence(char *str1, char *str2, char *str3, int m, int n, int o) {
    int L[m+1][n+1][o+1];
 
    for (int i=0; i<=m; i++) {
        for (int j=0; j<=n; j++) {
            for (int k=0; k<=o; k++) {
                if (i == 0 || j == 0|| k == 0)
                    L[i][j][k] = 0;
 
                else if (str1[i-1] == str2[j-1] && str1[i-1] == str3[k-1])
                    L[i][j][k] = L[i-1][j-1][k-1] + 1;
 
                else
                    L[i][j][k] = (L[i-1][j][k]>L[i][j-1][k])? 
                                 (L[i-1][j][k]>L[i][j][k-1]?
                                  L[i-1][j][k]:L[i][j][k-1]):
                                 (L[i][j-1][k]>L[i][j][k-1]?
                                  L[i][j-1][k]:L[i][j][k-1]);
            }
        }
    }
 
    int index = L[m][n][o];
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    char *subSeq = (char*)malloc(sizeof(char)*(index+1));
    subSeq[index] = '\0';
 
    int i = m, j = n, k = o;
    while (i > 0 && j > 0 && k > 0) {
        if (str1[i-1]==str2[j-1] && str1[i-1]==str3[k-1]) {
            subSeq[--index] = str1[i-1]; 
            i--; j--; k--; 
        }
        else if (L[i-1][j][k] >= L[i][j-1][k] && L[i-1][j][k] >= L[i][j][k-1])
            i--;
        else if (L[i][j-1][k] >= L[i][j][k-1])
            j--;
        else
            k--;
    }
 
    return subSeq;
}

int main(){
    char str1[100],str2[100],str3[100];
    printf("Enter first string: "); gets(str1);
    printf("Enter second string: "); gets(str2);
    printf("Enter third string: "); gets(str3);
    int m = strlen(str1);
    int n = strlen(str2);
    int o = strlen(str3);
    
    char *subseq = findCommonSubsequence(str1, str2, str3, m, n, o);
    printf("Longest Common Subsequence is %s", subseq);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'free' [-Wbuiltin-declaration-mismatch]
     */
    free(subseq);
    return 0;
}