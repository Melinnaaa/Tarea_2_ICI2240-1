#ifndef Menu_h
#define Menu_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "csvread.h"
#include "list.h"
#include "producto.h"

void leerChar (char** nombreArchivo);

void imprimirOpcionesMenu();

void menu(Map* mapaTipo, Map* mapaNombre, Map* mapaMarca, Map* carritos, Map* nombreCarritos);


#endif 