#include "personajes.h"
#include "disparos.h"
#include "diseno.h"
#include <allegro.h>

#define ANCHO 600
#define ALTO  600


void NAVE::inicio(char* ruta_nave , char* ruta_bala, int anchob, int altob, int anchop, int altop , int x_ , int y_, int dir_bala1 , int _tipo, int _vida){
    x=x_, y=y_;
    n_disp=0 , max_disp=2;
    dir_bala=dir_bala1;
    tick=0;
    ancho_b=anchob , alto_b=altob;
    ancho_p=anchop , alto_p=altop;

    img_nave=load_bitmap(ruta_nave,NULL);
    img_bala=load_bitmap(ruta_bala,NULL);
    tipo = _tipo;
    vida = _vida;
    exp_enem=load_bitmap("Recursos/pum_enemigo.bmp",NULL);


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
            enemigos[indice].inicio("Recursos/enemigos.bmp","Recursos/BalaE.bmp",6,12,25,20,140+j*30,130+i*20, 8, _tipo , 1);
        }
    }
}
void pintar_enemigo(struct NAVE enemigos[], BITMAP* buffer, int mov){
    int indice=-1;
    for(int i=0;i<5; i++){
        for(int j=0; j<11 ; j++){
            indice++;
            if(enemigos[indice].vida>0)
            enemigos[indice].pinta(buffer,mov,enemigos[indice].tipo-1);
        }
    }
}


void explosion1(struct NAVE enemigos, BITMAP* buffer)
{
    BITMAP* parche = create_bitmap(25,20);
    clear_to_color(parche,0x000000);
    blit(parche,buffer,0,0,enemigos.x, enemigos.y , 25,20);
    masked_blit(enemigos.exp_enem, buffer , 0,0 , enemigos.x - 10 , enemigos.y , 41,34);
}

void explosion2(struct NAVE n, BITMAP* buffer, BITMAP* fondo){
    BITMAP* parche2 = create_bitmap(30,20);
    clear_to_color(parche2,0x000000);
    for(int j=0 ; j<6 ; j++){
        for(int i=1;i<=2;i++){
            blit(parche2,buffer,0,0,n.x,n.y,30,20);
            masked_blit(n.img_nave, buffer, i*30,0,n.x,n.y,30,20);
            imprimir_fondo(fondo,buffer);
            blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
            rest(50);
        }
    }
}

void inicia_escudo(struct escudo muros[]){
    char pos_muros[3][22] = {
        "AEC AEC AEC AEC",
        "B D B D B D B D",};
    int r=0;
    for(int i=0 ; i<20;i++){
        for(int j=0;j<2;j++){
            if(pos_muros[j][i]!=' '){
                    muros[r].x=150+i*20;
                    muros[r].y=425+j*15;
                    muros[r].dan=0;
                    if(pos_muros[j][i]=='A') muros[r].tipo=0;
                    if(pos_muros[j][i]=='B')muros[r].tipo=1;
                    if(pos_muros[j][i]=='C')muros[r].tipo=2;
                    if(pos_muros[j][i]=='D')muros[r].tipo=3;
                    if(pos_muros[j][i]=='E')muros[r].tipo=4;
                    r++;
            }
        }
    }
}
void pintar_escudos(struct escudo es[], BITMAP* img_mur, BITMAP* buffer){
    for(int i=0; i<20; i++){
        if(es[i].dan!=3){
            masked_blit(img_mur ,buffer ,es[i].dan*20,es[i].tipo*16, es[i].x,es[i].y,20,16);
        }
    }
}

