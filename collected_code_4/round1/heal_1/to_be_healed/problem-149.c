#include <stdio.h>
#include <stdlib.h>

int* longestSubsequence(int* arr, int n, int* returnSize){
  int length = 1;
  int maxLength = 1;
  int start = 0;

  for(int i=1; i<n; i++){
    if(abs(arr[i-1] - arr[i]) == 1)
      length++;
    else{
      if(length > maxLength){
        maxLength = length;
        start = i - maxLength;
      }
      length = 1;
    }
  }

  if(length > maxLength){
    maxLength = length;
    start = n - maxLength;
  }

  *returnSize = maxLength;
  int* subsequence = (int*) malloc(sizeof(int) * maxLength);

  for(int i = 0; i<maxLength; i++)
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'subsequence' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    subsequence[i] = arr[start++];
    
  return subsequence;
}

int main(){
  int arr[] = {1, 2, 3, 4, 5, 3, 2, 3, 7, 8, 9};
  int n = sizeof(arr)/sizeof(arr[0]);

  int returnSize;
  int* result = longestSubsequence(arr, n, &returnSize);

  printf("Longest subsequence is: ");
  for(int i=0; i<returnSize; i++)
    printf("%d ", result[i]);
    
  free(result);
  
  return 0;
}