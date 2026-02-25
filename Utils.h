#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * @file utils.h
 * @brief Declaracion de utilidades para generacion de arreglos y medicion de tiempos.
 */

 /**
  * @brief Prepara la estructura de datos dinamicamente.
  * @param arreglo Referencia al puntero del arreglo de enteros.
  * @param n Tamano del arreglo (N).
  * @param unicos Verdadero para generar sin repeticiones, Falso para aleatorios puros.
  */
void generarArreglo(int*& arreglo, int n, bool unicos);

/**
 * @brief Ejecuta el algoritmo solicitado midiendo su tiempo en nanosegundos.
 * @param func Puntero a la funcion de ordenamiento basica.
 * @param arreglo Puntero al arreglo original (se clonara para no afectarlo).
 * @param n Tamano del arreglo (N).
 * @param nombreAlgoritmo Etiqueta para imprimir en consola.
 */
void medirTiempo(void (*func)(int*, int, bool), int* arreglo, int n, std::string nombreAlgoritmo);

/**
 * @brief Version del medidor de tiempo especificamente para QuickSort.
 * @param func Puntero a la funcion recursiva de QuickSort.
 * @param arreglo Puntero al arreglo original.
 * @param n Tamano del arreglo (N).
 * @param nombreAlgoritmo Etiqueta para imprimir en consola.
 */
void medirTiempoRec(void (*func)(int*, int, int, int&, int&, bool), int* arreglo, int n, std::string nombreAlgoritmo);

/**
 * @brief Version del medidor de tiempo especificamente para MergeSort.
 * @param func Puntero a la funcion recursiva de MergeSort.
 * @param arreglo Puntero al arreglo original.
 * @param n Tamano del arreglo (N).
 * @param nombreAlgoritmo Etiqueta para imprimir en consola.
 */
void medirTiempoMerge(void (*func)(int*, int, int, int&, bool), int* arreglo, int n, std::string nombreAlgoritmo);

/**
 * @brief Reordena los elementos de forma aleatoria destruyendo cualquier orden previo.
 * @param arreglo Puntero al arreglo de enteros.
 * @param n Tamano del arreglo (N).
 */
void desordenarArreglo(int* arreglo, int n);

#endif