#ifndef producto_h
#define producto_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "csvread.h"
#include "list.h"

typedef struct producto producto;

struct producto
{
  char nombre[100]; // Almacena el nombre del producto
  char marca[100]; // Almacena la marca del producto
  char tipo[100]; // Almacena el tipo del producto
  int stock; // Almacena el stock del producto
  int precio; // Almacena el precio del producto
};

typedef struct carrito carrito;

struct carrito
{
  char nombreProducto[100]; // Almacena el nombre del producto
  char nombreCarrito[100]; // Almacena la marca del producto
  int cantidad; // Almacena la cantidad de productos del carrito
};

void leerChar (char** nombreArchivo);

void imprimirOpcionesMenu();

void aumentar_o_Agregar (Map* mapa, char* clave, producto* tmpProducto);

void aumentarStock(Map* mapa, producto* clave);

producto* createProd();

char* reservarMemoria (int largo);

void exportarCanciones(Map* map, char* nombreArchivo);

void importarProductos(char* nombreArchivo, Map* mapaNombre, Map* mapaMarca, Map* mapaTipo);

void mostrarProductosNombre(Map* mapaNombre, char* nombreProducto);

void mostrarProductosLista(Map* mapa, char* clave);

void mostrarTodos(Map* mapaNombre);

void agregarProducto(Map* mapaMarca, Map* mapaNombre, Map* mapaTipo, producto* tmpProducto);

carrito* createShoppingCart();

void asignarCarrito(carrito* cart, Map* carritos);

void mostrarCarritos(Map* carritos);

void menu(Map* mapaTipo, Map* mapaNombre, Map* mapaMarca, Map* carritos);

#endif