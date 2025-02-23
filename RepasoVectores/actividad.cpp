#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Función para llenar un vector
void llenarVector(vector<int> &v, int n) {
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cout << "Ingrese un numero: ";
        cin >> v[i];
    }
}

// 1. Calcular el promedio de los números
float calcularPromedio(const vector<int> &v) {
    int suma = 0;
    for (int num : v) {
        suma += num;
    }
    return static_cast<float>(suma) / v.size();
}

// 2. Producto de números mayores a 100
long long productoMayores100(const vector<int> &v) {
    long long producto = 1;
    bool encontrado = false;
    for (int num : v) {
        if (num > 100) {
            producto *= num;
            encontrado = true;
        }
    }
    return encontrado ? producto : 0;
}

// 3. Contar números que terminan en 4, inician en 5 y tienen 3 dígitos
int contarNumeros(const vector<int> &v) {
    int contador = 0;
    for (int num : v) {
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

int contarPrimos(const vector<int> &v) {
    int contador = 0;
    for (int num : v) {
        if (esPrimo(num)) contador++;
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

void mostrarMultiplosDe3(const vector<int> &v) {
    for (int num : v) {
        if (sumaDigitos(num) % 3 == 0) {
            cout << num << " ";
        }
    }
    cout << endl;
}

// 6. Calcular la norma de un vector
double calcularNorma(const vector<int> &v) {
    double suma = 0;
    for (int num : v) {
        suma += num * num;
    }
    return sqrt(suma);
}

// 7. Comparar si tres vectores son iguales
bool sonVectoresIguales(const vector<int> &v1, const vector<int> &v2, const vector<int> &v3) {
    return v1 == v2 && v2 == v3;
}

// 8. Encontrar números perfectos
bool esPerfecto(int num) {
    int suma = 0;
    for (int i = 1; i < num; i++) {
        if (num % i == 0) suma += i;
    }
    return suma == num;
}

void mostrarPerfectos(const vector<int> &v) {
    for (int num : v) {
        if (esPerfecto(num)) cout << num << " ";
    }
    cout << endl;
}

// 9. Factorial de cada número
long long factorial(int num) {
    long long resultado = 1;
    for (int i = 2; i <= num; i++) {
        resultado *= i;
    }
    return resultado;
}

void mostrarFactoriales(const vector<int> &v) {
    for (int num : v) {
        cout << "Factorial de " << num << " es " << factorial(num) << endl;
    }
}

// 10. Encontrar el menor número en un vector
int encontrarMinimo(const vector<int> &v) {
    return *min_element(v.begin(), v.end());
}

// 11. Encontrar el mayor número primo en un vector
int mayorPrimo(const vector<int> &v) {
    int maxPrimo = -1;
    for (int num : v) {
        if (esPrimo(num) && num > maxPrimo) maxPrimo = num;
    }
    return maxPrimo;
}

// 12. Imprimir el vector en orden inverso
void imprimirReverso(const vector<int> &v) {
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

// 13. Retornar un vector con los m primeros factoriales
vector<long long> primerosFactoriales(int m) {
    vector<long long> fact(m);
    for (int i = 0; i < m; i++) {
        fact[i] = factorial(i + 1);
    }
    return fact;
}

// 14. Ordenar 10 números ingresados
void ordenarNumeros(vector<int> &v) {
    sort(v.begin(), v.end());
}

// Programa principal con menú
int main() {
    vector<int> v;
    int opcion, n;
    do {
        cout << "\nMENU:\n";
        cout << "1-14. Seleccionar una opcion del problema\n";
        cout << "0. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        
        if (opcion == 0) break;
        cout << "Ingrese tamaño del vector: ";
        cin >> n;
        llenarVector(v, n);
        
        switch (opcion) {
            case 1: cout << calcularPromedio(v) << endl; break;
            case 2: cout << productoMayores100(v) << endl; break;
            case 3: cout << contarNumeros(v) << endl; break;
            case 4: cout << contarPrimos(v) << endl; break;
            case 5: mostrarMultiplosDe3(v); break;
            case 6: cout << calcularNorma(v) << endl; break;
            case 7: cout << "No implementado en menú" << endl; break;
            case 8: mostrarPerfectos(v); break;
            case 9: mostrarFactoriales(v); break;
            case 10: cout << encontrarMinimo(v) << endl; break;
            case 11: cout << mayorPrimo(v) << endl; break;
            case 12: imprimirReverso(v); break;
            case 13: cout << "Ingrese m: "; cin >> n; primerosFactoriales(n); break;
            case 14: ordenarNumeros(v); break;
        }
    } while (opcion != 0);
    return 0;
}
