#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

int extractMaxValue(char *str){
    int max = 0, num;
    char temp[100], *ptr;
    regex_t regex;
    regmatch_t matches[2];
 
    regcomp(&regex, "(\\d+)", REG_EXTENDED);
    ptr=str;
    
    while (!regexec(&regex, ptr, 2, matches, 0)) {
      int len = matches[1].rm_eo - matches[1].rm_so;
      strncpy(temp, ptr+matches[1].rm_so, len);
      temp[len] = '\0';
      num = atoi(temp);
  
      if (num > max)
          max = num;
  
      ptr += matches[0].rm_eo;
    }
  
    regfree(&regex);
    return max;
}

int main(void)
{
    char str[] = "This is a string with numbers 23, 345, 584 and 12";
    printf("Max value: %d\n", extractMaxValue(str));
    return 0;
}