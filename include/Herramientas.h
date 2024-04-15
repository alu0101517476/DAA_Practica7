#pragma once

#include <iostream>
#include <vector>

#include "Solucion.h"

/**
 * @brief Struct que representa una terna de tct y máquina. Útil para el grasp y
 * poder tener una estructura de datos que represente el tct, la máquina y la
 * posición
 */
struct TernaTctGrasp {
  int tct_;
  int maquina_;
  int posicion_;
};

/**
 * @brief Función que calcula el TCT de una máquina
 * @param maquina máquina de la que queremos calcular el TCT
 * @param valores_arcos valores de los arcos
 * @return int
 */
int calcularTCTMaquina(const std::vector<int>& maquina,
                       const std::vector<std::vector<int>>& valores_arcos);

/**
 * @brief Función que calcula el TCT de una máquina después de haber introducido
 * una tarea, útil para el algoritmo voraz
 * @param maquina maquina que se va a modificar
 * @param posicion posición en la que se introduce la tarea
 * @param tarea tarea a introducir
 * @param solucion_algoritmo
 * @param valores_arcos
 * @return int
 */
int calcularTCTOptimo(int maquina, int posicion, int tarea,
                      Solucion& solucion_algoritmo,
                      const std::vector<std::vector<int>>& valores_arcos);

/**
 * @brief Función que calcula el TCT total de todas las máquinas que tiene una
 * solución
 * @param solucion_algoritmo solución de la que se va a calcular el TCT total
 * @param valores_arcos
 * @return int
 */
int calcularTCTTotalMaquinas(
    Solucion& solucion_algoritmo,
    const std::vector<std::vector<int>>& valores_arcos);

/**
 * @brief Sobrecarga de la función anterior, que acepta una estructura de datos
 * que tiene internamente la clase "Solucion" para guardar la solución
 * @param matriz_solucion matriz que contiene la solución
 * @param valores_arcos
 * @return int
 */
int calcularTCTTotalMaquinas(
    std::vector<std::vector<int>>& matriz_solucion,
    const std::vector<std::vector<int>>& valores_arcos);

/**
 * @brief Función que sirve para que el usuario elija por consola que estructura
 * de entorno se va a ejecutar en el algoritmo GRASP
 * @return int la estructura de entorno que se va a ejecutar
 */
int elegirEstructuraEntornoGrasp();

/**
 * @brief Función de ayuda que imprime la información de cómo se ejecuta el programa
 */
void ayuda();