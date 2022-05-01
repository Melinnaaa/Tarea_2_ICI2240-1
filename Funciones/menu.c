#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csvread.h"
#include "Map.h"
#include "list.h"
#include "producto.h"
#include "carrito.h"
#include "menu.h"

void leerChar (char** nombreArchivo)
{
  char buffer[100];
  int largo;
  scanf("%[^\n]s", buffer);
  getchar();
  largo = strlen(buffer) + 1;
  (*nombreArchivo) = (char*) calloc (largo, sizeof(char));
  strcpy((*nombreArchivo), buffer);
}

void imprimirOpcionesMenu()
{
  printf("1.- Importar Productos.\n");
  printf("2.- Exportar Productos.\n");
  printf("3.- Agregar Producto.\n");
  printf("4.- Buscar producto por tipo.\n");
  printf("5.- Buscar producto por marca.\n");
  printf("6.- Buscar prooducto por nombre.\n");
  printf("7.- Mostrar todos los productos.\n");
  printf("8.- Agregar un producto al carrito.\n");
  printf("9.- Eliminar un producto del carrito.\n");
  printf("10.- Finalizar compra.\n");
  printf("11.- Mostrar carritos de compra\n");
  printf("12.- Salir\n");
  printf("Seleccione una opcion.\n");
}

void menu(Map* mapaTipo, Map* mapaNombre, Map* mapaMarca, Map* carritos, Map* nombreCarritos)
{
  int opcion;// Almacena la opcion ingresada por el usuario
  while(1)
  {
    //Este ciclo se encarga de scanear la opcion ingreasada hasta que sea valida.
    do
    {
      imprimirOpcionesMenu();
      scanf("%d", &opcion);
      getchar();
    } while (opcion< 1 || opcion > 12);

    switch (opcion)
    {
      case 1:
      {
        char* nombreArchivo;
        printf("Ingrese el archivo a importar:\n");
        leerChar(&nombreArchivo);
        importarProductos(nombreArchivo, mapaNombre, mapaMarca, mapaTipo);
        break;
      }
      case 2:
      {
        char* archivoExportar;
        printf("Ingrese el nombre del archivo al que desea importar los productos\n");
        leerChar(&archivoExportar);
        exportarProductos(mapaNombre, archivoExportar);
        break;
      }
      case 3:
      {
        producto* tmp = (producto*) calloc (1, sizeof(producto));
        tmp = createProd();
        agregarProducto(mapaMarca, mapaNombre, mapaTipo, tmp);
        break;
      }
      case 4:
      {
        char* tipo;
        printf("Ingrese el tipo de producto que busca:\n");
        leerChar(&tipo);
        mostrarProductosLista(mapaTipo, tipo);
        break;
      }
      case 5:
      {
        char* marca;
        printf("Ingrese la marca del producto que busca:\n");
        leerChar(&marca);
        mostrarProductosLista(mapaMarca, marca);
        break;
      }
      case 6:
      {
        char* nombreProducto;
        printf("Ingrese el nombre del producto que busca:\n");
        leerChar(&nombreProducto);
        mostrarProductosNombre(mapaNombre, nombreProducto);
        break;
      }
      case 7:
      {
        mostrarTodos(mapaNombre);
        break;
      }
      case 8:
      {
        carrito* cart = createShoppingCart();
        asignarCarrito(cart, carritos, mapaNombre, nombreCarritos);
        break;
      }
      case 9:
      {
        char* nombreCarrito;
        printf("Ingrese el nombre del carrito:\n");
        leerChar(&nombreCarrito);
        eliminarProductoCarrito(carritos, nombreCarrito);
        break;
      }
      case 10:
      {
        char* nombreCarrito;
        printf("Ingrese el nombre del carrito:\n");
        leerChar(&nombreCarrito);
        concretarCompra(carritos, nombreCarrito, mapaNombre, nombreCarritos);
        break;
      }
      case 11:
      {
        mostrarCarritos(carritos, nombreCarritos);
        break;
      }
      case 12:
      {
        printf("Gracias por utilizar el programa!\n");
        return;
      }
    }
    //Este ciclo se encarga de scanear la opcion ingreasada hasta que sea valida.
    do
    {
      printf("¿Desea continuar?\n");
      printf("1- Si. / 2- NO.\n");
      scanf("%d", &opcion);
      getchar();
    } while (opcion < 1 || opcion > 2);
    //Si la opción es 2 se finaliza el programa.
    if (opcion == 2)
    {
      printf("Gracias por utilizar el programa!\n");
      break;
    }
  }
}