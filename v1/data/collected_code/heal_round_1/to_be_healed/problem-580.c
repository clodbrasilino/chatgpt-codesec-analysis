#include <stdio.h>

void extractEvenElements(void *tuple) {
  if (tuple == NULL)
    return;

  void *innerTuple;
  int *number;
  innerTuple = *(void **)tuple;

  while (innerTuple != NULL) {
    /* Possible weaknesses found:
     *  read of 4 bytes from after the end of 'num1'
     *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
     */
    extractEvenElements(*((void **)innerTuple));
  
    /* Possible weaknesses found:
     *  read of 8 bytes from after the end of 'num1'
     *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
     */
    number = *(int **)(innerTuple + sizeof(void *));
    if (*number % 2 == 0)
      printf("%d\n", *number);
    
    /* Possible weaknesses found:
     *  read of 8 bytes from after the end of 'num1'
     *  stack-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
     */
    innerTuple = *(void **)(innerTuple + sizeof(void *) + sizeof(int *));
  }
}

int main() {
  int num1 = 1;
  int num2 = 2;
  int num3 = 3;
  int num4 = 4;
  int num5 = 5;

  void *innerTuple3[] = {&num5, NULL};
  void *innerTuple2[] = {&num4, innerTuple3};
  void *innerTuple1[] = {&num3, innerTuple2};
  void *tuple[] = {&num1, innerTuple1};

  extractEvenElements(tuple);

  return 0;
}