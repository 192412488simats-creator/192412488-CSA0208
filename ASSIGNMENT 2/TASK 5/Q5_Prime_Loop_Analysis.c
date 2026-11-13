#include <stdio.h>
unsigned long checks;
int basic(unsigned long n){unsigned long i;checks=0;if(n<2)return 0;for(i=2;i<n;i++){checks++;if(n%i==0)return 0;}return 1;}
int prime_for(unsigned long n){unsigned long i;checks=0;if(n<2)return 0;for(i=2;i<=n/i;i++){checks++;if(n%i==0)return 0;}return 1;}
int prime_while(unsigned long n){unsigned long i=2;checks=0;if(n<2)return 0;while(i<=n/i){checks++;if(n%i==0)return 0;i++;}return 1;}
int prime_do(unsigned long n){unsigned long i=2;checks=0;if(n<2)return 0;do{if(i>n/i)break;checks++;if(n%i==0)return 0;i++;}while(i<=n/i);return 1;}
int main(void){unsigned long a[]={2,3,97,100,7919,1000003};int k,p;for(k=0;k<6;k++){p=prime_for(a[k]);printf("%8lu %-8s improved=%lu",a[k],p?"prime":"not prime",checks);p=basic(a[k]);printf(" basic=%lu\\n",checks);}p=prime_while(7919);printf("while 7919=%s checks=%lu\\n",p?"prime":"not prime",checks);p=prime_do(7919);printf("do-while 7919=%s checks=%lu\\n",p?"prime":"not prime",checks);return 0;}