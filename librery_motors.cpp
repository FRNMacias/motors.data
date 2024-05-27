#include "librery_motors.h"
int bits(FILE *f){
    fseek(f,0,SEEK_END);
    int b = ftell(f);
    rewind(f);
    printf("\nEl archivo tiene %d bits",b);
    return b;
}
struct motors* resize(struct motors *vec, int vec_size){
    int new_size = vec_size +1;
    struct motors *aux; 
    aux = new struct motors [new_size];
    for(int i=0; i<vec_size; i++){
        aux[i] = vec[i];
    }
    delete []vec;
    return aux;
}
int busq(uint32_t ind,struct motors *v,int c){
    for(int i=0; i<c; i++){
        if(ind == v[i].index){
            return 10;
        }
    }
    return 5;
}
int pos(uint32_t ind,struct motors *v,int c){
    for(int i=0; i<c; i++){
        if(ind == v[i].index){
            return i;
        }
    }
}
void type_data(struct motors *v, int pos, uint32_t t, FILE *f){
    if(t==3){
        printf("\nInformación invalida.");
        float a;
        fread(&a,sizeof(float),1,f);
    }else{
        if(t == 0){               //Torque
            fread(&v[pos].torque,sizeof(float),1,f); 
        }
        if(t==1){                 //vel
            fread(&v[pos].vel,sizeof(float),1,f);
        }
        if(t==2){                //power
            fread(&v[pos].power,sizeof(float),1,f);
        }
    }
}