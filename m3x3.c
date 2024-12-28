#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>

#include "m3x3.h"


struct Matrix3{
    uint64_t *content;
};


u64 tr(const M3 m){ 
#define E m->content 
    return E[0]+E[4]+E[8];   
#undef E
}

M3 addM3(const M3 m1, const M3 m2){
#define E1(i) m1->content[i]
#define E2(i) m2->content[i]
#define S(i) E1(i)+E2(i)
    return init(S(0), S(1), S(2), S(3), S(4), S(5), S(6), S(7), S(8));
#undef S
#undef E2
#undef E1
}

M3 subM3(const M3 m1, const M3 m2){
#define E1(i) m1->content[i]
#define E2(i) m2->content[i]
#define S(i) E1(i)-E2(i)
    return init(S(0), S(1), S(2), S(3), S(4), S(5), S(6), S(7), S(8));
#undef S
#undef E2
#undef E1
}

M3 scalarmultM3(const M3 m, const u64 k){
#define E(i) m->content[i]
    return init(k*E(0), k*E(1), k*E(2), k*E(3), k*E(4), k*E(5), k*E(6), k*E(7), k*E(8));
#undef E
}


M3 multM3(const M3 m1, const M3 m2){
#define E1 m1->content
#define E2 m2->content
    return init(
        E1[0]*E2[0]+E1[1]*E2[3]+E1[2]*E2[6],
        E1[0]*E2[1]+E1[1]*E2[4]+E1[2]*E2[7],
        E1[0]*E2[2]+E1[1]*E2[5]+E1[2]*E2[8],
        E1[3]*E2[0]+E1[4]*E2[3]+E1[5]*E2[6],
        E1[3]*E2[1]+E1[4]*E2[4]+E1[5]*E2[7],
        E1[3]*E2[2]+E1[4]*E2[5]+E1[5]*E2[8],
        E1[6]*E2[0]+E1[7]*E2[3]+E1[8]*E2[6],
        E1[6]*E2[1]+E1[7]*E2[4]+E1[8]*E2[7],
        E1[6]*E2[2]+E1[7]*E2[5]+E1[8]*E2[8]
    );

#undef E2
#undef E1
}

M3 mapM3(const M3 m, const u64 (*f)(const u64)){
#define E m->content    
    return init(
            f(E[0]), f(E[1]), f(E[2]),
            f(E[3]), f(E[4]), f(E[5]),
            f(E[6]), f(E[7]), f(E[8])
        );
#undef E
}

M3 init(int arg1, ...){
    M3 out = (M3)malloc(sizeof(Matrix3));
    out -> content = (uint64_t*)malloc(9*SIZE64);
    out -> content[0] = arg1;
    va_list args;
    va_start(args, arg1);
    for(char i = 1; i < 9; ++i){
        out -> content[i] = va_arg(args, u64);
    }
    va_end(args);
    return out;
}

void destroy(M3 m3){
    free(m3->content);
    free(m3);
}

u64 det(const M3 m){
    #define E m->content
    return E[0]*(E[4]*E[8]-E[5]*E[7])
            -E[1]*(E[3]*E[8]-E[5]*E[6])
            +E[2]*(E[3]*E[7]-E[4]*E[6]);
    #undef E
}




void printM3(const M3 m3){
    for(char i = 0; i < 3; i++){
        printf("[");
        for(char j = 0; j < 3; j++){
            printf("%lu%s", m3->content[i*3+j], j != 2 ? ", " : "");
        }
        printf("]\n");
    }
}
