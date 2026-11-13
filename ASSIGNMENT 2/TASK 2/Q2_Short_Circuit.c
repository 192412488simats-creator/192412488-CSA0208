#include <stdio.h>
static unsigned long calls;
int slow_verify(int id){calls++;return id%10==0;}
int main(void){
 int id,senior,eligible; unsigned long first=0,second=0;
 for(id=1;id<=1000;id++){
  senior=id%4==0; eligible=id%3==0;
  calls=0; (void)((senior&&eligible)||slow_verify(id)); first+=calls;
  calls=0; (void)(slow_verify(id)||(senior&&eligible)); second+=calls;
 }
 printf("Cheap test first: %lu calls\\nCard check first: %lu calls\\n",first,second);
 calls=0; (void)(0&&slow_verify(1000)); printf("0 && function: %lu calls\\n",calls);
 calls=0; (void)(0&slow_verify(1000)); printf("0 & function: %lu calls\\n",calls);
 calls=0; for(id=1;id<=1000;id++){int card=slow_verify(id);senior=id%4==0;eligible=id%3==0;(void)((senior&&eligible)||card);}
 printf("Audit every passenger: %lu calls\\n",calls); return 0;
}