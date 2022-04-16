#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "csvread.h"
#include "list.h"
#include "producto.h"

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

void aumentar_o_Agregar (Map* mapa, char* clave, producto* tmpProducto)
{
  if (searchMap(mapa, clave) == NULL) 
  {
    List* lista = createList(); // Lista que almacenara todos los datos de las marcas/tipo
    insertMap(mapa, clave, lista);
    pushFront (lista, tmpProducto);
  }
  else
  {
    List* lista = (List*)searchMap(mapa, clave);
    producto* tmp = (producto*) calloc (1, sizeof(producto));
    tmp = (producto*) firstList(lista);
    while (tmp != NULL)
    {
      if (strcmp(tmpProducto->nombre, tmp->nombre) == 0)
      {
        tmp->stock = tmp->stock + tmpProducto->stock;
        return;
      }
      tmp = (producto*) nextList(lista);
    }
    if (tmp == NULL)
    {
      pushBack (lista, tmpProducto);
    }
  }
}

void aumentarStock(Map* mapa, producto* clave)
{
  producto* tmp = (producto*) calloc (1, sizeof(producto));
  tmp = (producto*)searchMap(mapa, clave->nombre);
  if (tmp != NULL)
  {
    tmp->stock = tmp->stock + clave->stock;
  }
}

producto* createProd()
{
  producto* tmp = (producto*) calloc (1, sizeof(producto));
  printf("Ingrese el nombre del producto.\n");
  scanf("%[^\n]s", tmp->nombre);
  getchar();
  printf("Ingrese la marca del producto.\n");
  scanf("%[^\n]s", tmp->marca);
  getchar();
  printf("Ingrese el tipo del producto.\n");
  scanf("%[^\n]s", tmp->tipo);
  getchar();
  printf("Ingrese el stock del producto.\n");
  scanf("%d", &tmp->stock);
  getchar();
  printf("Ingrese el precio del producto.\n");
  scanf("%d", &tmp->precio);
  getchar();
  return tmp;
}

char* reservarMemoria (int largo)
{
  char* tmp = (char*) calloc (largo, sizeof(char));
  return tmp;
}

void exportarCanciones(Map* map, char* nombreArchivo)
{
  FILE* archivo = fopen (nombreArchivo, "a");//Se abre en modo "append", el cual escribe al final del archivo si existe o crea uno si no existe.
  producto* tmp = (producto*)firstMap(map);
  //Se recorre la lista de canciones hasta que sea nula.
  while (tmp != NULL)  
  {
    fprintf(archivo, "%s, %s, %s, %d, %d\n", tmp->nombre, tmp->marca, tmp->tipo, tmp->stock, tmp->precio);//Se escriben los datos en el archivo.
    tmp = (producto*)nextMap(map);
  }
  fclose(archivo);
}

void importarProductos(char* nombreArchivo, Map* mapaNombre, Map* mapaMarca, Map* mapaTipo)
{
  FILE* productos = fopen (nombreArchivo, "r");

  if (productos == NULL)
  {
    printf("El archivo que ingreso no existe\n");
    return;
  }
  char linea[1024];

  while (fgets (linea, 1023, productos) != NULL) // Se lee la linea
  {
    producto* tmpProducto = (producto*) calloc (1, sizeof(producto));
    for (int i = 0 ; i < 5 ; i = i + 1) //Lee 5 veces, ya que una canción solo tiene 5 caracteristicas
    {
      char* aux = get_csv_field(linea, i); // Se guardan los datos en la variable
      switch (i)
      {
        case 0: //Se almacena el nombre
        {
          strcpy(tmpProducto->nombre, aux);
          break;
        }
        case 1: //Se almacena la marca
        {
          strcpy(tmpProducto->marca, aux);
          break;
        }
        case 2: //Se almacena el genero
        { 
          strcpy(tmpProducto->tipo, aux);
          break;
        }
        case 3: //Se almacena el año de la canción
        {
          tmpProducto->stock = atoi(aux);
          break;
        }
        case 4: //Se almacena a la lista que pertenece
        {
          tmpProducto->precio = atoi(aux);
          break;
        }
      }
    }
    //Se comprueba si ya existe un producto con ese nombre en el mapa, ya que el nombre es unico.
    if (searchMap(mapaNombre, tmpProducto->nombre) == NULL)
    {
      insertMap(mapaNombre, tmpProducto->nombre, tmpProducto);
      aumentar_o_Agregar (mapaMarca, tmpProducto->marca, tmpProducto);
      aumentar_o_Agregar (mapaTipo, tmpProducto->tipo, tmpProducto);
    } 
    else // Si esta aumentan el stock de los productos
    {
      aumentarStock(mapaNombre, tmpProducto);
      aumentar_o_Agregar (mapaMarca, tmpProducto->marca, tmpProducto);
      aumentar_o_Agregar (mapaTipo, tmpProducto->tipo, tmpProducto);
    }  
  }
  fclose(productos);
}

void mostrarProductosNombre(Map* mapaNombre, char* nombreProducto)
{
  producto* tmpProducto = (producto*) calloc (1, sizeof(producto));
  tmpProducto = searchMap(mapaNombre, nombreProducto);
  if (tmpProducto != NULL)
  {
    printf ("%s, %s, %s, %d, %d\n", tmpProducto->nombre, tmpProducto->marca, tmpProducto->tipo, tmpProducto->stock, tmpProducto->precio);
  }
  else
  {
    printf ("El producto que ingreso no existe.\n");
  }
}

void mostrarProductosLista(Map* mapa, char* clave)
{
  List* lista = (List*)searchMap(mapa, clave);
  if (lista == NULL)
  {
    printf ("El producto que busca no existe\n");
  }
  producto* tmp = (producto*) calloc (1, sizeof(producto));
  tmp = (producto*) firstList(lista);
  while (tmp != NULL)
  {
    printf ("%s, %s, %s, %d, %d\n", tmp->nombre, tmp->marca, tmp->tipo, tmp->stock, tmp->precio);
    tmp = (producto*) nextList(lista);
  }
}

void mostrarTodos(Map* mapaNombre)
{
  producto* tmp = (producto*) calloc (1, sizeof(producto));
  tmp = (producto*) firstMap(mapaNombre);
  while (tmp != NULL)
  {
    printf ("%s, %s, %s, %d, %d\n", tmp->nombre, tmp->marca, tmp->tipo, tmp->stock, tmp->precio);
    tmp = (producto*) nextMap(mapaNombre);
  }
}

void agregarProducto(Map* mapaMarca, Map* mapaNombre, Map* mapaTipo, producto* tmpProducto)
{
  if (searchMap (mapaNombre, tmpProducto->nombre) == NULL)
  {
      insertMap(mapaNombre, tmpProducto->nombre, tmpProducto);
      aumentar_o_Agregar (mapaMarca, tmpProducto->marca, tmpProducto);
      aumentar_o_Agregar (mapaTipo, tmpProducto->tipo, tmpProducto);
    } 
    else // Si esta aumentan el stock de los productos
    {
      aumentarStock(mapaNombre, tmpProducto);
      aumentar_o_Agregar (mapaMarca, tmpProducto->marca, tmpProducto);
      aumentar_o_Agregar (mapaTipo, tmpProducto->tipo, tmpProducto);
    }  
}

void menu(Map* mapaTipo, Map* mapaNombre, Map* mapaMarca)
{
  int opcion;// Almacena la opcion ingresada por el usuario
  while(1)
  {
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
        printf("Ingrese el nombre del archivo al que desea importar las cacniones\n");
        leerChar(&archivoExportar);
        exportarCanciones(mapaNombre, archivoExportar);
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
        
        break;
      }
      case 9:
      {
        break;
      }
      case 10:
      {
        break;
      }
      case 11:
      {
        
        break;
      }
      case 12:
      {
        printf("Gracias por utilizar el programa\n");
        return;
      }
    }
    do
    {
      printf("¿Desea continuar?\n");
      printf("1- Si. / 2- NO.\n");
      scanf("%d", &opcion);
      getchar();
    } while (opcion < 1 || opcion > 2);
    if (opcion == 2)
    {
      printf("Gracias por utilizar el programa\n");
      break;
    }
  }
}