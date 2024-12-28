#ifndef M3X3_H
#define M3X3_H
#include <stdint.h>

#define SIZE64 sizeof(uint64_t) // supposedly 64
#define u64 uint64_t

typedef struct Matrix3 Matrix3;
typedef Matrix3* M3;
M3 init(int arg1,...);
void destroy(M3);
void printM3(const M3);
uint64_t det(const M3);
u64 tr(const M3);
M3 addM3(const M3, const M3);
M3 subM3(const M3, const M3);
M3 scalarmultM3(const M3, const u64);
M3 multM3(const M3, const M3);
M3 mapM3(const M3, const u64(*)(const u64));
#endif
