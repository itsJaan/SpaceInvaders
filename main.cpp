#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include "inicia.h"
#include "disparos.h"
#include "personajes.h"
#include "diseno.h"

#define ANCHO 600
#define ALTO  600


int main(){
    srand(time(NULL));
    inicia_allegro(ANCHO,ALTO); // fuciones del include inicia.h
	inicia_audio(70,70);        //
    //Pantalla principal
    BITMAP *buffer = create_bitmap(ANCHO, ALTO);
    BITMAP *portada = load_bitmap("Recursos/portada.bmp", NULL);
    BITMAP *fondo = load_bitmap("Recursos/fondo.bmp", NULL);

    PORTADA(portada);
    //INICIALIZANDO LAS FUNCIONES DE LAS NAVES;
    NAVE nave;
    nave.inicio("Recursos/nave.bmp","Recursos/Bala2.bmp",nave.ancho_b,nave.alto_b ,30,20 , ANCHO/2 , ALTO-70, -10 , 0 , 3);

    NAVE enemigo[60];
    acomodar_enemigos(enemigo);
    Balas disparos[nave.max_disp];
    Balas disparos_e[enemigo[0].max_disp];

    int azar = rand()%55;
    int mov = 0;

    while(!key[KEY_ESC]){//El juego se estara ejecuntando hasta que se presione el Boton ESC
            clear_to_color(buffer,0x000000);
            nave.pinta(buffer,0,0);
            nave.mover();
            if(key[KEY_SPACE] && nave.temporizador(5))
                crear_bala(nave.n_disp , nave.max_disp , disparos , nave.x , nave.y , nave.dir_bala);
            nave.disparar(disparos ,buffer);

            for(int i=0; i < 55;i++)
               eliminar_bala_objeto(nave,enemigo[i],disparos);


            /* codigo con 11
            for(int i=0; i < 55;i++)
               if(eliminar_bala_objeto(nave,enemigo[i],disparos))
                explosion1(enemigo[i],buffer);
            */

            pintar_enemigo(enemigo, buffer, mov);
            //if(enemigo[azar].n_disp == 0) azar = rand()%55;
            //enemigo[azar].disparar(disparos_e , buffer);
            if(enemigo[0].temporizador(10))
            if(++mov == 2) mov =0;

            imprimir_fondo(fondo , buffer);

            blit(buffer,screen, 0,0 , 0,0 ,ANCHO,ALTO );
            rest(20);

    }

	return 0;
}
END_OF_MAIN();
