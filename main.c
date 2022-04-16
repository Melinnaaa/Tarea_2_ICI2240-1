#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./Carpeta/Map.h"
#include "./Carpeta/producto.h"

int is_equal_int(void * key1, void * key2) {
    if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

int main (void)
{
    Map* mapaTipo = createMap(is_equal_int); // 20 es la capacidad momentanea que tendra el mapa
    Map* mapaNombre = createMap(is_equal_int);
    Map* mapaMarca = createMap(is_equal_int);
    menu(mapaTipo, mapaNombre, mapaMarca);
    return (0);
}