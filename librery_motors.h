#pragma once
#include <stdio.h>
#include <stdint.h>
#include <cstdio>

struct motors{
    uint32_t index;
    float torque, vel, power;
};
struct motors* resize(struct motors *vec, int vec_size);
int bits(FILE *f);
void encab(FILE *f);
int busq(uint32_t h,struct motors *v,int c);
int pos(uint32_t h,struct motors *v,int c);
void type_data(struct motors *v, int pos, uint32_t t,FILE *f);