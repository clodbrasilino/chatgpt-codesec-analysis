#include <stdio.h>
#include <stdlib.h>

void findLucky(int n) {
  int lucky[100] = {3, 7}, p2 = 0, p3 = 0, i, nextVal;
  for(int arrSize = 2; arrSize < n;) {
    p2++;
    p3++;
    if(lucky[p2]*3 < lucky[p3]*7) {
      lucky[arrSize] = lucky[p2]*3;
      if(lucky[arrSize] > lucky[arrSize - 1]) {
        arrSize++;
      }
    } else if(lucky[p2]*3 > lucky[p3]*7) {
      lucky[arrSize] = lucky[p3]*7;
      if(lucky[arrSize] > lucky[arrSize - 1]) {
        arrSize++;
      }
      p2--; 
    } else {
      lucky[arrSize] = lucky[p2]*3;
      if(lucky[arrSize] > lucky[arrSize - 1]) {
        arrSize++;
      }
    }
  }
  for(i = 0; i < n; i++) {
    printf("%d ", lucky[i]);
  }
}

int main() {
  int n;
  printf("Enter the value of n: ");
  scanf("%d", &n);
  findLucky(n);
  return 0;
}