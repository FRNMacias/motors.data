#pragma once
#include <stdio.h>
#include <stdint.h>
#include <cstdio>
#include <iostream>
#include <cmath>

struct motors{
    uint32_t index;
    float torque, vel, power;
    float error,pm;
};
struct motors* resize(struct motors *vec, int vec_size);
int bits(FILE *f);
void encab(FILE *f);
int busq(uint32_t h,struct motors *v,int c);
int pos(uint32_t h,struct motors *v,int c);
void type_data(struct motors *v, int pos, uint32_t t,FILE *f);
void shell_index(struct motors *v, int cant);
void data_txt(FILE *c, struct motors *v, int cant);
int may_power(struct motors *v, int tam);
void porc_error(struct motors *v, int tam);