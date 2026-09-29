#include <stdio.h>
#include <stdbool.h>
#define SIZE 100

bool is_sequence_match(int arr[], int n, int pat[], int m) {
  if (m > n) {
    return false;
  }
  int i = 0;
  int j = 0;
  while (i < n && j < m) {
    if (arr[i] == pat[j]) {
      j++;
    }
    i++;
  }
  return j == m;
}

int main() {
  int arr[SIZE];
  int pattern[SIZE];
  int n, m, i;
  
  printf("Enter number of elements in array: ");
  scanf("%d", &n);
  printf("Enter array elements: ");
  for(i=0; i<n; i++) {
    scanf("%d", &arr[i]);
  }

  printf("Enter number of elements in pattern: ");
  scanf("%d", &m);
  printf("Enter pattern elements: ");
  for(i=0; i<m; i++) {
    scanf("%d", &pattern[i]);
  }
  
  if (is_sequence_match(arr, n, pattern, m)) {
    printf("Array follows the sequence given in the pattern.\n");
  } else {
    printf("Array does not follow the sequence given in the pattern.\n");
  }

  return 0;
}