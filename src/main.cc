#include <iostream>
#include <sstream>
#include <chrono>

#include "../include/Algoritmo.h"
#include "../include/AlgoritmoVoraz.h"
#include "../include/Problema.h"
#include "../include/Solucion.h"
#include "../include/AlgoritmoGrasp.h"
#include "../include/AlgoritmoGvns.h"

int main(/*int argc, char* argv[]*/) { 
  /*
  if (argc != 2) {
    std::cerr << "Error: número de argumentos incorrecto" << std::endl;
    ayuda();
    return 1;
  }
  */
  std::vector<std::string> nombres_ficheros{{"PMSP/I40j_2m_S1_1.txt", "PMSP/I40j_4m_S1_1.txt", "PMSP/I40j_6m_S1_1.txt", "PMSP/I40j_8m_S1_1.txt", "PMSP/Inst50j/I50j_2m_S1_1.txt", "PMSP/Inst60j/I60j_2m_S1_1.txt", "PMSP/Inst70j/I70j_2m_S1_1.txt"}};
  //std::string nombre_fichero{argv[1]};
  /*
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
  std::cout << "\t\tAlgoritmo GRASP con Intercambio entre tareas" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 1, 300};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolver();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tAlgoritmo GRASP con Intercambio en la misma máquina" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 2, 300};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolver();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tAlgoritmo GRASP con Reinserción entre máquinas" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 3, 300};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolver();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tAlgoritmo GRASP con Reinserción en la misma máquina" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 3, 300};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.resolver();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  */
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\tFase constructiva GRASP" << std::endl;
  printf("%-25s %-5s %-13s %-11s %-11s\n", "Problema", "n", "Ejecución", "TCT", "CPU");
  std::cout << "------------------------------------------------------------------------" << std::endl;
  for (int i{0}; i < nombres_ficheros.size(); ++i) {
    AlgoritmoGrasp grasp{nombres_ficheros[i], 3, 300};
    auto start = std::chrono::high_resolution_clock::now();
    grasp.setSolucion(grasp.faseConstructiva());
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    printf("%-25s %-5d %-13d %-10d %-10ldµs", nombres_ficheros[i].c_str(), grasp.getProblema().getNumeroTareas(), (i + 1), grasp.getTCTTotal(), duration);
    std::cout << std::endl;
  }
  //////////////////////////////////////////////////////////
  std::cout << "------------------------------------------------------------------------" << std::endl;
  std::cout << "\t\t\t\tGVNS MultiArranque" << std::endl;
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
  std::cout << "\t\t\t\tGVNS" << std::endl;
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