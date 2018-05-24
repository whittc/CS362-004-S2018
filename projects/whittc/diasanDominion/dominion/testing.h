#include <stdio.h>
#define NOISY 1

void assertTrue_int(int test, int expected){
    if (test == expected){
#if (NOISY == 1)
        printf("Assert passed\n\n");
#endif
    }
    else{
        printf("Test case = %d, expected case = %d\n", test, expected);
        printf("Assert failed\n\n");
    }
    
    return;
}


void assertTrue_array(int *test, int *expected){
    int i;
    int passed = 1;
    
    for(i=0; i<sizeof(expected); i++){
        if(test[i] != expected[i]){
            passed = 0;
            printf("Test case = %d, expected case = %d\n", test[i], expected[i]);
        }
    }

    if (passed == 0)
        printf("Assert failed\n\n");
    else{
#if (NOISY == 1)
        printf("Assert passed\n\n");
#endif
    }
    
    return;
}
