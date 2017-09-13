#include <allegro.h>

#ifndef PERSONAJES_H_INCLUDED
#define PERSONAJES_H_INCLUDED


struct NAVE{
        int x,y;
        int n_disp;
        int max_disp;
        int tick;//el tiempo  que tarda en sacar balas
        int ancho_b, alto_b;//balas
        int ancho_p , alto_p;
        int dir_bala;
        int tipo;
        int vida;

        BITMAP* img_nave;
        BITMAP* img_bala;
        BITMAP* exp_enem;
        /*BITMAP* vidas;
        BITMAP* vidas2;
        BITMAP* vidas3;
        */
        void inicio(char* ruta_nave , char* ruta_bala, int anchob , int altob , int anchoe, int altoe , int x_ ,int y_, int dir_bala1 , int _tipo , int _vida);
        bool temporizador(int tiempo);
        void pinta(BITMAP* buffer, int ix , int iy);
        void mover();
        void disparar(struct Balas disparos[] ,BITMAP* buffer);

};


void acomodar_enemigos(struct NAVE enemigos[] );
void pintar_enemigo(struct NAVE enemigos[], BITMAP* buffer, int mov);
void explosion1(struct NAVE enemigo, BITMAP* buffer);
void explosion2(struct NAVE n, BITMAP* buffer, BITMAP* fondo);
//void pintar_vidas(BITMAP * buffer);
#endif // PERSONAJES_H_INCLUDED
