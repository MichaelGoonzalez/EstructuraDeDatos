#include<stdlib.h> 
#include<stdio.h>
#include <locale.h>

typedef struct nodo_arbol {
    int dato;
    struct nodo_arbol *izquierdo;
    struct nodo_arbol *derecho;
} NodoAR;

typedef NodoAR *Arbol;

/////////////////////////////menú general
void menu(){
    printf("\nBIENVENIDO AL MARAVILLOSO MUNDO DE LOS ARBOLES BINARIOS\n");
    printf("1. Insertar elemento\n");
    printf("2. Recorrer Arbol\n");
    printf("3. Imprimir nodos que terminan en 7\n");
    printf("4. Contar nodos del Arbol\n");
    printf("5. Contar nodos multiplos de 5\n");
    printf("6. Determinar si un elemento es una hoja\n");
    printf("7. Eliminar Arbol\n");
    printf("8. Eliminar nodo\n");
    printf("9. SALIR\n");
}

////////////sub menú para el caso de recorrer el Arbol
void menu_recorrido(){
    printf("RECORRIDO DE ARBOLES BINARIOS\n");
    printf("1. Preorden\n");
    printf("2. Inorden\n");
    printf("3. Postorden\n");
    printf("4. SALIR\n");
}

// Verifica si el Arbol está vacío
int Vacio(Arbol r){
    return r == NULL;
}

// Inserta un nuevo nodo en el Arbol
int insertar_arbol(Arbol *a, int dat){
    Arbol padre = NULL; 
    Arbol actual = *a;

    while(!Vacio(actual) && dat != actual->dato) {
        padre = actual;
        if(dat < actual->dato) 
            actual = actual->izquierdo; 
        else 
            actual = actual->derecho; 
    }

    if(!Vacio(actual)) return 1; // Ya existe

    Arbol nuevo = (Arbol)malloc(sizeof(NodoAR));
    nuevo->dato = dat;
    nuevo->izquierdo = nuevo->derecho = NULL;

    if (Vacio(padre)) {
        *a = nuevo; // Primer nodo (raíz)
    } else if (dat < padre->dato) {
        padre->izquierdo = nuevo;
    } else {
        padre->derecho = nuevo;
    }
    return 0;
}

/////////////////// Recorridos ///////////////////
void preorden(Arbol a) {
    if (a != NULL) {
        printf("%d ", a->dato);
        preorden(a->izquierdo);
        preorden(a->derecho);
    }
}

void inorden(Arbol a) {
    if (a != NULL) {
        inorden(a->izquierdo);
        printf("%d ", a->dato);
        inorden(a->derecho);
    }
}

void postorden(Arbol a) {
    if (a != NULL) {
        postorden(a->izquierdo);
        postorden(a->derecho);
        printf("%d ", a->dato);
    }
}

/////////////////// Nodos que terminan en 7 ///////////////////
void termina7(Arbol a) {
    if (a != NULL) {
        if (a->dato % 10 == 7) {
            printf("%d ", a->dato);
        }
        termina7(a->izquierdo);
        termina7(a->derecho);
    }
}

/////////////////// Contar todos los nodos ///////////////////
int contarNodos(Arbol a) {
    if (a == NULL) return 0;
    return 1 + contarNodos(a->izquierdo) + contarNodos(a->derecho);
}

/////////////////// Contar multiplos de 5 ///////////////////
int contarMultiplos5(Arbol a) {
    if (a == NULL) return 0;
    int suma = (a->dato % 5 == 0) ? 1 : 0;
    return suma + contarMultiplos5(a->izquierdo) + contarMultiplos5(a->derecho);
}

/////////////////// Verifica si un nodo es hoja ///////////////////
int esHoja(Arbol a, int valor) {
    if (a == NULL) return 0;
    if (a->dato == valor)
        return (a->izquierdo == NULL && a->derecho == NULL);
    if (valor < a->dato)
        return esHoja(a->izquierdo, valor);
    else
        return esHoja(a->derecho, valor);
}

/////////////////// Eliminar todo el Arbol ///////////////////
void eliminarArbol(Arbol *a) {
    if (*a != NULL) {
        eliminarArbol(&((*a)->izquierdo));
        eliminarArbol(&((*a)->derecho));
        free(*a);
        *a = NULL;
    }
}

/////////////////// Eliminar un nodo ///////////////////
Arbol eliminarNodo(Arbol raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->dato) {
        raiz->izquierdo = eliminarNodo(raiz->izquierdo, valor);
    } else if (valor > raiz->dato) {
        raiz->derecho = eliminarNodo(raiz->derecho, valor);
    } else {
        // Nodo encontrado
        if (raiz->izquierdo == NULL) {
            Arbol temp = raiz->derecho;
            free(raiz);
            return temp;
        } else if (raiz->derecho == NULL) {
            Arbol temp = raiz->izquierdo;
            free(raiz);
            return temp;
        } else {
            // Nodo con dos hijos: buscar el mínimo en el subArbol derecho
            Arbol sucesor = raiz->derecho;
            while (sucesor->izquierdo != NULL)
                sucesor = sucesor->izquierdo;

            raiz->dato = sucesor->dato;
            raiz->derecho = eliminarNodo(raiz->derecho, sucesor->dato);
        }
    }
    return raiz;
}

////////////////////////////////////////////////////////////////////////////////

int main(){
    setlocale(LC_ALL, "");
    int valor_ingreso, opc=0, opc_recorrido=0;
    Arbol p = NULL;

    while(opc != 9){
        system("cls");
        menu();
        scanf("%d", &opc);

        switch(opc){
            case 1:
                system("cls");
                printf("Ingrese elementos (-1 para terminar):\n");
                scanf("%d", &valor_ingreso);
                while(valor_ingreso != -1){
                    if (insertar_arbol(&p, valor_ingreso) == 1)
                        printf("El dato ya existe en el Arbol.\n");
                    else
                        printf("Dato insertado correctamente.\n");
                    scanf("%d", &valor_ingreso);
                }
                system("pause");
                break;

            case 2:
                do {
                    system("cls");
                    menu_recorrido();
                    scanf("%d", &opc_recorrido);
                    switch(opc_recorrido){
                        case 1:
                            printf("Preorden:\n");
                            preorden(p);
                            break;
                        case 2:
                            printf("Inorden:\n");
                            inorden(p);
                            break;
                        case 3:
                            printf("Postorden:\n");
                            postorden(p);
                            break;
                    }
                    printf("\n");
                    system("pause");
                } while(opc_recorrido != 4);
                break;

            case 3:
                system("cls");
                printf("Nodos que terminan en 7:\n");
                termina7(p);
                printf("\n");
                system("pause");
                break;

            case 4:
                system("cls");
                printf("Total de nodos en el Arbol: %d\n", contarNodos(p));
                system("pause");
                break;

            case 5:
                system("cls");
                printf("Cantidad de nodos multiplos de 5: %d\n", contarMultiplos5(p));
                system("pause");
                break;

            case 6:
                system("cls");
                printf("Ingrese el valor a verificar si es hoja: ");
                scanf("%d", &valor_ingreso);
                if (esHoja(p, valor_ingreso))
                    printf("El nodo %d es una hoja.\n", valor_ingreso);
                else
                    printf("El nodo %d NO es una hoja.\n", valor_ingreso);
                system("pause");
                break;

            case 7:
                system("cls");
                eliminarArbol(&p);
                printf("Arbol eliminado correctamente.\n");
                system("pause");
                break;

            case 8:
                system("cls");
                printf("Ingrese el valor a eliminar: ");
                scanf("%d", &valor_ingreso);
                p = eliminarNodo(p, valor_ingreso);
                printf("Nodo eliminado si existía.\n");
                system("pause");
                break;

            case 9:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opción inválida.\n");
                system("pause");
        }
    }
    return 0;
}
