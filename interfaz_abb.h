// Nodo de un árbol binario
typedef struct s
{
    void *datos;            // área de datos
    struct s *izquierdo;    // raíz del subárbol izquierdo
    struct s *derecho;      // raíz del subárbol derecho
} Nodo;


////////////////////////////////////////////////////////////////////////////////////
// Interfaz abb: árbol binario de búsqueda. Para utilizar las
// funciones proporcionadas por esta interfaz, tendremos que
// definir en la aplicación que la utilice las funciones:
// comparar, compiar, procesar y liberarmem.
//
// Mostrar un mensaje de error y abortar el programa
void error()
{
    printf("Insuficiente memoria\n");
    exit(1);
}

// Crear un nuevo elemento
Nodo *nuevoNodo()
{
    Nodo *q = (Nodo *)malloc(sizeof(Nodo));
    return q;
}

void *buscar(void *datos, Nodo *raiz)
{
    // La función buscar permite acceder a un nodo determinado
    Nodo *actual = raiz;
    int nComp = 0;

    // Buscar un nodo que tenfa asociados los datos especificados
    while(actual != NULL)
    {
        if((nComp = comparar(datos, actual->datos)) == 0)
            return(actual->datos);  // nodo encontrado
        else if(nComp < 0)          // buscar en el subárbol izquierdo
            actual = actual->izquierdo;
        else                        // buscar en el subárbol derecho
            actual = actual->derecho;
    }
    return NULL;    // no exisite
}

int insertar(void *datos, Nodo **raiz)
{
    // La función insertar permite añadir un nodo que aún no está
    // en el árbol
    Nodo *nuevo = NULL, *ultimo = NULL, *actual = *raiz;
    int nComp = 0;
    if(datos == NULL)   return -1;  // no datos

    // Comienza la búsqueda para verificar si existe un nodo con
    // estos datos en el árbol
    while(actual != NULL)
    {
        if((nComp = comparar(datos, actual->datos)) == 0)
            break;  // se encontró el nodo
        else
        {
            ultimo = actual;
            if(nComp < 0)   // buscar en el subárbol izquierdo
                actual = actual->izquierdo;
            else            // buscar en el subárbol derecho
                actual = actual->derecho;
        }
    }

    if(actual == NULL)  // no se encontró el nodo, añadirlo
    {
        nuevo = nuevoNodo();
        if(!nuevo)  return 0;   // memoria insuficiente
        nuevo->datos = datos;
        nuevo->izquierdo = nuevo->derecho = NULL;
        // El nodo a añadir pasará a ser la raíz del árbol total si
        // este está vacío, del subárbol derecho de "ultimo" si
        // la comparación fue mayor
        if(ultimo == NULL)  // árbol vacío
            *raiz = nuevo;
        else if(nComp < 0)
            ultimo->izquierdo = nuevo;
        else
            ultimo->derecho = nuevo;
        return 1;   // correcto
    }   // fin del bloque if(actual == NULL)
    else    // el nodo ya existe en el árbol
        return 2;   // ya existe
}

void inorden(Nodo *raiz)
{
    // La función recursiva inorden visita los nodos del árbol
    // utilizando la forma inorden; esto es, primero visita
    // el subárbol izquierdo, después visita la raíz y, por
    // último, el subárbol derecho.

    Nodo *actual = raiz;

    if(actual != NULL)
    {
        inorden(actual->izquierdo); // visitar el subárbol izquierdo
        // Procesar los datos del nood visitado
        procesar(actual->datos);
        inorden(actual->derecho);   // visitar el subárbol derecho
    }
}

void preorden(Nodo *raiz)
{
    Nodo *actual = raiz;

    if(actual != NULL)
    {
        // Procesar los datos del nood visitado
        procesar(actual->datos);
        preorden(actual->izquierdo); // visitar el subárbol izquierdo
        preorden(actual->derecho);   // visitar el subárbol derecho
    }
}

void postorden(Nodo *raiz)
{
    Nodo *actual = raiz;

    if(actual != NULL)
    {
        inorden(actual->izquierdo); // visitar el subárbol izquierdo
        inorden(actual->derecho);   // visitar el subárbol derecho
        // Procesar los datos del nood visitado
        procesar(actual->datos);
    }
}

void borrarArbol(Nodo **raiz)
{
    // La función recursiva borrarArbol visita los nodos del árbol
    // utilizando la forma postorden para liberar la memoria
    // asignada a cada uno de ellos.
    Nodo *actual = *raiz;

    if(actual != NULL)
    {
        borrarArbol(&actual->izquierdo);    // subárbol izquierdo
        borrarArbol(&actual->derecho);      // subárbol derecho
        liberarmem(actual->datos);
        free(actual);
    }
    *raiz = NULL;
}
////////////////////////////////////////////////////////////////////////////////////
