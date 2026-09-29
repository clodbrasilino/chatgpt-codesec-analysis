#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int binaryToDecimal(char *n) {
  char *pt;
  int length = strlen(n) - 1;
  int decimal = 0, base = 1, temp;
  
  for(pt = n + length; pt >= n; --pt) {
    if (*pt == '1') {
      temp = 1;
    } else if (*pt == '0') {
      temp = 0;
    } else {
      return -1;
    }
    decimal += temp * base;
    base = base * 2;
  }
  return decimal;
}

int countOddRotations(char* binStr) {
    int count = 0;
    int length = strlen(binStr);
    char* rotatedStr = (char*)malloc((length + 1) * sizeof(char));
    if(!rotatedStr) {
        return -1;
    }
    
    for(int i = 0; i < length; i++) {
        memcpy(rotatedStr, binStr + i, length - i);
        memcpy(rotatedStr + length - i, binStr, i);
        rotatedStr[length] = '\0';
        
        int decimal = binaryToDecimal(rotatedStr);
        if(decimal == -1) {
            free(rotatedStr);
            return -1;
        }
        if(decimal % 2 != 0) {
            count++;
        }
    }

    free(rotatedStr);
    return count;
}

int main() {
    char string[] = "1011";
    int count = countOddRotations(string);
    if (count == -1) {
        printf("Invalid binary string");
        return 0;
    }
    printf("Count of rotations = %d", count);
    return 0;
}
