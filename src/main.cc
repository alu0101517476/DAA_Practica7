#include <iostream>
#include <sstream>
#include <chrono>

#include "../include/Algoritmo.h"
#include "../include/AlgoritmoVoraz.h"
#include "../include/Problema.h"
#include "../include/Solucion.h"
#include "../include/AlgoritmoGrasp.h"
#include "../include/AlgoritmoGvns.h"

int main() { 
  std::vector<std::string> nombres_ficheros{{"PMSP/I40j_2m_S1_1.txt", "PMSP/I40j_4m_S1_1.txt", "PMSP/I40j_6m_S1_1.txt", "PMSP/I40j_8m_S1_1.txt", "PMSP/Inst50j/I50j_2m_S1_1.txt", "PMSP/Inst60j/I60j_2m_S1_1.txt", "PMSP/Inst70j/I70j_2m_S1_1.txt"}};
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tAlgoritmo Voraz" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;

  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoVoraz voraz{nombres_ficheros[i]};
    auto start = std::chrono::high_resolution_clock::now();
    voraz.resolver();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), voraz.getProblema().getNumeroTareas(), (i + 1), voraz.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  ////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tAlgoritmo GRASP MULTIARRANQUE con Intercambio de tareas entre máquinas" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 1, 1000};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolverMultiarranque();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tAlgoritmo GRASP MULTIARRANQUE con Intercambio de tareas en la misma máquina" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 2, 1000};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolverMultiarranque();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tAlgoritmo GRASP MULTIARRANQUE con Reinserción de tareas entre máquinas" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 3, 1000};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolverMultiarranque();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tAlgoritmo GRASP MULTIARRANQUE con Reinserción de tareas en la misma máquina" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 3, 1000};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolverMultiarranque();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tFase constructiva GRASP" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 3, 1000};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.setSolucion(grasp.faseConstructiva());
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tGRASP con Reinserción de tareas entre máquinas" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 1};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolver();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tGRASP con Intercambio de tareas en la misma máquina" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 2};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolver();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tGRASP con Reinserción de tareas en la misma máquina" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 3};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolver();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tGRASP con Intercambio de tareas entre máquinas" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 4};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolver();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\t\t\tGVNS" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGvns gvns{nombres_ficheros[i]};
    auto start = std::chrono::high_resolution_clock::now();
    gvns.resolverMultiArranque();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), gvns.getProblema().getNumeroTareas(), (i + 1), gvns.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\t\t\tVNS" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGvns gvns{nombres_ficheros[i]};
    auto start = std::chrono::high_resolution_clock::now();
    gvns.resolver();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), gvns.getProblema().getNumeroTareas(), (i + 1), gvns.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  return 0; 
}