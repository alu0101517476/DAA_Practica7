#include "../include/AlgoritmoGrasp.h"

int AlgoritmoGrasp::calcularTCTTotal() {
  int tct_total{0};
  for (const auto& maquina : solucion_algoritmo_.getSolucion().first) {
    tct_total += calcularTCTMaquina(maquina, problema_.getValoresArcos());
  }
  return tct_total;
}

Solucion AlgoritmoGrasp::faseConstructiva() {
  int numero_maquinas{problema_.getNumeroMaquinas()},
      numero_tareas{problema_.getNumeroTareas()};
  solucion_algoritmo_.setCosteTotal(INT_MAX);
  for (int ejecuciones{0}; ejecuciones < 100; ++ejecuciones) {
    Solucion solucion_actual{problema_.getNumeroMaquinas()};
    // Seleccionamos las m tareas con menores valores de t0j
    for (int i{0}; i < numero_maquinas; ++i) {
      solucion_actual[i].emplace_back(0);
    }
    // Iteramos sobre todas las tareas para asignarlas
    for (int tarea{1}; tarea <= numero_tareas; ++tarea) {
      // Busca la mejor posición y máquina para la tarea
      std::vector<TernaTctGrasp> lista_candidatos_restringida;
      for (int maquina{0}; maquina < numero_maquinas; ++maquina) {
        for (int posicion{0}; posicion < solucion_actual[maquina].size();
             ++posicion) {
          int tct{calcularTCTOptimo(maquina, posicion, tarea, solucion_actual,
                                    problema_.getValoresArcos())};
          // Introducimos los posibles candidatos
          TernaTctGrasp candidato{tct, maquina, posicion};
          lista_candidatos_restringida.emplace_back(candidato);
        }
        std::sort(lista_candidatos_restringida.begin(),
                  lista_candidatos_restringida.end(),
                  [](const TernaTctGrasp& candidato1,
                     const TernaTctGrasp& candidato2) {
                    return candidato1.tct_ < candidato2.tct_;
                  });
      }
      // Escogemos uno de los 3 mejores candidatos al azar
      int inicio_indice_aleatorio{0}, final_indice_aleatorio{0},
          numero_candidatos{lista_candidatos_restringida.size()};
      if (lista_candidatos_restringida.size() >= 3) {
        final_indice_aleatorio = 2;
      } else if (lista_candidatos_restringida.size() == 2) {
        final_indice_aleatorio = 1;
      }
      // Inicializa el generador de números aleatorios
      std::random_device rd;
      std::mt19937 gen(rd());
      // Define el rango de los números aleatorios que quieres generar
      std::uniform_int_distribution<> distrib(inicio_indice_aleatorio,
                                              final_indice_aleatorio);

      TernaTctGrasp candidato_aleatorio{
          lista_candidatos_restringida[distrib(gen)]};
      // Insertamos la tarea en la mejor máquina y en la mejor posición
      // encontrada
      std::vector<int>::iterator it =
          solucion_actual[candidato_aleatorio.maquina_].begin();
      solucion_actual[candidato_aleatorio.maquina_].emplace(
          it + candidato_aleatorio.posicion_ + 1, tarea);
    }
    solucion_actual.setCosteTotal(
        calcularTCTTotalMaquinas(solucion_actual, problema_.getValoresArcos()));
    if (solucion_algoritmo_.getCosteTotal() > solucion_actual.getCosteTotal()) {
      solucion_algoritmo_ = solucion_actual;
    }
  }
  return solucion_algoritmo_;
}

Solucion AlgoritmoGrasp::exploracionVecindario() {
  int menor_numero_tareas{INT_MAX}, mayor_numero_tareas{0}, indice_menor_tareas,
      indice_mayor_tareas;
  // Escogemos la máquina con menor y mayor tareas asignadas
  std::vector<std::vector<int>> matriz_solucion{
      solucion_algoritmo_.getSolucion().first};
  for (int i{0}; i < matriz_solucion.size(); ++i) {
    if (menor_numero_tareas > matriz_solucion[i].size()) {
      menor_numero_tareas = matriz_solucion[i].size();
      indice_menor_tareas = i;
    }
    if (mayor_numero_tareas < matriz_solucion[i].size()) {
      mayor_numero_tareas = matriz_solucion[i].size();
      indice_mayor_tareas = i;
    }
  }
  std::vector<int> maquina_menor_tareas{
      solucion_algoritmo_[indice_menor_tareas]},
      maquina_mayor_tareas{solucion_algoritmo_[indice_mayor_tareas]};
  
  // Se escoge una tarea aleatoria de la máquina pequeña
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribucion(0, maquina_menor_tareas.size() - 1);
  int indice_aleatorio{distribucion(gen)}, tarea_aleatoria{maquina_menor_tareas[indice_aleatorio]};
  // Se escoge una tarea aleatoria de la máquina grande 
  std::uniform_int_distribution<> distribucion2(0, maquina_mayor_tareas.size() - 1);
  int indice_aleatorio_max{distribucion2(gen)}, tarea_aleatoria_max{maquina_mayor_tareas[indice_aleatorio_max]};
  // Se eliminan las dos tareas de las máquinas
  
  /////
  maquina_menor_tareas.erase(maquina_menor_tareas.begin() + indice_aleatorio);
  maquina_mayor_tareas.erase(maquina_mayor_tareas.begin() + indice_aleatorio_max);
  // Calculamos la mejor posición en donde poner la tarea en la máquina pequeña
  int tct_minimo{INT_MAX}, posicion;
  for (int i{0}; i < maquina_menor_tareas.size(); ++i) {
    int tct{calcularTCTOptimo(indice_menor_tareas, i, tarea_aleatoria_max, solucion_algoritmo_, problema_.getValoresArcos())};
    if (tct < tct_minimo) {
      tct_minimo = tct;
      posicion = i;
    }
  }
  maquina_menor_tareas.emplace(maquina_menor_tareas.begin() + posicion + 1, tarea_aleatoria_max);
  // Calculamos la mejor posición en donde poner la tarea en la máquina grande
  tct_minimo = INT_MAX;
  for (int i{0}; i < maquina_mayor_tareas.size(); ++i) {
    int tct{calcularTCTOptimo(indice_mayor_tareas, i, tarea_aleatoria, solucion_algoritmo_, problema_.getValoresArcos())};
    if (tct < tct_minimo) {
      tct_minimo = tct;
      posicion = i;
    }
  }
  maquina_mayor_tareas.emplace(maquina_mayor_tareas.begin() + posicion + 1, tarea_aleatoria);
  // Establecemos la solución vecina y la devolvemos
  matriz_solucion[indice_mayor_tareas] = maquina_mayor_tareas;
  matriz_solucion[indice_menor_tareas] = maquina_menor_tareas;
  Solucion solucion_vecina{{matriz_solucion, calcularTCTTotalMaquinas(matriz_solucion, problema_.getValoresArcos())}};
  return solucion_vecina;
}

Solucion AlgoritmoGrasp::resolver() {
  // 1. Fase constructiva
  // 2. Fase PostProcesamiento
  // 3. Fase actualización (En caso de mejora)
}