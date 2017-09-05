#include "personajes.h"
#include "disparos.h"
#include <allegro.h>

#define ANCHO 600
#define ALTO  375


void NAVE::inicio(char* ruta_nave , char* ruta_bala, int anchob, int altob, int anchop, int altop , int x_ , int y_, int dir_bala1 , int _tipo){
    x=x_, y=y_;
    n_disp=0 , max_disp=2;
    dir_bala=dir_bala1;
    tick=0;
    ancho_b=anchob , alto_b=altob;
    ancho_p=anchop , alto_p=altop;

    img_nave=load_bitmap(ruta_nave,NULL);
    img_bala=load_bitmap(ruta_bala,NULL);
    tipo = _tipo;

}
bool NAVE::temporizador(int tiempo){
    tick++;
    if(tick == tiempo){
        tick=0;
        return true;
    }
    return false;
}
void NAVE::pinta(BITMAP* buffer, int ix , int iy){
        masked_blit(img_nave,buffer,ix*ancho_p,iy*alto_p,x,y,ancho_p,alto_p);
}

void NAVE::mover(){
    if(key[KEY_LEFT]){
         x=x-5;
    }
    if(key[KEY_RIGHT]){
         x=x+5;
    }
}
void NAVE::disparar(struct Balas disparos[] ,BITMAP* buffer){

    if(tipo)
    crear_bala(n_disp,max_disp,disparos, x ,y ,dir_bala);
    pintar_bala(n_disp , max_disp , disparos , buffer , img_bala,6,12);
    elimina_bala(n_disp, max_disp , disparos , ANCHO, ALTO);

}
void acomodar_enemigos(struct NAVE enemigos[] ){
    int indice=-1;
    int _tipo = 0;
    for(int i=0;i<5; i++){
            _tipo++;
            if(_tipo == 4) _tipo = 1;
        for(int j=0; j<11 ; j++){
            indice++;
            enemigos[indice].inicio("Recursos/enemigos.bmp","Recursos/BalaE.bmp",6,12,25,20,140+j*30,100+i*20, 8, _tipo);
        }
    }
}
void pintar_enemigo(struct NAVE enemigos[], BITMAP* buffer, int mov){
    int indice=-1;
    for(int i=0;i<5; i++){
        for(int j=0; j<11 ; j++){
            indice++;
            enemigos[indice].pinta(buffer,mov,enemigos[indice].tipo-1);
        }
    }
}
