#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Carpeta/Map.h"
#include "./Carpeta/producto.h"

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
    Map* mapaTipo = createMap(is_equal_string);
    setSortFunction(mapaTipo,lower_than_string);
    Map* mapaNombre = createMap(is_equal_string);
    setSortFunction(mapaNombre,lower_than_string);
    Map* mapaMarca = createMap(is_equal_string);
    setSortFunction(mapaMarca,lower_than_string);
    Map* carritos = createMap(is_equal_string);
    setSortFunction(carritos,lower_than_string);
    menu(mapaTipo, mapaNombre, mapaMarca, carritos);
    return (0);
}