#include <stdio.h>
unsigned long checks;
int original(unsigned long n){unsigned long i;checks=0;if(n<2)return 0;for(i=2;i<=n/i;i++){checks++;if(n%i==0)return 0;}return 1;}
int redesigned(unsigned long n){unsigned long i;checks=0;if(n<2)return 0;if(n==2)return 1;checks++;if(n%2==0)return 0;for(i=3;i<=n/i;i+=2){checks++;if(n%i==0)return 0;}return 1;}
int main(void){unsigned long a[]={97,100,7919,1000003},old;int k,p;for(k=0;k<4;k++){p=original(a[k]);old=checks;p=redesigned(a[k]);printf("%8lu %s original=%lu redesigned=%lu\\n",a[k],p?"prime":"not prime",old,checks);}return 0;}