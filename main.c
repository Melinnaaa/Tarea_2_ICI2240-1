#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Funciones/Map.h"
#include "./Funciones/menu.h"

int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

int main (void)
{
    Map* mapaTipo = createMap(is_equal_string); //Mapa que almacenara los productos de cada tipo en una lista.
    setSortFunction(mapaTipo,lower_than_string);
    Map* mapaNombre = createMap(is_equal_string);//Mapa que almacenara todos los nombres de los productos.
    setSortFunction(mapaNombre,lower_than_string);
    Map* mapaMarca = createMap(is_equal_string); //Mapa que almacenara los productos de cada marca en una lista.
    setSortFunction(mapaMarca,lower_than_string);
    Map* carritos = createMap(is_equal_string); //Mapa que almacenara los carritos y sus productos en una lista.
    setSortFunction(carritos,lower_than_string);
    Map* nombreCarritos = createMap(is_equal_string); //Mapa que almacenará los nombres de todos los carritos agregados
    setSortFunction(nombreCarritos,lower_than_string);
    menu(mapaTipo, mapaNombre, mapaMarca, carritos, nombreCarritos);
    return (0);
}