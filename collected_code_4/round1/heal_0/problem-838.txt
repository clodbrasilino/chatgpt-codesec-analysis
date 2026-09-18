#include <stdio.h>
#include <string.h>

int minSwaps(char *str1, char *str2, int n)
{
    int countx = 0, county = 0;
    for (int i = 0; i < n; i++)
    {
      if (str1[i] != str2[i] && str1[i] == '1')
          countx++;
      else if (str1[i] != str2[i] && str1[i] == '0')
          county++;
    }

    if (countx != county && (countx-county) != 1)
    {
      return -1;
    }

    return countx;
}

int main()
{
    char str1[] = "1100";
    char str2[] = "1010";
    int n = strlen(str1);
    int result = minSwaps(str1, str2, n);

    if(result == -1)
      printf("Not possible\n");
    else
      printf("Minimum swaps required = %d\n", result);

    return 0;
}