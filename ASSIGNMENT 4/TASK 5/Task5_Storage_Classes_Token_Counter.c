/* TASK 5 - Storage classes: automatic, static, global and register examples */
#include <stdio.h>

/* Global counter example. In a multi-file program, define this once in
   token_data.c as: int sharedToken = 1000;
   Declare it in token_data.h as: extern int sharedToken;
   Other source files include the header and use the same variable. */
int sharedToken = 1000;

int next_token(void) {
    static int token = 1000; /* retains value between calls */
    return ++token;
}

int auto_token(void) {
    int token = 1000; /* recreated and initialized on every call */
    return ++token;
}

int global_token(void) {
    return ++sharedToken;
}

void print_tokens(void) {
    printf("Register loop variable demonstration: ");
    for (register int i = 1; i <= 3; i++) printf("%d ", i);
    printf("\n");
}

int main(void) {
    printf("static: %d %d %d\n", next_token(), next_token(), next_token());
    printf("auto  : %d %d %d\n", auto_token(), auto_token(), auto_token());
    printf("global: %d %d %d\n", global_token(), global_token(), global_token());

    /* Separate independent counters can be implemented by keeping one
       counter per category, or by passing int *counter to a function. */
    int vegCounter = 1000, nonVegCounter = 2000;
    printf("pointer counters: veg=%d, non-veg=%d\n", ++vegCounter, ++nonVegCounter);
    print_tokens();
    return 0;
}
