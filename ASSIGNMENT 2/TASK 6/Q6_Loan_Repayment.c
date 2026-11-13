#include <stdio.h>
int main(void){
 double principal,rate,payment,balance,interest,total=0;int month=0;const int LIMIT=360;
 printf("Enter loan amount, monthly interest rate percent, repayment: ");
 if(scanf("%lf%lf%lf",&principal,&rate,&payment)!=3||principal<=0||rate<0||payment<=0){puts("Invalid input");return 1;}
 balance=principal;puts("\\nMonth  Due after interest  Payment  Balance");
 while(balance>0.005){
  interest=balance*rate/100.0;
  if(payment<=interest){puts("Repayment must be greater than monthly interest.");return 0;}
  {double due=balance+interest;double paid=payment<due?payment:due;balance=due-paid;total+=interest;month++;printf("%5d %18.2f %8.2f %9.2f\\n",month,due,paid,balance);}
  if(month>=LIMIT&&balance>0.005){printf("Safety limit %d reached; loan remains unpaid.\\n",LIMIT);break;}
 }
 if(balance<=0.005)printf("Repaid in %d months. Total interest=Rs %.2f\\n",month,total);
 return 0;
}