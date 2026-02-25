#include "GestorArreglo.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Inicializa el puntero en nulo y establece el estado base del objeto.
GestorArreglo::GestorArreglo()
{
    arreglo = nullptr;
    n = 0;
    estaOrdenado = false;
}

// Libera la memoria dinamica ocupada por el arreglo al destruir la instancia.
GestorArreglo::~GestorArreglo()
{
    if (arreglo != nullptr) {
        delete[] arreglo;
    }
}

// Dimensiona el arreglo en memoria. Por un lado, genera numeros unicos con saltos aleatorios; por el otro, inserta valores repetidos.
void GestorArreglo::configurar(int tam, bool unicos)
{
    if (arreglo != nullptr) {
        delete[] arreglo;
    }

    n = tam;
    arreglo = new int[n];
    estaOrdenado = false;
    srand((unsigned int)time(NULL));

    if (unicos) {
        vector<int> bolsa(n);
        int acumulador = 1;
        for (int i = 0; i < n; i++) {
            acumulador += (rand() % 25) + 1;
            bolsa[i] = acumulador;
        }

        unsigned int seed = (unsigned int)system_clock::now().time_since_epoch().count();
        shuffle(bolsa.begin(), bolsa.end(), default_random_engine(seed));

        for (int i = 0; i < n; i++) arreglo[i] = bolsa[i];
    }
    else {
        for (int i = 0; i < n; i++) {
            arreglo[i] = rand() % 10000;
        }
    }
}

// Revuelve los elementos actuales usando una semilla de tiempo real, por lo tanto, destruye cualquier orden previo.
void GestorArreglo::desordenar()
{
    unsigned int seed = (unsigned int)system_clock::now().time_since_epoch().count();
    shuffle(arreglo, arreglo + n, default_random_engine(seed));
    estaOrdenado = false;
}

// Despliega el contenido en pantalla, sin embargo, limita la impresion a 50 elementos para evitar saturacion.
void GestorArreglo::mostrar()
{
    if (n > 50) {
        cout << "(El arreglo es mayor a 50 elementos, se oculta para no saturar la pantalla)\n";
        return;
    }
    cout << "\nArreglo: ";
    for (int i = 0; i < n; i++) cout << arreglo[i] << " ";
    cout << endl;
}

bool GestorArreglo::getEstaOrdenado() { return estaOrdenado; }
int GestorArreglo::getN() { return n; }

// Escanea linealmente la estructura en busca del elemento.
int GestorArreglo::busquedaSecuencial(int valor)
{
    for (int i = 0; i < n; i++) {
        if (arreglo[i] == valor) return i;
    }
    return -1;
}

// Asegura el ordenamiento previo y busca el valor seccionando el arreglo por mitades.
int GestorArreglo::busquedaBinaria(int valor)
{
    if (!estaOrdenado) ordenarQuickSort(false);

    int izquierda = 0, derecha = n - 1, medio;
    while (izquierda <= derecha) {
        medio = (izquierda + derecha) / 2;
        if (arreglo[medio] == valor) return medio;
        else if (arreglo[medio] < valor) izquierda = medio + 1;
        else derecha = medio - 1;
    }
    return -1;
}

// Ordena moviendo los valores altos al fondo iterativamente.
void GestorArreglo::ordenarBurbuja(bool mostrarPasos)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (arreglo[j] > arreglo[j + 1]) {
                if (mostrarPasos) cout << "[Burbuja] Intercambiando " << arreglo[j] << " con " << arreglo[j + 1] << endl;
                temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
            }
        }
    }
    estaOrdenado = true;
}

// Posiciona el valor mas bajo encontrado al inicio del ciclo actual.
void GestorArreglo::ordenarSeleccion(bool mostrarPasos)
{
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (arreglo[j] < arreglo[min]) min = j;
        }
        if (mostrarPasos && min != i) cout << "[Seleccion] Moviendo minimo " << arreglo[min] << " a posicion " << i << endl;
        temp = arreglo[i];
        arreglo[i] = arreglo[min];
        arreglo[min] = temp;
    }
    estaOrdenado = true;
}

// Inserta cada numero en su lugar correspondiente desplazando los demas a la derecha.
void GestorArreglo::ordenarInsercion(bool mostrarPasos)
{
    int i, j, clave;
    for (i = 1; i < n; i++) {
        clave = arreglo[i];
        j = i - 1;
        while (j >= 0 && arreglo[j] > clave) {
            if (mostrarPasos) cout << "[Insercion] Desplazando " << arreglo[j] << " a la derecha" << endl;
            arreglo[j + 1] = arreglo[j];
            j--;
        }
        arreglo[j + 1] = clave;
    }
    estaOrdenado = true;
}

// Fragmenta la informacion basandose en un pivote central recursivamente.
void GestorArreglo::quickSortRec(int* arr, int izquierda, int derecha, int& comparaciones, int& intercambios, bool mostrarPasos)
{
    int i = izquierda, j = derecha;
    int pivote = arr[(izquierda + derecha) / 2];
    int temp;

    if (mostrarPasos) cout << "[QuickSort] Pivote: " << pivote << " Rango: " << izquierda << "-" << derecha << endl;

    while (i <= j) {
        while (arr[i] < pivote) { i++; comparaciones++; }
        while (arr[j] > pivote) { j--; comparaciones++; }
        if (i <= j) {
            temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            intercambios++; i++; j--;
        }
    }
    if (izquierda < j) quickSortRec(arr, izquierda, j, comparaciones, intercambios, mostrarPasos);
    if (i < derecha) quickSortRec(arr, i, derecha, comparaciones, intercambios, mostrarPasos);
}

void GestorArreglo::ordenarQuickSort(bool mostrarPasos)
{
    int comp = 0, inter = 0;
    quickSortRec(arreglo, 0, n - 1, comp, inter, mostrarPasos);
    estaOrdenado = true;
}

// Fusiona sub-listas preordenadas instanciando memoria temporal.
void GestorArreglo::merge(int* arr, int izquierda, int medio, int derecha, int& comparaciones, bool mostrarPasos)
{
    int i = izquierda, j = medio + 1, k = 0;
    int* temp = new int[derecha - izquierda + 1]();

    while (i <= medio && j <= derecha) {
        comparaciones++;
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= medio) temp[k++] = arr[i++];
    while (j <= derecha) temp[k++] = arr[j++];

    for (i = izquierda, k = 0; i <= derecha; i++, k++) arr[i] = temp[k];

    if (mostrarPasos) cout << "[Merge] Fusionando rango " << izquierda << " a " << derecha << endl;
    delete[] temp;
}

// Separa el arreglo iterativamente por mitades para procesar su orden.
void GestorArreglo::mergeSortRec(int* arr, int izquierda, int derecha, int& comparaciones, bool mostrarPasos)
{
    int medio;
    if (izquierda < derecha) {
        medio = (izquierda + derecha) / 2;
        mergeSortRec(arr, izquierda, medio, comparaciones, mostrarPasos);
        mergeSortRec(arr, medio + 1, derecha, comparaciones, mostrarPasos);
        merge(arr, izquierda, medio, derecha, comparaciones, mostrarPasos);
    }
}

void GestorArreglo::ordenarMergeSort(bool mostrarPasos)
{
    int comp = 0;
    mergeSortRec(arreglo, 0, n - 1, comp, mostrarPasos);
    estaOrdenado = true;
}

// Crea un entorno aislado clonando el arreglo original, ejecuta cada metodo midiendo su duracion exacta y finalmente restaura los datos.
void GestorArreglo::compararTiempos()
{
    cout << "\n=== TIEMPOS DE EJECUCION (N=" << n << ") ===\n";

    int* respaldo = new int[n];
    for (int i = 0; i < n; i++) respaldo[i] = arreglo[i];

    auto medir = [&](void (GestorArreglo::* algoritmo)(bool), string nombre) {
        for (int i = 0; i < n; i++) arreglo[i] = respaldo[i];

        auto inicio = high_resolution_clock::now();
        (this->*algoritmo)(false);
        auto fin = high_resolution_clock::now();

        auto duracion = duration_cast<nanoseconds>(fin - inicio);
        cout << "Tiempo " << nombre << ": " << duracion.count() << " nanosegundos." << endl;
        };

    medir(&GestorArreglo::ordenarBurbuja, "Burbuja");
    medir(&GestorArreglo::ordenarSeleccion, "Seleccion");
    medir(&GestorArreglo::ordenarInsercion, "Insercion");
    medir(&GestorArreglo::ordenarQuickSort, "QuickSort");
    medir(&GestorArreglo::ordenarMergeSort, "MergeSort");

    for (int i = 0; i < n; i++) arreglo[i] = respaldo[i];
    estaOrdenado = false;
    delete[] respaldo;
}