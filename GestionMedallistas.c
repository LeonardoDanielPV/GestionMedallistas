#include <stdio.h>
#include <stdlib.h>

#include "arreglos_funciones.h"

#define CMAX 32

typedef struct
{
    char nombre[CMAX];
    char nacionalidad[CMAX];
    int puntos;
} Medallista;
char nacionalidadBuscar[CMAX];
int nacionalidadPuntos;

void ImprimirMedallista(Medallista *);
char *Medalla(int, char *);

int comparar(void *datos1, void *datos2)
{
    char *x = ((Medallista *)datos1)->nombre;
    char *y = ((Medallista *)datos2)->nombre;

    int cmp = CompCadena(x, y);
    if(cmp == 0)
    {
        x = ((Medallista *)datos1)->nacionalidad;
        y = ((Medallista *)datos2)->nacionalidad;
        cmp = CompCadena(x, y);
    }
    return cmp;
}

void copiar(void *datos1, void *datos2)
{
    *((Medallista *)datos1) = *((Medallista *)datos2);
}

void procesar(void *datos)
{
    Medallista *x = (Medallista *)datos;
    if(!x) return;
    if(CompCadena(x->nacionalidad, nacionalidadBuscar) == 0)
        nacionalidadPuntos = nacionalidadPuntos + x->puntos;
}

void liberarmem(void *datos)
{
    free((Medallista *)datos);
}

#include "interfaz_abb.h"

void error1(Nodo *raiz)
{
    borrarArbol(&raiz);
    error();
}

void error2(Medallista *x, Nodo *raiz)
{
    free(x);
    borrarArbol(&raiz);
    error();
}

void cargarMedallistas(Nodo **, Nodo **, Nodo **, char *);

int main(int argc, char **argv)
{
    Nodo *raizMedallistasdConOro = NULL;
    Nodo *raizMedallistasConPlata = NULL;
    Nodo *raizMedallistasConBronce = NULL;

    cargarMedallistas(&raizMedallistasdConOro, &raizMedallistasConPlata, &raizMedallistasConBronce, "BaseDatos.txt");

    Medallista entrada;
    Medallista *actual;
    char cAux[CMAX];
    printf("Introduce el nombre y nacionalidad de un medallista para ver su medalla ademas de su equipo y los puntos del pais (0 para salir)\n");
    do
    {
        printf("Nombre: ");
        scanf("%s", entrada.nombre);
        if(CompCadena("0", entrada.nombre) == 0)
            break;
        printf("Nacionalidad: ");
        scanf("%s",entrada.nacionalidad);

        actual = buscar(&entrada, raizMedallistasdConOro);
        if(!actual)
            actual = buscar(&entrada, raizMedallistasConPlata);
        if(!actual)
            actual = buscar(&entrada, raizMedallistasConBronce);

        if(!actual)
            printf("No se encuentra este medallista\n\n");
        else
        {
            printf("Su medalla es %s\n", Medalla(actual->puntos, cAux));
            CopiaCadena(nacionalidadBuscar, actual->nacionalidad);
            nacionalidadPuntos = 0;
            inorden(raizMedallistasdConOro);
            inorden(raizMedallistasConPlata);
            inorden(raizMedallistasConBronce);
            printf("El equipo de %s tiene %d puntos:\n\n", actual->nacionalidad, nacionalidadPuntos);
        }
    } while(1);

    borrarArbol(&raizMedallistasdConOro);
    borrarArbol(&raizMedallistasConPlata);
    borrarArbol(&raizMedallistasConBronce);
}

void ImprimirMedallista(Medallista *x)
{
    printf("Nombre: %s\tNacionalidad: %s\tMedalla: ", x->nombre, x->nacionalidad);
    if(x->puntos == 10)
        puts("Oro");
    else if(x->puntos == 5)
        puts("Plata");
    else if(x->puntos == 2)
        puts("Bronce");
}

char *Medalla(int puntos, char *medalla)
{
    if(puntos == 10)
        CopiaCadena(medalla, "Oro");
    else if(puntos == 5)
        CopiaCadena(medalla, "Plata");
    else if(puntos == 2)
        CopiaCadena(medalla, "Bronce");
    else
        CopiaCadena(medalla, "Indefinida");

    return medalla;
}

void cargarMedallistas(Nodo **raizMedallistasConOro, Nodo **raizMedallistasConPlata, Nodo **raizMedallistasConBronce, char *archivo)
{
    FILE *baseDatos = fopen(archivo, "rt");

    Medallista leido;
    Medallista *guardar;
    while(fscanf(baseDatos, "%s %s %d", leido.nombre, leido.nacionalidad, &leido.puntos) > 0)
    {
        guardar = (Medallista *)malloc(sizeof(Medallista));
        CopiaCadena(guardar->nombre, leido.nombre);
        CopiaCadena(guardar->nacionalidad, leido.nacionalidad);
        guardar->puntos = leido.puntos;

        if(guardar->puntos == 10)
            insertar(guardar, raizMedallistasConOro);
        else if(guardar->puntos == 5)
            insertar(guardar, raizMedallistasConPlata);
        else if(guardar->puntos == 2)
            insertar(guardar, raizMedallistasConBronce);
    }
}
