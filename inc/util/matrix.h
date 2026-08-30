#ifndef __MATRIX_H__
#define __MATRIX_H__

#define offsetof(type, member) \
    ((size_t)&(((type *)0)->member))
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

void matrix_mul(int d11, int d12, int d21, int d22, double m1[d11][d12], double m2[d21][d22], double res[d11][d22]);

#endif // __MATRIX_H__
