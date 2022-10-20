//#include <stdio.h>  // For IO operations
// #include <stdlib.h> // for malloc/free
#include <iostream>
#include "free_space.h"


int unitTest1(int status){
    int passed = 0;
    node_t* node = create_node(20);
    if (node->size == 20) passed = 1;
    return passed;
}

int unitTest2(int status){
    int passed = 0;
    dll_t* test = create_dll(1000);
    dll_push_front(test, 778);
    dll_push_front(test,99);
    if(dll_get(test, 0) == 99 && dll_size(test) == 3){
        passed = 1;
    }
    return passed;
}

int unitTest3(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (f->size == 1000) passed = 1;
    return passed;
}

int unitTest4(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int res = malloc('F', 1200, stack);
    // node_t* f = get_freelist(stack);
    // print_freelist(f);
    if (res == -1) passed = 1;
    return passed;
} 


int unitTest5(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int res = malloc('F', 10, stack);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 0) passed = 1;
    return passed;
}

int unitTest6(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    malloc('F', 10, stack);
    int res = malloc('F', 30, stack);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 1) passed = 1;
    return passed;
}

int unitTest7(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    malloc('F', 10, stack);
    malloc('F', 30, stack);
    int res = malloc('F', 1000, stack);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == -1) passed = 1;
    return passed;
} 

int unitTest8(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    malloc('F', 10, stack);
    malloc('F', 30, stack);
    int res = free(stack, 0);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 0) passed = 1;
    return passed;
}

int unitTest9(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    malloc('F', 10, stack);
    malloc('F', 30, stack);
    int res = free(stack, 3);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == -1) passed = 1;
    return passed;
}

int unitTest10(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int tasks[] = {10, 20, 30, 40};
    for (auto task: tasks){
        malloc('F', task, stack);
    }
    int res = free(stack, 0);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 0) passed = 1;
    return passed;
}

// 4 times malloc, and 2 times free
int unitTest11(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int tasks[] = {10, 20, 30, 40};
    for (auto task: tasks){
        malloc('F', task, stack);
    }
    free(stack, 0);
    int res = free(stack, 2);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 2) passed = 1;
    return passed;
}

// 4 times malloc, and 2 times free, and malloc again.
int unitTest12(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int tasks[] = {10, 20, 30, 40};
    for (auto task: tasks){
        malloc('F', task, stack);
    }
    free(stack, 0);
    free(stack, 2);
    int res = malloc('F', 20, stack);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 2) passed = 1;
    return passed;
}

int unitTest13(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int res = malloc('B', 1200, stack);
    // node_t* f = get_freelist(stack);
    // print_freelist(f);
    if (res == -1) passed = 1;
    return passed;
}

int unitTest14(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int res = malloc('B', 10, stack);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 0) passed = 1;
    return passed;
}

int unitTest15(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    malloc('B', 10, stack);
    int res = malloc('B', 30, stack);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 1) passed = 1;
    return passed;
}

int unitTest16(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    malloc('B', 10, stack);
    malloc('B', 30, stack);
    int res = malloc('B', 1000, stack);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == -1) passed = 1;
    return passed;
} 

int unitTest17(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    malloc('B', 10, stack);
    malloc('B', 30, stack);
    int res = free(stack, 0);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 0) passed = 1;
    return passed;
}

int unitTest18(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    malloc('B', 10, stack);
    malloc('B', 30, stack);
    int res = free(stack, 3);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == -1) passed = 1;
    return passed;
}

int unitTest19(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int tasks[] = {10, 20, 30, 40};
    for (auto task: tasks){
        malloc('B', task, stack);
    }
    int res = free(stack, 0);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 0) passed = 1;
    return passed;
}

int unitTest20(int status){
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int tasks[] = {10, 20, 30, 40};
    for (auto task: tasks){
        malloc('W', task, stack);
    }
    int res = free(stack, 0);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 0) passed = 1;
    return passed;
}

// Use FIRST fit to malloc, the last malloc would pick the 50 chunk because it's the first free chunk that the task can fit.
int unitTest21(int status){
    printf("First fit example:\n");
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int tasks[] = {10, 20, 50, 40, 30, 60};
    for (auto task: tasks){
        malloc('F', task, stack);
    }
    free(stack, 2);
    free(stack, 4);
    int res = malloc('F', 25, stack);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 2) passed = 1;
    return passed;
}

// Use BEST fit to malloc, the last malloc would pick the 50 chunk because it's the best free chunk that the task can fit.
int unitTest22(int status){
    printf("Best fit example:\n");
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int tasks[] = {10, 20, 50, 40, 30, 60};
    for (auto task: tasks){
        malloc('B', task, stack);
    }
    free(stack, 2);
    free(stack, 4);
    // node_t* f0 = get_freelist(stack);
    // print_freelist(f0);
    int res = malloc('B', 25, stack);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 4) passed = 1;
    return passed;
}

// Use WORST fit to malloc, the last malloc would pick the 790 chunk because it's the worst free chunk that the task can fit. 
// The largest free chunk would be smaller than the other two cases.
int unitTest23(int status){
    printf("Worst fit example:\n");
    int passed = 0;
    dll_t* stack = create_dll(1000);
    int tasks[] = {10, 20, 50, 40, 30, 60};
    for (auto task: tasks){
        malloc('W', task, stack);
    }
    free(stack, 2);
    free(stack, 4);
    int res = malloc('W', 25, stack);
    node_t* f = get_freelist(stack);
    print_freelist(f);
    if (res == 6) passed = 1;
    return passed;
}




int (*unitTests[])(int)={
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    unitTest5,
    unitTest6,
    unitTest7,
    unitTest8,
    unitTest9,
    unitTest10,
    unitTest11,
    unitTest12,
    unitTest13,
    unitTest14,
    unitTest15,
    unitTest16,
    unitTest17,
    unitTest18,
    unitTest19,
    unitTest20,
    unitTest21,
    unitTest22,
    unitTest23,
    NULL
};

int main(){
    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
    	printf("========unitTest %d========\n",counter);
        if(1==unitTests[counter](1)){
    		printf("passed test\n");
    		testsPassed++;	
    	}else{
    		printf("failed test, missing functionality, or incorrect test\n");
    	}
    counter++;
    }

    printf("%d of %d tests passed\n",testsPassed,counter);
    return 0;
}

