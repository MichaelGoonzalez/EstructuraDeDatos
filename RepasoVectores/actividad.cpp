#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Función para llenar un vector dinámico
template <typename T>
void llenarVector(T *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Ingrese un número: ";
        cin >> *(arr + i);
    }
}

// 1. Calcular el promedio de los números
float calcularPromedio(int *arr, int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        suma += *(arr + i);
    }
    return static_cast<float>(suma) / n;
}

// 2. Producto de números mayores a 100
long long productoMayores100(int *arr, int n) {
    long long producto = 1;
    bool encontrado = false;
    for (int i = 0; i < n; i++) {
        if (*(arr + i) > 100) {
            producto *= *(arr + i);
            encontrado = true;
        }
    }
    return encontrado ? producto : 0;
}

// 3. Contar números que terminan en 4, inician en 5 y tienen 3 dígitos
int contarNumeros(int *arr, int n) {
    int contador = 0;
    for (int i = 0; i < n; i++) {
        int num = *(arr + i);
        if (num >= 100 && num <= 999 && num % 10 == 4 && to_string(num)[0] == '5') {
            contador++;
        }
    }
    return contador;
}

// 4. Contar números primos
bool esPrimo(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int contarPrimos(int *arr, int n) {
    int contador = 0;
    for (int i = 0; i < n; i++) {
        if (esPrimo(*(arr + i))) contador++;
    }
    return contador;
}

// 5. Suma de dígitos múltiplo de 3
int sumaDigitos(int num) {
    int suma = 0;
    while (num > 0) {
        suma += num % 10;
        num /= 10;
    }
    return suma;
}

void mostrarMultiplosDe3(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (sumaDigitos(*(arr + i)) % 3 == 0) {
            cout << *(arr + i) << " ";
        }
    }
    cout << endl;
}

// 6. Calcular la norma de un vector
double calcularNorma(int *arr, int n) {
    double suma = 0;
    for (int i = 0; i < n; i++) {
        suma += (*(arr + i)) * (*(arr + i));
    }
    return sqrt(suma);
}

// 7. Comparar tres vectores
bool sonIguales(int *a, int *b, int *c, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i] || a[i] != c[i]) return false;
    }
    return true;
}

// 8. Números perfectos
bool esPerfecto(int num) {
    int suma = 0;
    for (int i = 1; i < num; i++) {
        if (num % i == 0) suma += i;
    }
    return suma == num;
}

void mostrarPerfectos(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (esPerfecto(*(arr + i))) cout << *(arr + i) << " ";
    }
    cout << endl;
}

// 9. Factorial de cada número
long long factorial(int num) {
    return (num <= 1) ? 1 : num * factorial(num - 1);
}

void mostrarFactoriales(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << "Factorial de " << *(arr + i) << " es " << factorial(*(arr + i)) << endl;
    }
}

// 10. Encontrar el menor número en un vector
int encontrarMinimo(int *arr, int n) {
    return *min_element(arr, arr + n);
}

// 11. Encontrar el número primo más grande
int mayorPrimo(int *arr, int n) {
    int maxPrimo = -1;
    for (int i = 0; i < n; i++) {
        if (esPrimo(*(arr + i)) && *(arr + i) > maxPrimo) maxPrimo = *(arr + i);
    }
    return maxPrimo;
}

// 12. Imprimir el vector en orden inverso
void imprimirReverso(int *arr, int n) {
    for (int i = n - 1; i >= 0; i--) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

// 13. Generar los primeros m factoriales
void primerosFactoriales(int m) {
    for (int i = 1; i <= m; i++) {
        cout << factorial(i) << " ";
    }
    cout << endl;
}

// 14. Ordenar 10 números
void ordenarVector(int *arr, int n) {
    sort(arr, arr + n);
}

// Programa principal con menú
int main() {
    int *v;
    int opcion, n;
    do {
        cout << "\nMENU:\n";
        cout << "Ingrese una opción (1-14), 0 para salir: ";
        cin >> opcion;
        if (opcion == 0) break;
        cout << "Ingrese tamaño del vector: ";
        cin >> n;
        v = new int[n];
        llenarVector(v, n);
        switch (opcion) {
            case 1: cout << calcularPromedio(v, n) << endl; break;
            case 2: cout << productoMayores100(v, n) << endl; break;
            case 3: cout << contarNumeros(v, n) << endl; break;
            case 4: cout << contarPrimos(v, n) << endl; break;
            case 5: mostrarMultiplosDe3(v, n); break;
            case 6: cout << calcularNorma(v, n) << endl; break;
            case 7: cout << (sonIguales(v, v, v, n) ? "Son iguales" : "No son iguales") << endl; break;
            case 8: mostrarPerfectos(v, n); break;
            case 9: mostrarFactoriales(v, n); break;
            case 10: cout << encontrarMinimo(v, n) << endl; break;
            case 11: cout << mayorPrimo(v, n) << endl; break;
            case 12: imprimirReverso(v, n); break;
            case 13: primerosFactoriales(n); break;
            case 14: ordenarVector(v, n); break;
        }
        delete[] v;
    } while (opcion != 0);
    return 0;
}
