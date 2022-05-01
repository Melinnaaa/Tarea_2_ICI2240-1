#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csvread.h"
#include "Map.h"
#include "list.h"
#include "producto.h"
#include "carrito.h"

//Función encargada de crear una variable tipo carrito con los datos que le ingrese el usuario
carrito* createShoppingCart()
{
  carrito* cart = (carrito*) calloc (1, sizeof(carrito));
  printf("Ingrese el nombre del producto\n");
  scanf("%[^\n]s", cart->nombreProducto);
  getchar();
  printf("Ingrese la cantidad de articulos\n");
  scanf("%d", &cart->cantidad);
  getchar();
  printf("Ingrese el nombre del carrito\n");
  scanf("%[^\n]s", cart->nombreCarrito);
  getchar();
  return cart;
}

//Se encarga de agregar un producto al carrito.
void asignarCarrito(carrito* cart, Map* carritos, Map* mapaNombre, Map* nombreCarritos)
{
  //Si el producto no existe no se añade al carrito y se finaliza la función.
  if (searchMap(mapaNombre, cart->nombreProducto) == NULL)
  {
    printf("El producto que desea agregar no existe\n");
    return;
  }
  //Si el carrito no existe
  if (searchMap(carritos, cart->nombreCarrito) == NULL) 
  {
    List* lista = createList(); //Se crea una lista (carrito) que guarde los productos.
    insertMap(carritos, cart->nombreCarrito, lista); //Se inserta en el mapa de carritos.
    pushFront (lista, cart);//Se guarda el producto en la lista
    insertMap(nombreCarritos, cart->nombreCarrito, cart->nombreCarrito);//Se guarda el nombre del producto en la lista que almacena el nombre de todos los carritos.
  }
  //Si el carrito existe
  else
  {
    List* lista = (List*)searchMap(carritos, cart->nombreCarrito);//Variable que almacena la lista encontrada a partir de su nombre
    carrito* tmp = (carrito*) calloc (1, sizeof(carrito));//Variable que almacena el producto del carrito, y se utilizará para recorrer la lista.
    tmp = (carrito*) firstList(lista);
    while (tmp != NULL)
    {
      if (strcmp(cart->nombreProducto, tmp->nombreProducto) == 0)//Si el producto ya se encontraba en el carrito se aumenta su stock y se finaliza la función
      {
        tmp->cantidad = tmp->cantidad + cart->cantidad;
        return;
      }
      tmp = (carrito*) nextList(lista);
    }
    if (tmp == NULL) // Si el producto ingresado no existe en el carrito se agrega a la lista
    {
      pushBack (lista, cart);
    }
  }
}

//Función encargada de mostrar todos los carritos y la cantidad de productos
void mostrarCarritos(Map* carritos, Map* nombreCarritos)
{
  List* mapa = (List*)firstMap(carritos);
  //Si no se encontro una lista con el nombre ingresado se finaliza la función
  if (mapa == NULL)
  {
    printf ("No existe ningun carrito\n");
    return;
  }
  carrito* tmp = (carrito*) calloc (1, sizeof(carrito));
  int totalProductos; //Almacena el total de productos que contiene el carrito.
  char tmpNombre[100];//Almacena el nombre actual del carrito
  strcpy(tmpNombre, firstMap(nombreCarritos));
  //Ciclo que recorre el mapa de carritos.
  while (mapa != NULL)
  {
    tmp = (carrito*) firstList(mapa);
    totalProductos = 0; //Se reinicia cada vez que se repite el ciclo.
    //Si no existen productos en el carrito actual se muestra un mensaje.
    if (tmp == NULL)
    {
      printf("No hay ningun producto en el carrito: %s\n", tmpNombre);
    }
    //Por otro lado se recorre la lista que guarda los productos del carrito.
    else
    {
      //Ciclo que recorre la lista de carritos
      while (tmp != NULL)
      {
        totalProductos = totalProductos + tmp->cantidad; //Aumenta el total de procutos.
        tmp = (carrito*) nextList(mapa);
      }
      printf("Carrito: %s, cantidad de productos: %d\n", tmpNombre, totalProductos);//Se muestra el nombre del carrito y el total de productos que contiene.
    }
    mapa = (List*)nextMap(carritos);
    //Si el siguiente dato no es NULL se copia el nombre del carrito a la variable que almacena el nombre del carrito.
    if (mapa != NULL)
    {
      strcpy(tmpNombre, nextMap(nombreCarritos));
    }
  }
}

//Función encargada de eliminar el ultimo producto ingresado al carrito (no elimina el carrito)
void eliminarProductoCarrito(Map* carritos, char* nombreCarrito)
{
  List* lista = (List*)searchMap(carritos, nombreCarrito);
  if (lista == NULL)//Si la lista es nula significa que no existe ningun carrito con ese nombre.
  {
    printf("No existe ningun carrito con este nombre\n");
  }
  else//Si existe se elimina el ultimo producto agregado
  {
    lista = popBack(lista);
  }
}

void concretarCompra(Map* carritos, char* nombreCarrito, Map* mapaNombre, Map* nombreCarritos)
{
  List* lista = (List*)searchMap(carritos, nombreCarrito);
  //Si no se encuentra una lista con el nombre indicado en el mapa significa que el carrito no existe.
  if (lista == NULL)
  {
    printf ("El carrito no existe.\n");
    return;
  }
  carrito* tmp = (carrito*) calloc (1, sizeof(carrito));//Almacena el producto que tiene el carrito
  tmp = (carrito*) firstList(lista);
  //Si el producto es nulo significa que el carrito no tiene productos, por lo cual se muestra un mensaje y se finaliza la función.
  if (tmp == NULL)
  {
    printf ("El carrito no tiene ningun producto.\n");
    return;
  }
  producto* tmpStock = (producto*) calloc (1, sizeof(producto));//Almacenara el stock del producto para poder hacer los cambios luego de la compra al stock(restar stock).
  int total;// Almacenará el precio a pagar por un determinado producto.
  int precio = 0;//Almacenará precio total a pagar.
  printf("Resumen de compra:\n");
  //Ciclo que recorre la lista que contiene los productos del carrito.
  while (tmp != NULL)
  {
    tmpStock = (producto*)searchMap(mapaNombre, tmp->nombreProducto);
    //Si el total de productos en el carrito sobrepasa el stock existente se le da solamente el stock disponible.
    if (tmpStock->stock <  tmp->cantidad)
    {
      total = tmpStock->stock * tmpStock->precio; //Se multiplica el precio por la cantidad de productos(La cantidad es el stock existinte).
      precio = precio + total; //Se le suma al precio total
      printf ("%s, %d\n", tmp->nombreProducto, tmpStock->stock); //Se muestran el nombre del producto y su stock.
      tmpStock->stock = 0; //Se actualiza el stock
    }
    //Si el total de productos en el carrito es menor al stock existente
    else
    {
      total = tmp->cantidad * tmpStock->precio; //Se multiplica el precio por la cantidad de productos
      precio = precio + total; //Se le suma al precio total
      tmpStock->stock = tmpStock->stock - tmp->cantidad; //Se actualiza el stock restando la cantidad al stock
      printf ("%s, %d\n", tmp->nombreProducto, tmp->cantidad); //Se muestran el nombre del producto y su stock.
    }
    tmp = (carrito*) nextList(lista);
  }
  printf("El total a pagar es : $%d\n", precio);
  eraseMap(carritos, nombreCarrito);
  eraseMap(nombreCarritos, nombreCarrito);
}