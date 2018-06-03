#include <stdio.h>
#define NOISY 1

int assertTrue_int(int test, int expected){
    if (test == expected){
#if (NOISY == 1)
        printf("PASSED\n\n");
#endif
        return 1;
    }
    else{
        printf("Test case = %d, expected case = %d\n", test, expected);
        printf("FAILED\n\n");
        return 0;
    }
    
}


int  assertTrue_array(int *test, int *expected){
    int i;
    int passed = 1;
    
    for(i=0; i<sizeof(expected); i++){
        if(test[i] != expected[i]){
            passed = 0;
            printf("Test case = %d, expected case = %d\n", test[i], expected[i]);
        }
    }

    if (passed == 0){
        printf("FAILED\n\n");
        return 1;
    }
    else{
#if (NOISY == 1)
        printf("PASSED\n\n");
#endif
        return 0;
    }
    
}
