#pragma once
#ifndef GESTOR_ARREGLO_H
#define GESTOR_ARREGLO_H

/**
 * @class GestorArreglo
 * @brief Administra la memoria del arreglo y ejecuta los algoritmos. Centraliza los datos y sus operaciones.
 */
class GestorArreglo
{
private:
    int* arreglo;
    int n;
    bool estaOrdenado;

    void quickSortRec(int* arr, int izquierda, int derecha, int& comp, int& inter, bool mostrar);
    void merge(int* arr, int izquierda, int medio, int derecha, int& comp, bool mostrar);
    void mergeSortRec(int* arr, int izquierda, int derecha, int& comp, bool mostrar);

public:
    /**
     * @brief Inicializa el puntero en nulo y establece el estado base del objeto.
     */
    GestorArreglo();

    /**
     * @brief Libera la memoria dinamica ocupada por el arreglo al destruir la instancia.
     */
    ~GestorArreglo();

    /**
     * @brief Dimensiona el arreglo en memoria. Genera numeros unicos o con valores repetidos.
     * @param tam El tamano total (N) del arreglo a generar.
     * @param unicos Verdadero para generar sin repeticiones, Falso para aleatorios puros.
     */
    void configurar(int tam, bool unicos);

    /**
     * @brief Revuelve los elementos actuales usando una semilla de tiempo real, destruyendo cualquier orden previo.
     */
    void desordenar();

    /**
     * @brief Despliega el contenido en pantalla (limita la impresion a 50 elementos para evitar saturacion).
     */
    void mostrar();

    /**
     * @brief Devuelve el estado actual del arreglo.
     * @return Verdadero si esta ordenado, falso de lo contrario.
     */
    bool getEstaOrdenado();

    /**
     * @brief Obtiene el tamano actual del arreglo.
     * @return Entero con la cantidad de elementos (N).
     */
    int getN();

    /**
     * @brief Escanea linealmente la estructura en busca del elemento.
     * @param valor El numero entero que se desea encontrar.
     * @return El indice donde se encontro el valor, o -1 si no existe.
     */
    int busquedaSecuencial(int valor);

    /**
     * @brief Asegura el ordenamiento previo y busca el valor seccionando el arreglo por mitades.
     * @param valor El numero entero que se desea encontrar.
     * @return El indice donde se encontro el valor, o -1 si no existe.
     */
    int busquedaBinaria(int valor);

    /**
     * @brief Ordena moviendo los valores altos al fondo iterativamente.
     * @param mostrar Verdadero para imprimir cada paso en consola.
     */
    void ordenarBurbuja(bool mostrar);

    /**
     * @brief Posiciona el valor mas bajo encontrado al inicio del ciclo actual.
     * @param mostrar Verdadero para imprimir cada paso en consola.
     */
    void ordenarSeleccion(bool mostrar);

    /**
     * @brief Inserta cada numero en su lugar correspondiente desplazando los demas a la derecha.
     * @param mostrar Verdadero para imprimir cada paso en consola.
     */
    void ordenarInsercion(bool mostrar);

    /**
     * @brief Fragmenta la informacion basandose en un pivote central recursivamente.
     * @param mostrar Verdadero para imprimir cada paso en consola.
     */
    void ordenarQuickSort(bool mostrar);

    /**
     * @brief Separa el arreglo iterativamente por mitades para procesar su orden.
     * @param mostrar Verdadero para imprimir cada paso en consola.
     */
    void ordenarMergeSort(bool mostrar);

    /**
     * @brief Crea un entorno aislado clonando el arreglo, ejecuta cada metodo midiendo su duracion exacta y restaura los datos.
     */
    void compararTiempos();
};

#endif