#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
int main(void)
{
    float dollars;
    do{
        dollars=get_float("Change owed:");
    }
    while(dollars<0);
    int cents = round(dollars * 100);
    int number=0,a=0,b=0,c=0;
        a=cents/25;
        number=number+a;
        b=(cents%25)/10;
        number=number+b;
        c=((cents%25)%10)/5;
        number=number+c;
        number=number+((cents%25)%10)%5;
        printf("%i\n",number);
        
    
    
}