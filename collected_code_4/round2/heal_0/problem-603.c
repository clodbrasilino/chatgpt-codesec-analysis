```


#include <stdio.h>
#include <stdlib.h>  

int lucid(int n);

int check_lucid(int num);

int main()
{
    int n;
  
    printf("Enter an integer: ");
    scanf("%d", &n);
  
    printf("The largest lucid number smaller than or equal to %d is: ", n);
    printf("%d\n", lucid(n));
  
    return 0;
}

int lucid(int n) {
    while(n >= 0) {
        if(check_lucid(n))
            return n;
        
        --n;
    }
    
    return -1;
}

int check_lucid(int num) {
	int r,sum=0,tmp;    	
	tmp=num;    
	while(num>0)    
	{    
		r=num%10;    
		sum=(sum*10)+r;    
		num=num/10;    
	}    
    
	if(tmp==sum)
		return 1;   
	else      	
		return 0;  
}