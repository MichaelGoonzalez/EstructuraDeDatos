#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DESCUENTO 0.15
#define MAX_LIBROS_VENTA 5

// Estructura para representar un libro
typedef struct Libro {
    char titulo[100];
    char autor[100];
    int anio_publicacion;
    char genero[50];
    int num_paginas;
    char editorial[50];
    char issn[20];
    char idioma[30];
    char fecha_publicacion[11]; // formato dd/mm/aaaa
    char estado[10]; // "Nuevo" o "Usado"
    float precio;
    int cantidad;

    struct Libro* anterior;
    struct Libro* siguiente;
} Libro;

// Estructura para representar una venta
typedef struct Venta {
    char documento[20];
    char nombre[100];
    char telefono[20];

    char titulos[MAX_LIBROS_VENTA][100];
    int cantidades[MAX_LIBROS_VENTA];
    float precios[MAX_LIBROS_VENTA];

    int total_libros;
    float total_pago;

    struct Venta* anterior;
    struct Venta* siguiente;
} Venta;

// Punteros principales para las listas dobles
Libro* cabezaLibros = NULL;
Venta* cabezaVentas = NULL;

// Función para validar si una fecha tiene formato correcto DD/MM/AAAA
int validarFecha(const char* fecha) {
    if (strlen(fecha) != 10) return 0;
    if (fecha[2] != '/' || fecha[5] != '/') return 0;
    return 1;
}

// Función para buscar libro por título y estado
Libro* buscarLibro(char* titulo, char* estado) {
    Libro* temp = cabezaLibros;
    while (temp != NULL) {
        if (strcmp(temp->titulo, titulo) == 0 && strcmp(temp->estado, estado) == 0) {
            return temp;
        }
        temp = temp->siguiente;
    }
    return NULL;
}

// Función para agregar un nuevo libro
void agregarLibro() {
    Libro* nuevo = (Libro*)malloc(sizeof(Libro));
    printf("\n--- Agregar Libro ---\n");

    printf("Titulo: ");
    fflush(stdin);
    fgets(nuevo->titulo, 100, stdin);
    nuevo->titulo[strcspn(nuevo->titulo, "\n")] = 0; // quitar salto de línea

    printf("Autor: ");
    fflush(stdin);
    fgets(nuevo->autor, 100, stdin);
    nuevo->autor[strcspn(nuevo->autor, "\n")] = 0;

    printf("Anio de publicacion: ");
    scanf("%d", &nuevo->anio_publicacion);

    printf("Genero literario: ");
    fflush(stdin);
    fgets(nuevo->genero, 50, stdin);
    nuevo->genero[strcspn(nuevo->genero, "\n")] = 0;

    printf("Numero de paginas: ");
    scanf("%d", &nuevo->num_paginas);

    printf("Editorial: ");
    fflush(stdin);
    fgets(nuevo->editorial, 50, stdin);
    nuevo->editorial[strcspn(nuevo->editorial, "\n")] = 0;

    printf("ISSN: ");
    fflush(stdin);
    fgets(nuevo->issn, 20, stdin);
    nuevo->issn[strcspn(nuevo->issn, "\n")] = 0;

    printf("Idioma: ");
    fflush(stdin);
    fgets(nuevo->idioma, 30, stdin);
    nuevo->idioma[strcspn(nuevo->idioma, "\n")] = 0;

    do {
        printf("Fecha de publicacion (DD/MM/AAAA): ");
        fflush(stdin);
        fgets(nuevo->fecha_publicacion, 11, stdin);
        nuevo->fecha_publicacion[strcspn(nuevo->fecha_publicacion, "\n")] = 0;
    } while (!validarFecha(nuevo->fecha_publicacion));

    do {
        printf("Estado (Nuevo/Usado): ");
        fflush(stdin);
        fgets(nuevo->estado, 10, stdin);
        nuevo->estado[strcspn(nuevo->estado, "\n")] = 0;
    } while (strcmp(nuevo->estado, "Nuevo") != 0 && strcmp(nuevo->estado, "Usado") != 0);

    printf("Precio unitario: ");
    scanf("%f", &nuevo->precio);

    printf("Cantidad de ejemplares: ");
    scanf("%d", &nuevo->cantidad);

    // Verificar que no esté repetido (titulo y estado)
    if (buscarLibro(nuevo->titulo, nuevo->estado) != NULL) {
        printf("ERROR: El libro ya existe con ese estado.\n");
        free(nuevo);
        return;
    }

    // Insertar al principio de la lista
    nuevo->anterior = NULL;
    nuevo->siguiente = cabezaLibros;
    if (cabezaLibros != NULL) {
        cabezaLibros->anterior = nuevo;
    }
    cabezaLibros = nuevo;

    printf("Libro agregado correctamente.\n");
}

// Función para editar un libro
void editarLibro() {
    char titulo[100], estado[10];
    printf("\n--- Editar Libro ---\n");
    printf("Titulo: ");
    fflush(stdin);
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = 0;

    printf("Estado (Nuevo/Usado): ");
    fflush(stdin);
    fgets(estado, 10, stdin);
    estado[strcspn(estado, "\n")] = 0;

    Libro* libro = buscarLibro(titulo, estado);
    if (libro == NULL) {
        printf("Libro no encontrado.\n");
        return;
    }

    printf("Nuevo precio: ");
    scanf("%f", &libro->precio);
    printf("Nueva cantidad: ");
    scanf("%d", &libro->cantidad);

    printf("Libro actualizado correctamente.\n");
}

// Función para eliminar un libro
void eliminarLibro() {
    char titulo[100], estado[10];
    printf("\n--- Eliminar Libro ---\n");
    printf("Titulo: ");
    fflush(stdin);
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = 0;

    printf("Estado (Nuevo/Usado): ");
    fflush(stdin);
    fgets(estado, 10, stdin);
    estado[strcspn(estado, "\n")] = 0;

    Libro* libro = buscarLibro(titulo, estado);
    if (libro == NULL) {
        printf("Libro no encontrado.\n");
        return;
    }

    if (libro->cantidad != 0) {
        printf("No se puede eliminar un libro que tenga existencias.\n");
        return;
    }

    // Ajustar enlaces
    if (libro->anterior != NULL) {
        libro->anterior->siguiente = libro->siguiente;
    } else {
        cabezaLibros = libro->siguiente;
    }

    if (libro->siguiente != NULL) {
        libro->siguiente->anterior = libro->anterior;
    }

    free(libro);
    printf("Libro eliminado correctamente.\n");
}

// Función para buscar e imprimir libros
void buscarImprimirLibro() {
    int opcion;
    printf("\n--- Buscar Libro ---\n");
    printf("1. Buscar por titulo\n");
    printf("2. Buscar por autor\n");
    printf("3. Buscar por estado\n");
    printf("4. Buscar por rango de precios\n");
    printf("Seleccione opcion: ");
    scanf("%d", &opcion);

    Libro* temp = cabezaLibros;
    char busqueda[100];
    float min, max;

    switch(opcion) {
        case 1:
            printf("Titulo a buscar: ");
            fflush(stdin);
            fgets(busqueda, 100, stdin);
            busqueda[strcspn(busqueda, "\n")] = 0;
            while (temp != NULL) {
                if (strcmp(temp->titulo, busqueda) == 0) {
                    printf("Libro encontrado: %s - %s - %s - $%.2f\n", temp->titulo, temp->autor, temp->estado, temp->precio);
                }
                temp = temp->siguiente;
            }
            break;
        case 2:
            printf("Autor a buscar: ");
            fflush(stdin);
            fgets(busqueda, 100, stdin);
            busqueda[strcspn(busqueda, "\n")] = 0;
            while (temp != NULL) {
                if (strcmp(temp->autor, busqueda) == 0) {
                    printf("Libro encontrado: %s - %s - %s - $%.2f\n", temp->titulo, temp->autor, temp->estado, temp->precio);
                }
                temp = temp->siguiente;
            }
            break;
        case 3:
            printf("Estado (Nuevo/Usado): ");
            fflush(stdin);
            fgets(busqueda, 100, stdin);
            busqueda[strcspn(busqueda, "\n")] = 0;
            while (temp != NULL) {
                if (strcmp(temp->estado, busqueda) == 0) {
                    printf("Libro: %s - $%.2f\n", temp->titulo, temp->precio);
                }
                temp = temp->siguiente;
            }
            break;
        case 4:
            printf("Precio minimo: ");
            scanf("%f", &min);
            printf("Precio maximo: ");
            scanf("%f", &max);
            while (temp != NULL) {
                if (temp->precio >= min && temp->precio <= max) {
                    printf("Libro: %s - $%.2f\n", temp->titulo, temp->precio);
                }
                temp = temp->siguiente;
            }
            break;
        default:
            printf("Opcion invalida.\n");
    }
}

// Función para mostrar menú
void mostrarMenu() {
    printf("\n//// Libreria: El libro favorito ////\n");
    printf("1. Agregar Libro\n");
    printf("2. Editar Libro\n");
    printf("3. Eliminar Libro\n");
    printf("4. Buscar/Imprimir Libro\n");
    printf("5. Vender Libro\n");
    printf("6. Editar Venta\n");
    printf("7. Eliminar Venta\n");
    printf("8. Imprimir Factura\n");
    printf("9. SALIR\n");
}

int main() {
    int opcion;
    do {
        mostrarMenu();
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                agregarLibro();
                break;
            case 2:
                editarLibro();
                break;
            case 3:
                eliminarLibro();
                break;
            case 4:
                buscarImprimirLibro();
                break;
            case 5:
                // venderLibro(); (por crear)
                printf("Funcionalidad de vender aún no implementada.\n");
                break;
            case 6:
                // editarVenta(); (por crear)
                printf("Funcionalidad de editar venta aún no implementada.\n");
                break;
            case 7:
                // eliminarVenta(); (por crear)
                printf("Funcionalidad de eliminar venta aún no implementada.\n");
                break;
            case 8:
                // imprimirFactura(); (por crear)
                printf("Funcionalidad de imprimir factura aún no implementada.\n");
                break;
            case 9:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 9);

    return 0;
}
