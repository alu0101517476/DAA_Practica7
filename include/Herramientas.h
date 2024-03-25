#pragma once

#include <iostream>
#include <vector>

#include "Solucion.h"

int calcularIncrementoTCT(Solucion& solucion, int maquina, int tarea,
                          int posicion, std::vector<int> procesamiento_tareas,
                          std::vector<std::vector<int>> tiempos_setup);