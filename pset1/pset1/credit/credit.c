#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long a = get_long("Number:");
    int sum=0,i,c;
    long long b=a;
    for(i=0;a!=0;i++)
    {
        c=(a%10)*(1+i%2);
        if(c>9)
        c=c/10+c%10;
        sum=sum+c;
        a/=10;
    }
    if((sum%10)!=0)
    {
        printf("INVALID\n");
    }
    else
    {
        int d=b/10000000000000;
        int e=b/100000000000000;
        int t;
          for(int j=0;j<i-1;j++)
        {
            b=b/10;
            t=b;
        }
        if((i==15)&&((d==34)||(d==37)))
        {
            printf("AMEX\n");
        }
        else if((i==16)&&(e>=51)&&(e<=55))
        {
            printf("MASTERCARD\n");
        }
        else if((i>=13)&&(i<=16)&&(t==4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n"); 
        }
    }
    return 0;
}