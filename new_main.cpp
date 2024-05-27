#include "librery_motors.h"
int main(){
    struct motors *vec;
    int cant=0;
    FILE *f = fopen("swt_data.dat","rb");
    if (f == NULL ){
        printf("\nEl archivo es nulo");
        return 0;
    }
    int b = bits(f);
    int i=0;
    int j;
    int x;
    uint32_t type,header,aux,ind_aux;
    while(i<b){
        fread(&header,sizeof(uint32_t),1,f);
        if(i==0){                       //primer encabezado que lee
            vec = new struct motors[1];
            cant++;
        }
        type = header >> 30;
        //printf("\ntype: %u",type);
        aux = header << 2;
        ind_aux = aux >> 2;
        x = busq(ind_aux,vec,cant);
        if(x==1){                       //ya esta el motor
            j = pos(ind_aux,vec,cant);   //nos devuelve la posición en donde esta el motor.
        }else{                           // no existe el motor
            j = cant;
            vec = resize(vec,cant);
            cant++;
        }
        vec[j].index = ind_aux;
        type_data(vec,j,type,f);
        i=ftell(f);
    }
    for(i=0; i<cant; i++){
        printf("\n----------------");
        printf("\nIndex: %u",vec[i].index);
        printf("\ntorque: %.3f Nm",vec[i].torque);
        printf("\nWs: %.3f rad/s",vec[i].vel);
        printf("\nPower: %.3f Watts",vec[i].power);
    }
    FILE *c = fopen("datos_motores.txt","wb");
    if(c == NULL){
        printf("\nNo es posible abrir el archivo para texto");
    }
    data_txt(c,vec,cant);
    

    fclose(c);
    fclose(f);
    return 0;
}
