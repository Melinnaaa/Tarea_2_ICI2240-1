#ifndef Producto_h
#define Producto_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "csvread.h"
#include "list.h"
#include "producto.h"


typedef struct carrito carrito;

struct carrito
{
  char nombreProducto[100]; // Almacena el nombre del producto
  char nombreCarrito[100]; // Almacena la marca del producto
  int cantidad; // Almacena la cantidad de productos del carrito
};

carrito* createShoppingCart();

void asignarCarrito(carrito* cart, Map* carritos, Map* mapaNombre, Map* nombreCarritos);

void mostrarCarritos(Map* carritos, Map* nombreCarritos);

void eliminarProductoCarrito(Map* carritos, char* nombreCarrito);

void concretarCompra(Map* carritos, char* nombreCarrito, Map* mapaNombre, Map* nombreCarritos);

#endif 