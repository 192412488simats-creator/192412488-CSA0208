#include <stdio.h>
char grade_if(int m){if(m<0||m>100)return '?';if(m>=90)return 'S';if(m>=80)return 'A';if(m>=70)return 'B';if(m>=60)return 'C';if(m>=50)return 'D';return 'F';}
char grade_switch(int m){if(m<0||m>100)return '?';switch(m/10){case 10:case 9:return 'S';case 8:return 'A';case 7:return 'B';case 6:return 'C';case 5:return 'D';default:return 'F';}}
int main(void){int a[]={100,90,89,85,84,80,79,75,74,70,69,60,59,50,49,0,-1,101};int i;for(i=0;i<18;i++)printf("%3d: ladder=%c switch=%c\\n",a[i],grade_if(a[i]),grade_switch(a[i]));return 0;}