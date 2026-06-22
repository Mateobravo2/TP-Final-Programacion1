#include "pila.h"

void inicpila(P_Pila p)
{
       p->valores = (int *)malloc(50 * sizeof(int));
       p->postope = 0;
}

void apilar(P_Pila p, int dato)
{
    if (p->postope < 50)
    {
        p->valores[p->postope] = dato;
        p->postope++;
    }
    else
    {
        printf("Error: La pila esta llena, no se puede apilar %d\n", dato);
    }
}

int desapilar(P_Pila p)
{
    if (!pilavacia(p))
    {
       int z = p->valores[p->postope - 1];
       p->postope--;
       return z;
    }
    printf("Error: Intento desapilar una pila vacia.\n");
    return -1;
}

int tope(P_Pila p)
{
    if (!pilavacia(p))
    {
       return p->valores[p->postope - 1];
    }
    printf("Error: La pila esta vacia, no hay tope.\n");
    return -1;
}

int pilavacia(P_Pila p)
{
       return (p->postope == 0);
}

void leer(P_Pila p)
{
    int aux = 0;
    if (p->postope < 50)
    {
        printf("Ingrese un valor entero: ");
        scanf("%d", &aux);
        apilar(p, aux);
    }
    else
        printf("Error: la pila esta llena\n");
}

void mostrar(P_Pila p)
{
    printf("\n BASE ------------> TOPE \n");
    for(int i = 0; i < p->postope; i++)
    {
        printf("| %d ", p->valores[i]);
    }
    printf("\n ------------------------ \n");
}

void freepila(P_Pila p)
{
    if(p->valores != NULL)
    {
        free(p->valores);
        p->valores = NULL;
    }
}
