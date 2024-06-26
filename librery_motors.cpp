#include "librery_motors.h"
/**
 * @brief Cantidad de bits de un archivo
 * 
 * @param f manipulador del archiv
 * @return int cant de bits
 */
int bits(FILE *f){
    fseek(f,0,SEEK_END);
    int b = ftell(f);
    rewind(f);
    printf("\nEl archivo tiene %d bits",b);
    return b;
}
/**
 * @brief Redimensiona el vector motors
 * 
 * @param vec apuntador del vector
 * @param vec_size tamaño del vector
 * @return struct motors* nueva direccion de memoria
 */
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
/**
 * @brief Existencia del motor
 * 
 * Verifica si el motor ya esstá registrado
 * dentro del vector.
 * @param ind index  
 * @param v direccion de memoria del vector
 * @param c tamaño del vector
 * @return int 1 (si), 0 (no)
 */
int busq(uint32_t ind,struct motors *v,int c){
    for(int i=0; i<c; i++){
        if(ind == v[i].index){
            return 1;
        }
    }
    return 0;
}
/**
 * @brief Posicion del motor
 * 
 * Esta funcion devuelve la posicion donde ya esta registrado el motor.
 * No llamar a la funcion si no e verificó su exitencia con la funcion  "busq".
 * 
 * @param ind index
 * @param v direccion de memoria del vector
 * @param c tamaño del vector
 * @return int posicion
 */
int pos(uint32_t ind,struct motors *v,int c){
    for(int i=0; i<c; i++){
        if(ind == v[i].index){
            return i;
        }
    }
}
/**
 * @brief Clasificacion de datos
 * 
 * Este procedimiento clasifica los datos segpun su index.
 * No llamar al procedimeitno si no se tiene la posicion del index.
 * 
 * @param v direccion de memoria del vector
 * @param pos posición de index
 * @param t type 
 * @param f manipulador de archivo
 */
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
/**
 * @brief Escritura de archivo txt
 * 
 * @param c manipulador de archivo de texto
 * @param v direccion de memoria del vector
 * @param cant tamaño del vector
 */
void data_txt(FILE *c, struct motors *v, int cant){
    for( int i=0 ; i<cant ; i++ ){
        fprintf(c,"\n- - - - - - - - - - - - - ");
        fprintf(c,"\n\t\tIndex: %u",v[i].index);
        fprintf(c,"\nWS:     %.3f rad/s",v[i].vel);
        fprintf(c,"\npower:     %.3f W",v[i].power);
        fprintf(c,"\ntorque: %.3f Nm",v[i].torque);
    }
}
void shell_index(struct motors *vec, int cant){
    uint32_t aux;
    int y,b;
    int x = cant/2;
    do{
        do{
            b=0;
            for(int i=x; i<cant; i++){
                if(vec[i].index<vec[i-x].index){
                    aux = vec[i].index;
                    vec[i].index = vec[i-x].index;
                    vec[i-x].index = aux;
                    b=1;
                }
            }
        }while(b==1);
        x = x/2;
    }while(x>0);
}
int may_power(struct motors *v, int tam){
    float may;
    int pos;
    for(int i=0; i<tam; i++){
        if(i==0){
            may = v[i].power;
            pos=i;
        }
        else{
            if(v[i].power>may){
                may=v[i].power;
                pos=i;
            }
        }
    }
    return pos;
}
void porc_error(struct motors *v, int tam){
    float aux;
    for(int i=0; i<tam; i++){
        v[i].pm = (v[i].torque * v[i].vel);
        aux = (v[i].pm - v[i].power);
        if (aux<0){
            aux=aux*(-1);
        }
        v[i].error = (aux/v[i].power)*100;
    }
}
