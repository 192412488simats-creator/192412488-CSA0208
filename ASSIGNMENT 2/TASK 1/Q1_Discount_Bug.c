#include <stdio.h>
int main(void){
 double price,qty,gross,discount,tax,total,net,wrong; int senior,count=0;
 printf("Enter price quantity senior(1=yes,0=no): ");
 if(scanf("%lf%lf%d",&price,&qty,&senior)!=3||price<0||qty<0||(senior!=0&&senior!=1)){puts("Invalid input");return 1;}
 wrong=price*qty-price*qty*15/100*senior+price*qty*5/100;
 gross=price*qty; discount=senior?gross*0.15:0; tax=(gross-discount)*0.05;
 total=gross-discount+tax; net=total>1000?total-50:total;
 printf("Original total=%.2f\\nCorrect gross=%.2f discount=%.2f GST=%.2f\\nTotal=%.2f Payable=%.2f\\n",wrong,gross,discount,tax,total,net);
 count++; printf("Safe count=%d\\n",count);
 return 0;
}