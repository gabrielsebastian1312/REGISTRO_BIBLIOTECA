
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LIBROS 10


struct Libro {
    int id;
    char titulo[101];
    char autor[51];
    int anio;
    char estado[15];
};


void registrarLibro(struct Libro libros[], int *cantidad);
void mostrarLibros(struct Libro libros[], int cantidad);
void buscarPorID(struct Libro libros[], int cantidad);
void buscarPorTitulo(struct Libro libros[], int cantidad);
void actualizarEstado(struct Libro libros[], int cantidad);
void eliminarLibro(struct Libro libros[], int *cantidad);
int validarID(struct Libro libros[], int cantidad, int id);
int leerEntero(char mensaje[]);


int main() {

    struct Libro libros[MAX_LIBROS];
    int cantidad = 0;
    int opcion;

    do {

        printf("\n========== BIBLIOTECA ==========\n");
        printf("1. Registrar libro\n");
        printf("2. Mostrar todos los libros\n");
        printf("3. Buscar libro por ID\n");
        printf("4. Buscar libro por titulo\n");
        printf("5. Actualizar estado del libro\n");
        printf("6. Eliminar libro\n");
        printf("7. Salir\n");
        printf("================================\n");

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {

            case 1:
                registrarLibro(libros, &cantidad);
                break;

            case 2:
                mostrarLibros(libros, cantidad);
                break;

            case 3:
                buscarPorID(libros, cantidad);
                break;

            case 4:
                buscarPorTitulo(libros, cantidad);
                break;

            case 5:
                actualizarEstado(libros, cantidad);
                break;

            case 6:
                eliminarLibro(libros, &cantidad);
                break;

            case 7:
                printf("\nSaliendo del programa...\n");
                break;

            default:
                printf("\nOpcion no valida. Intente nuevamente.\n");
        }

    } while (opcion != 7);

    return 0;
}


int leerEntero(char mensaje[]) {

    char entrada[100];
    char extra;
    int numero;

    while (1) {

        printf("%s", mensaje);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("Error de lectura.\n");
            exit(1);
        }

        if (strchr(entrada, '\n') == NULL) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrada demasiado larga.\n");
            continue;
        }

        if (sscanf(entrada, " %d %c", &numero, &extra) == 1) {
            return numero;
        }

        printf("Error: debe ingresar un numero entero.\n");
    }
}


int validarID(struct Libro libros[], int cantidad, int id) {

    int i;

    for (i = 0; i < cantidad; i++) {

        if (libros[i].id == id) {
            return 0;
        }
    }

    return 1;
}


void registrarLibro(struct Libro libros[], int *cantidad) {

    int id;
    int anio;
    char titulo[101];
    char autor[51];

    if (*cantidad >= MAX_LIBROS) {
        printf("\nLa biblioteca ha alcanzado el limite de 10 libros.\n");
        return;
    }

    printf("\n========== REGISTRAR LIBRO ==========\n");

    id = leerEntero("Ingrese el ID del libro: ");

    if (id <= 0) {
        printf("El ID debe ser un numero positivo.\n");
        return;
    }

    if (!validarID(libros, *cantidad, id)) {
        printf("Error: el ID ya se encuentra registrado.\n");
        return;
    }

    printf("Ingrese el titulo: ");
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    if (strlen(titulo) == 0) {
        printf("El titulo no puede estar vacio.\n");
        return;
    }

    printf("Ingrese el autor: ");
    fgets(autor, sizeof(autor), stdin);
    autor[strcspn(autor, "\n")] = '\0';

    if (strlen(autor) == 0) {
        printf("El autor no puede estar vacio.\n");
        return;
    }

    anio = leerEntero("Ingrese el anio de publicacion: ");

    if (anio <= 0) {
        printf("El anio debe ser positivo.\n");
        return;
    }

    libros[*cantidad].id = id;
    strcpy(libros[*cantidad].titulo, titulo);
    strcpy(libros[*cantidad].autor, autor);
    libros[*cantidad].anio = anio;
    strcpy(libros[*cantidad].estado, "Disponible");

    (*cantidad)++;

    printf("\nLibro registrado correctamente.\n");
}


void mostrarLibros(struct Libro libros[], int cantidad) {

    int i;

    if (cantidad == 0) {
        printf("\nNo existen libros registrados.\n");
        return;
    }

    printf("\n================ LISTA DE LIBROS ================\n");

    printf("%-6s %-25s %-20s %-8s %-12s\n",
           "ID", "TITULO", "AUTOR", "ANIO", "ESTADO");

    printf("---------------------------------------------------------------\n");

    for (i = 0; i < cantidad; i++) {

        printf("%-6d %-25.25s %-20.20s %-8d %-12s\n",
               libros[i].id,
               libros[i].titulo,
               libros[i].autor,
               libros[i].anio,
               libros[i].estado);
    }

    printf("===============================================================\n");
}

void buscarPorID(struct Libro libros[], int cantidad) {

    int id;
    int i;

    id = leerEntero("\nIngrese el ID del libro que desea buscar: ");

    for (i = 0; i < cantidad; i++) {

        if (libros[i].id == id) {

            printf("\n========== INFORMACION DEL LIBRO ==========\n");
            printf("ID: %d\n", libros[i].id);
            printf("Titulo: %s\n", libros[i].titulo);
            printf("Autor: %s\n", libros[i].autor);
            printf("Anio: %d\n", libros[i].anio);
            printf("Estado: %s\n", libros[i].estado);

            return;
        }
    }

    printf("\nNo se encontro ningun libro con ese ID.\n");
}


void buscarPorTitulo(struct Libro libros[], int cantidad) {

    char titulo[101];
    int i;
    int encontrado = 0;

    printf("\nIngrese el titulo del libro: ");

    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    for (i = 0; i < cantidad; i++) {

        if (strcmp(libros[i].titulo, titulo) == 0) {

            printf("\n========== INFORMACION DEL LIBRO ==========\n");
            printf("ID: %d\n", libros[i].id);
            printf("Titulo: %s\n", libros[i].titulo);
            printf("Autor: %s\n", libros[i].autor);
            printf("Anio: %d\n", libros[i].anio);
            printf("Estado: %s\n", libros[i].estado);

            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("\nNo se encontro ningun libro con ese titulo.\n");
    }
}


void actualizarEstado(struct Libro libros[], int cantidad) {

    int id;
    int opcion;
    int i;

    id = leerEntero("\nIngrese el ID del libro: ");

    for (i = 0; i < cantidad; i++) {

        if (libros[i].id == id) {

            printf("\nLibro: %s\n", libros[i].titulo);
            printf("Estado actual: %s\n", libros[i].estado);

            printf("\nSeleccione el nuevo estado:\n");
            printf("1. Disponible\n");
            printf("2. Prestado\n");

            opcion = leerEntero("Ingrese una opcion: ");

            if (opcion == 1) {

                strcpy(libros[i].estado, "Disponible");

            } else if (opcion == 2) {

                strcpy(libros[i].estado, "Prestado");

            } else {

                printf("Opcion no valida.\n");
                return;
            }

            printf("\nEstado actualizado correctamente.\n");
            return;
        }
    }

    printf("\nNo se encontro ningun libro con ese ID.\n");
}


void eliminarLibro(struct Libro libros[], int *cantidad) {

    int id;
    int i;
    int j;

    id = leerEntero("\nIngrese el ID del libro que desea eliminar: ");

    for (i = 0; i < *cantidad; i++) {

        if (libros[i].id == id) {

            // Desplazar los libros posteriores una posicion
            for (j = i; j < *cantidad - 1; j++) {

                libros[j] = libros[j + 1];
            }

            (*cantidad)--;

            printf("\nLibro eliminado correctamente.\n");
            return;
        }
    }

    printf("\nNo se encontro ningun libro con ese ID.\n");
}
