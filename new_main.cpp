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
    shell_index(vec,cant);
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
    int Mw = may_power(vec,cant);
    printf("\n\n--Potencia maxima--\n");
    printf("Index: %u",vec[Mw].index);
    printf("\nPotencia: %.3f Watts",vec[Mw].power);
    double RPM = (vec[Mw].vel / (2* M_PI));
    printf("\n %.3f RPM",RPM);
    porc_error(vec,cant);
    printf("\n\n-- ERRORES --\n");
    for(i=0;i<cant;i++){
        printf("\n\nIndex: %u",vec[i].index);
        printf("\nPotencia mecanica: %0.3f",vec[i].pm);
        printf("\nError:  %.3f %",vec[i].error); 
    }
    return 0;
}
