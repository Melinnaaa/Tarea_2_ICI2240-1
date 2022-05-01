#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"
#include "csvread.h"
#include "list.h"
#include "producto.h"
#include "carrito.h"

void agregarMarca_o_Tipo (Map* mapa, char* clave, producto* tmpProducto)
{
  //Si la marca/tipo no tienen una lista creada, se les crea una y se agrega la lista al mapa.
  if (searchMap(mapa, clave) == NULL) 
  {
    List* lista = createList(); // Lista que almacenara todos los datos de las marcas/tipo
    insertMap(mapa, clave, lista);//Se inserta la lista al mapa, con clave el nombre de la marca/tipo del producto.
    pushFront (lista, tmpProducto);//Se agrega el producto a la lista
  }
  else//Si la marca/tipo ya tienen una lista asignada
  {
    List* lista = (List*)searchMap(mapa, clave);//Lista que contiene los productos de la marca/tipo.
    producto* tmp = (producto*) calloc (1, sizeof(producto));//Variable que se utilizara para recorrer la lista.
    tmp = (producto*) firstList(lista);
    while (tmp != NULL)
    {
      if (strcmp(tmpProducto->nombre, tmp->nombre) == 0)//Si lo encuentra se finaliza la funcion, ya que otra función aumenta el stock
      {
        return;
      }
      tmp = (producto*) nextList(lista);
    }
    if (tmp == NULL)//Si no se encuentra el producto en la lista este se agrega.
    {
      pushBack (lista, tmpProducto);
    }
  }
}

void aumentarStock(Map* mapa, producto* clave)
{
  producto* tmp = (producto*) calloc (1, sizeof(producto));//variable que almacenará el producto.
  tmp = (producto*)searchMap(mapa, clave->nombre);
  if (tmp != NULL)//Si el producto existe en el mapa se aumenta su stock.
  {
    tmp->stock = tmp->stock + clave->stock;
  }
}

//Función que se encarga de guardar los datos de un producto ingresado por el usuario
producto* createProd()
{
  producto* tmp = (producto*) calloc (1, sizeof(producto));//Variable tipo producto que almacenará los datos del producto a agregar
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

void exportarProductos(Map* map, char* nombreArchivo)
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

void agregarProducto(Map* mapaMarca, Map* mapaNombre, Map* mapaTipo, producto* tmpProducto)
{
  if (searchMap (mapaNombre, tmpProducto->nombre) == NULL)//Si el producto no se encontró en el mapa se agrega.
  {
      insertMap(mapaNombre, tmpProducto->nombre, tmpProducto);
      agregarMarca_o_Tipo (mapaMarca, tmpProducto->marca, tmpProducto);
      agregarMarca_o_Tipo (mapaTipo, tmpProducto->tipo, tmpProducto);
    } 
    else //Si se encontraba se aumenta el stock de los productos.
    {
      aumentarStock(mapaNombre, tmpProducto);
    }  
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

  while (fgets (linea, 1023, productos) != NULL) // Se lee una linea del archivo
  {
    producto* tmpProducto = (producto*) calloc (1, sizeof(producto));
    for (int i = 0 ; i < 5 ; i = i + 1) //Lee 5 veces, ya que el producto tiene 5 datos.
    {
      char* aux = get_csv_field(linea, i); // Se guardan los datos en una variable auxiliar.
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

    agregarProducto(mapaMarca, mapaNombre, mapaTipo, tmpProducto);
  }
  fclose(productos);
}

//Función que el producto con el nombre que se busca
void mostrarProductosNombre(Map* mapaNombre, char* nombreProducto)
{
  producto* tmpProducto = (producto*) calloc (1, sizeof(producto));
  tmpProducto = searchMap(mapaNombre, nombreProducto);
  //Si no es NULL significa que si existe el producto, y se imprimen sus datos.
  if (tmpProducto != NULL)
  {
    printf ("%s, %s, %s, %d, %d\n", tmpProducto->nombre, tmpProducto->marca, tmpProducto->tipo, tmpProducto->stock, tmpProducto->precio);
  }
  //Si no se encontro una clave con el nombre ingresado siginifica que no existe
  else
  {
    printf ("El producto que ingreso no existe.\n");
  }
}

//Función que se encarga de mostrar todos los productos que estan dentro de la lista de tipos/productos.
void mostrarProductosLista(Map* mapa, char* clave)
{
  List* lista = (List*)searchMap(mapa, clave);//Se busca la lista del producto con su clave.
  if (lista == NULL)//Si es NULL no existe
  {
    printf ("El producto que busca no existe\n");
  }
  producto* tmp = (producto*) calloc (1, sizeof(producto));
  tmp = (producto*) firstList(lista);
  //Por otro lado se recorre y imprime los datos del producto hasta que se encuentre un dato NULL
  while (tmp != NULL)
  {
    printf ("%s, %s, %s, %d, %d\n", tmp->nombre, tmp->marca, tmp->tipo, tmp->stock, tmp->precio);
    tmp = (producto*) nextList(lista);
  }
}

//Función que muestra todos los productos disponibles
void mostrarTodos(Map* mapaNombre)
{
  producto* tmp = (producto*) calloc (1, sizeof(producto));
  tmp = (producto*) firstMap(mapaNombre);
  //Si el primer dato del mapa es NULL significa que no hay productos
  if (tmp == NULL)
  {
    printf("No existe ningun producto\n");
  }
  //Por otro lado se recorre y imprime los datos del producto hasta que se encuentre un dato NULL
  while (tmp != NULL)
  {
    printf ("%s, %s, %s, %d, %d\n", tmp->nombre, tmp->marca, tmp->tipo, tmp->stock, tmp->precio);
    tmp = (producto*) nextMap(mapaNombre);
  }
}

