#include <allegro.h>
#include "inicia.h"
#include "disparos.h"

#define ANCHO 600
#define ALTO  375

struct NAVE{
        int x,y;
        int n_disp;
        int max_disp;
        int tick;//el tiempo  que tarda en sacar balas
        int ancho_b, alto_b;//balas
        int ancho_p , alto_p;
        int dir_bala;

        BITMAP* img_nave;
        BITMAP* img_bala;

        void inicio(char* ruta_nave , char* ruta_bala, int anchob , int altob , int anchoe, int altoe , int x_ ,int y_, int dir_bala1);
        bool temporizador();
        void pinta(BITMAP* buffer);
        void mover();
        void disparar(struct Balas disparos[] ,BITMAP* buffer);



};
void NAVE::inicio(char* ruta_nave , char* ruta_bala, int anchob, int altob, int anchop, int altop , int x_ , int y_, int dir_bala1){
    x=x_, y=y_;
    n_disp=0 , max_disp=4;
    dir_bala=dir_bala1;
    tick=0;
    ancho_b=anchob , alto_b=altob;
    ancho_p=anchop , alto_p=altop;

    img_nave=load_bitmap(ruta_nave,NULL);
    img_bala=load_bitmap(ruta_bala,NULL);

}
bool NAVE::temporizador(){
    tick++;
    if(tick>8){
        tick=0;
        return true;
    }
    return false;
}
void NAVE::pinta(BITMAP* buffer){
        masked_blit(img_nave,buffer,0,0,x,y,ancho_p,alto_p);
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

    if(key[KEY_SPACE] && temporizador()== true){
       crear_bala(n_disp,max_disp,disparos, x ,y ,dir_bala);
    }
    pintar_bala(n_disp , max_disp , disparos , buffer , img_bala,6,12);
    elimina_bala(n_disp, max_disp , disparos , ANCHO, ALTO);

}
void acomodar_enemigos(struct NAVE enemigos[] ){
    int indice=-1;
    for(int i=0;i<5; i++){
        for(int j=0; j<11 ; j++){
            indice++;
            enemigos[indice].inicio("Recursos/enemigos.bmp","Recursos/BalaE.bmp",6,12,25,20,140+j*30,100+i*20, 8);
        }
    }
}
void pintar_enemigo(struct NAVE enemigos[], BITMAP* buffer){
    int indice=-1;
    for(int i=0;i<5; i++){
        for(int j=0; j<11 ; j++){
            indice++;
            enemigos[indice].pinta(buffer);
        }
    }
}



int main(){
    inicia_allegro(ANCHO,ALTO); // fuciones del include inicia.h
	inicia_audio(70,70);        //
    //PAntalla principal
    BITMAP *buffer = create_bitmap(ANCHO, ALTO);
    //INICIALIZANDO LAS FUNCIONES DE LAS NAVES;
    NAVE nave;
    nave.inicio("Recursos/nave.bmp","Recursos/Bala2.bmp",nave.ancho_b,nave.alto_b ,30,20 , ANCHO/2 , ALTO-50, -10);

    NAVE enemigo[100];
    acomodar_enemigos(enemigo);
    Balas disparos[nave.max_disp];
    Balas disparos_e[enemigo[0].max_disp];

    while(!key[KEY_ESC]){//El juego se estara ejecuntando hasta que se presione el Boton ESC
            clear_to_color(buffer,0x000000);
            nave.pinta(buffer);
            nave.mover();
            nave.disparar(disparos ,buffer);


            pintar_enemigo(enemigo, buffer);
            blit(buffer,screen, 0,0 , 0,0 ,ANCHO,ALTO );
            rest(20);

    }

	return 0;
}
END_OF_MAIN();

