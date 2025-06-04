#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DESCUENTO 0.15
#define MAX_LIBROS_VENTA 5
#define ARCHIVO_LIBROS "inventario.csv"
#define ARCHIVO_VENTAS "ventas.csv"

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

// Función para guardar libros en archivo CSV
void guardarLibros() {
    FILE* archivo = fopen(ARCHIVO_LIBROS, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de inventario.\n");
        return;
    }

    // Escribir encabezados
    fprintf(archivo, "Titulo,Autor,Anio,Genero,Paginas,Editorial,ISSN,Idioma,Fecha,Estado,Precio,Cantidad\n");

    // Escribir datos de cada libro
    Libro* temp = cabezaLibros;
    while (temp != NULL) {
        fprintf(archivo, "%s,%s,%d,%s,%d,%s,%s,%s,%s,%s,%.2f,%d\n",
                temp->titulo, temp->autor, temp->anio_publicacion,
                temp->genero, temp->num_paginas, temp->editorial,
                temp->issn, temp->idioma, temp->fecha_publicacion,
                temp->estado, temp->precio, temp->cantidad);
        temp = temp->siguiente;
    }

    fclose(archivo);
    printf("Inventario guardado exitosamente.\n");
}

// Función para cargar libros desde archivo CSV
void cargarLibros() {
    FILE* archivo = fopen(ARCHIVO_LIBROS, "r");
    if (archivo == NULL) {
        printf("No se encontró archivo de inventario. Se creará uno nuevo.\n");
        return;
    }

    char linea[1024];
    // Saltar la línea de encabezados
    fgets(linea, sizeof(linea), archivo);

    while (fgets(linea, sizeof(linea), archivo)) {
        Libro* nuevo = (Libro*)malloc(sizeof(Libro));
        
        // Parsear la línea CSV
        char* token = strtok(linea, ",");
        strcpy(nuevo->titulo, token);
        
        token = strtok(NULL, ",");
        strcpy(nuevo->autor, token);
        
        token = strtok(NULL, ",");
        nuevo->anio_publicacion = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(nuevo->genero, token);
        
        token = strtok(NULL, ",");
        nuevo->num_paginas = atoi(token);
        
        token = strtok(NULL, ",");
        strcpy(nuevo->editorial, token);
        
        token = strtok(NULL, ",");
        strcpy(nuevo->issn, token);
        
        token = strtok(NULL, ",");
        strcpy(nuevo->idioma, token);
        
        token = strtok(NULL, ",");
        strcpy(nuevo->fecha_publicacion, token);
        
        token = strtok(NULL, ",");
        strcpy(nuevo->estado, token);
        
        token = strtok(NULL, ",");
        nuevo->precio = atof(token);
        
        token = strtok(NULL, ",");
        nuevo->cantidad = atoi(token);

        // Insertar al principio de la lista
        nuevo->anterior = NULL;
        nuevo->siguiente = cabezaLibros;
        if (cabezaLibros != NULL) {
            cabezaLibros->anterior = nuevo;
        }
        cabezaLibros = nuevo;
    }

    fclose(archivo);
    printf("Inventario cargado exitosamente.\n");
}

// Función para guardar ventas en archivo CSV
void guardarVentas() {
    FILE* archivo = fopen(ARCHIVO_VENTAS, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de ventas.\n");
        return;
    }

    // Escribir encabezados
    fprintf(archivo, "Documento,Nombre,Telefono,Total_Libros,Total_Pago\n");

    // Escribir datos de cada venta
    Venta* temp = cabezaVentas;
    while (temp != NULL) {
        fprintf(archivo, "%s,%s,%s,%d,%.2f\n",
                temp->documento, temp->nombre, temp->telefono,
                temp->total_libros, temp->total_pago);
        temp = temp->siguiente;
    }

    fclose(archivo);
    printf("Ventas guardadas exitosamente.\n");
}

// Función para cargar ventas desde archivo CSV
void cargarVentas() {
    FILE* archivo = fopen(ARCHIVO_VENTAS, "r");
    if (archivo == NULL) {
        printf("No se encontró archivo de ventas. Se creará uno nuevo.\n");
        return;
    }

    char linea[1024];
    // Saltar la línea de encabezados
    fgets(linea, sizeof(linea), archivo);

    while (fgets(linea, sizeof(linea), archivo)) {
        Venta* nueva = (Venta*)malloc(sizeof(Venta));
        
        // Parsear la línea CSV
        char* token = strtok(linea, ",");
        strcpy(nueva->documento, token);
        
        token = strtok(NULL, ",");
        strcpy(nueva->nombre, token);
        
        token = strtok(NULL, ",");
        strcpy(nueva->telefono, token);
        
        token = strtok(NULL, ",");
        nueva->total_libros = atoi(token);
        
        token = strtok(NULL, ",");
        nueva->total_pago = atof(token);

        // Insertar al principio de la lista
        nueva->anterior = NULL;
        nueva->siguiente = cabezaVentas;
        if (cabezaVentas != NULL) {
            cabezaVentas->anterior = nueva;
        }
        cabezaVentas = nueva;
    }

    fclose(archivo);
    printf("Ventas cargadas exitosamente.\n");
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
    guardarLibros(); // Guardar después de agregar
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
    guardarLibros(); // Guardar después de editar
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
    guardarLibros(); // Guardar después de eliminar
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

// Función para vender libros
void venderLibro() {
    Venta* nuevaVenta = (Venta*)malloc(sizeof(Venta));
    printf("\n--- Vender Libros ---\n");
    
    printf("Documento del cliente: ");
    fflush(stdin);
    fgets(nuevaVenta->documento, 20, stdin);
    nuevaVenta->documento[strcspn(nuevaVenta->documento, "\n")] = 0;

    printf("Nombre del cliente: ");
    fflush(stdin);
    fgets(nuevaVenta->nombre, 100, stdin);
    nuevaVenta->nombre[strcspn(nuevaVenta->nombre, "\n")] = 0;

    printf("Teléfono del cliente: ");
    fflush(stdin);
    fgets(nuevaVenta->telefono, 20, stdin);
    nuevaVenta->telefono[strcspn(nuevaVenta->telefono, "\n")] = 0;

    nuevaVenta->total_libros = 0;
    nuevaVenta->total_pago = 0;

    char continuar;
    do {
        if (nuevaVenta->total_libros >= MAX_LIBROS_VENTA) {
            printf("Se ha alcanzado el máximo de libros por venta.\n");
            break;
        }

        char titulo[100];
        printf("\nTítulo del libro a vender: ");
        fflush(stdin);
        fgets(titulo, 100, stdin);
        titulo[strcspn(titulo, "\n")] = 0;

        Libro* libro = buscarLibro(titulo, "Nuevo");
        if (libro == NULL) {
            libro = buscarLibro(titulo, "Usado");
        }

        if (libro == NULL) {
            printf("Libro no encontrado.\n");
            continue;
        }

        int cantidad;
        printf("Cantidad a vender: ");
        scanf("%d", &cantidad);

        if (cantidad > libro->cantidad) {
            printf("No hay suficiente stock disponible.\n");
            continue;
        }

        // Agregar libro a la venta
        strcpy(nuevaVenta->titulos[nuevaVenta->total_libros], libro->titulo);
        nuevaVenta->cantidades[nuevaVenta->total_libros] = cantidad;
        nuevaVenta->precios[nuevaVenta->total_libros] = libro->precio;
        nuevaVenta->total_libros++;

        // Actualizar stock
        libro->cantidad -= cantidad;

        printf("¿Desea agregar otro libro? (s/n): ");
        fflush(stdin);
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    // Calcular total
    for (int i = 0; i < nuevaVenta->total_libros; i++) {
        nuevaVenta->total_pago += nuevaVenta->precios[i] * nuevaVenta->cantidades[i];
    }

    // Aplicar descuento si corresponde
    if (nuevaVenta->total_pago > 200000) {
        nuevaVenta->total_pago *= (1 - DESCUENTO);
    }

    // Insertar venta al principio de la lista
    nuevaVenta->anterior = NULL;
    nuevaVenta->siguiente = cabezaVentas;
    if (cabezaVentas != NULL) {
        cabezaVentas->anterior = nuevaVenta;
    }
    cabezaVentas = nuevaVenta;

    printf("\nVenta realizada con éxito.\n");
    imprimirFactura(nuevaVenta->documento);
    guardarLibros(); // Guardar inventario actualizado
    guardarVentas(); // Guardar nueva venta
}

// Función para editar una venta
void editarVenta() {
    char documento[20];
    printf("\n--- Editar Venta ---\n");
    printf("Documento de la venta a editar: ");
    fflush(stdin);
    fgets(documento, 20, stdin);
    documento[strcspn(documento, "\n")] = 0;

    Venta* venta = cabezaVentas;
    while (venta != NULL) {
        if (strcmp(venta->documento, documento) == 0) {
            // Mostrar venta actual
            printf("\nVenta actual:\n");
            for (int i = 0; i < venta->total_libros; i++) {
                printf("%d. %s - Cantidad: %d - Precio: $%.2f\n",
                       i + 1, venta->titulos[i], venta->cantidades[i], venta->precios[i]);
            }

            // Editar libros
            int opcion;
            printf("\nSeleccione el número del libro a editar (0 para terminar): ");
            scanf("%d", &opcion);

            while (opcion > 0 && opcion <= venta->total_libros) {
                int nuevaCantidad;
                printf("Nueva cantidad para %s: ", venta->titulos[opcion - 1]);
                scanf("%d", &nuevaCantidad);

                // Buscar libro para actualizar stock
                Libro* libro = buscarLibro(venta->titulos[opcion - 1], "Nuevo");
                if (libro == NULL) {
                    libro = buscarLibro(venta->titulos[opcion - 1], "Usado");
                }

                if (libro != NULL) {
                    // Ajustar stock
                    libro->cantidad += venta->cantidades[opcion - 1] - nuevaCantidad;
                    venta->cantidades[opcion - 1] = nuevaCantidad;
                }

                printf("\nSeleccione el número del libro a editar (0 para terminar): ");
                scanf("%d", &opcion);
            }

            // Recalcular total
            venta->total_pago = 0;
            for (int i = 0; i < venta->total_libros; i++) {
                venta->total_pago += venta->precios[i] * venta->cantidades[i];
            }

            // Aplicar descuento si corresponde
            if (venta->total_pago > 200000) {
                venta->total_pago *= (1 - DESCUENTO);
            }

            printf("\nVenta actualizada con éxito.\n");
            imprimirFactura(documento);
            guardarLibros(); // Guardar inventario actualizado
            guardarVentas(); // Guardar venta actualizada
            return;
        }
        venta = venta->siguiente;
    }
    printf("Venta no encontrada.\n");
}

// Función para eliminar una venta
void eliminarVenta() {
    char documento[20];
    printf("\n--- Eliminar Venta ---\n");
    printf("Documento de la venta a eliminar: ");
    fflush(stdin);
    fgets(documento, 20, stdin);
    documento[strcspn(documento, "\n")] = 0;

    Venta* venta = cabezaVentas;
    while (venta != NULL) {
        if (strcmp(venta->documento, documento) == 0) {
            // Reintegrar libros al stock
            for (int i = 0; i < venta->total_libros; i++) {
                Libro* libro = buscarLibro(venta->titulos[i], "Nuevo");
                if (libro == NULL) {
                    libro = buscarLibro(venta->titulos[i], "Usado");
                }
                if (libro != NULL) {
                    libro->cantidad += venta->cantidades[i];
                }
            }

            // Eliminar venta de la lista
            if (venta->anterior != NULL) {
                venta->anterior->siguiente = venta->siguiente;
            } else {
                cabezaVentas = venta->siguiente;
            }

            if (venta->siguiente != NULL) {
                venta->siguiente->anterior = venta->anterior;
            }

            free(venta);
            printf("Venta eliminada y libros reintegrados al stock.\n");
            guardarLibros(); // Guardar inventario actualizado
            guardarVentas(); // Guardar lista de ventas actualizada
            return;
        }
        venta = venta->siguiente;
    }
    printf("Venta no encontrada.\n");
}

// Función para imprimir factura
void imprimirFactura(const char* documento) {
    Venta* venta = cabezaVentas;
    while (venta != NULL) {
        if (strcmp(venta->documento, documento) == 0) {
            printf("\n========= FACTURA =========\n");
            printf("Documento: %s\n", venta->documento);
            printf("Nombre: %s\n", venta->nombre);
            printf("Teléfono: %s\n", venta->telefono);
            printf("------------------------------\n");
            printf("Libro\t\tCantidad\tPrecio\t\tSubtotal\n");
            
            float subtotal = 0;
            for (int i = 0; i < venta->total_libros; i++) {
                float subtotalLibro = venta->precios[i] * venta->cantidades[i];
                printf("%s\t%d\t\t$%.2f\t\t$%.2f\n",
                       venta->titulos[i], venta->cantidades[i],
                       venta->precios[i], subtotalLibro);
                subtotal += subtotalLibro;
            }

            printf("------------------------------\n");
            printf("Subtotal: $%.2f\n", subtotal);
            
            if (subtotal > 200000) {
                float descuento = subtotal * DESCUENTO;
                printf("Descuento (15%%): -$%.2f\n", descuento);
                printf("Total a pagar: $%.2f\n", subtotal - descuento);
            } else {
                printf("Total a pagar: $%.2f\n", subtotal);
            }
            
            printf("=============================\n");
            return;
        }
        venta = venta->siguiente;
    }
    printf("No se encontró ninguna venta con ese documento.\n");
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
    printf("9. Ver Inventario Completo\n");
    printf("10. Ver Historial de Ventas\n");
    printf("11. Generar Reporte de Ventas\n");
    printf("12. Ver Libros con Stock Bajo\n");
    printf("13. SALIR\n");
}

int main() {
    // Cargar datos al iniciar
    cargarLibros();
    cargarVentas();

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
                venderLibro();
                break;
            case 6:
                editarVenta();
                break;
            case 7:
                eliminarVenta();
                break;
            case 8:
                {
                    char documento[20];
                    printf("Documento de la venta: ");
                    fflush(stdin);
                    fgets(documento, 20, stdin);
                    documento[strcspn(documento, "\n")] = 0;
                    imprimirFactura(documento);
                }
                break;
            case 9:
                mostrarInventarioCompleto();
                break;
            case 10:
                mostrarHistorialVentas();
                break;
            case 11:
                generarReporteVentas();
                break;
            case 12:
                mostrarLibrosStockBajo();
                break;
            case 13:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 13);

    // Guardar datos al salir
    guardarLibros();
    guardarVentas();

    return 0;
}

// Función para mostrar inventario completo
void mostrarInventarioCompleto() {
    printf("\n=== INVENTARIO COMPLETO ===\n");
    printf("Título\t\tAutor\t\tEstado\tPrecio\tStock\n");
    printf("------------------------------------------------\n");
    
    Libro* temp = cabezaLibros;
    while (temp != NULL) {
        printf("%-20s %-20s %-8s $%.2f\t%d\n",
               temp->titulo, temp->autor, temp->estado,
               temp->precio, temp->cantidad);
        temp = temp->siguiente;
    }
    printf("------------------------------------------------\n");
}

// Función para mostrar historial de ventas
void mostrarHistorialVentas() {
    printf("\n=== HISTORIAL DE VENTAS ===\n");
    printf("Documento\tCliente\t\tTotal\tFecha\n");
    printf("------------------------------------------------\n");
    
    Venta* temp = cabezaVentas;
    while (temp != NULL) {
        printf("%-12s %-20s $%.2f\n",
               temp->documento, temp->nombre, temp->total_pago);
        temp = temp->siguiente;
    }
    printf("------------------------------------------------\n");
}

// Función para generar reporte de ventas
void generarReporteVentas() {
    float totalVentas = 0;
    int totalLibrosVendidos = 0;
    int ventasConDescuento = 0;
    
    Venta* temp = cabezaVentas;
    while (temp != NULL) {
        totalVentas += temp->total_pago;
        totalLibrosVendidos += temp->total_libros;
        if (temp->total_pago > 200000) {
            ventasConDescuento++;
        }
        temp = temp->siguiente;
    }
    
    printf("\n=== REPORTE DE VENTAS ===\n");
    printf("Total de ventas realizadas: $%.2f\n", totalVentas);
    printf("Total de libros vendidos: %d\n", totalLibrosVendidos);
    printf("Ventas con descuento: %d\n", ventasConDescuento);
    printf("Promedio por venta: $%.2f\n", 
           cabezaVentas != NULL ? totalVentas / totalLibrosVendidos : 0);
}

// Función para mostrar libros con stock bajo
void mostrarLibrosStockBajo() {
    const int STOCK_MINIMO = 5; // Se considera stock bajo menos de 5 unidades
    printf("\n=== LIBROS CON STOCK BAJO ===\n");
    printf("Título\t\tAutor\t\tStock\n");
    printf("------------------------------------------------\n");
    
    Libro* temp = cabezaLibros;
    int hayStockBajo = 0;
    
    while (temp != NULL) {
        if (temp->cantidad < STOCK_MINIMO) {
            printf("%-20s %-20s %d\n",
                   temp->titulo, temp->autor, temp->cantidad);
            hayStockBajo = 1;
        }
        temp = temp->siguiente;
    }
    
    if (!hayStockBajo) {
        printf("No hay libros con stock bajo.\n");
    }
    printf("------------------------------------------------\n");
}
