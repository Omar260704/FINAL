#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include "responsabilidad.h"
using namespace std;

int main() {
    vector<Responsabilidad> lista_tareas;
    unordered_map<string, vector<Responsabilidad>> tareas_por_dia;
    int opcion;

    do {
        cout << "========== MENU ==========\n";
        cout << "1. Agregar nueva tarea\n";
        cout << "2. Mostrar todas las tareas ordenadas por día\n";
        cout << "3. Mostrar tareas registradas\n";
        cout << "4. Eliminar una tarea\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";

        // Validación de la opción seleccionada (1-5)
        while (true) {
            cin >> opcion;

            // Validar que la opción sea un número dentro del rango 1-5
            if (cin.fail()) {
                cin.clear(); // Limpia el estado de error
                cin.ignore(1000, '\n'); // Ignora la entrada incorrecta
                cout << "¡Entrada inválida! Por favor ingrese un número entre 1 y 5: ";
            } else if (opcion < 1 || opcion > 5) {
                cout << "Opción fuera de rango. Por favor ingrese un número entre 1 y 5: ";
            } else {
                break; // Si la opción es válida, sale del bucle
            }
        }

        switch (opcion) {
            case 1: {
                Responsabilidad nueva;
                nueva.pedir_datos();
                lista_tareas.push_back(nueva);
                tareas_por_dia[nueva.getDia()].push_back(nueva);
                registrar_log("Se agregó la tarea: " + nueva.getNombre());
                break;
            }
            case 2: {
                if (lista_tareas.empty()) {
                    cout << "\nNo hay tareas registradas.\n";
                    break;
                }

                vector<string> orden_dias = {"lunes", "martes", "miercoles", "jueves", "viernes", "sabado", "domingo"};
                for (const auto& dia : orden_dias) {
                    vector<Responsabilidad> tareas_dia;
                    for (const auto& t : lista_tareas) {
                        string d = t.getDia();
                        transform(d.begin(), d.end(), d.begin(), ::tolower);
                        if (d == dia) {
                            tareas_dia.push_back(t);
                        }
                    }

                    sort(tareas_dia.begin(), tareas_dia.end(), [](const Responsabilidad& a, const Responsabilidad& b) {
                        if (a.getPrioridad() != b.getPrioridad())
                            return a.getPrioridad() < b.getPrioridad();
                        return hora_a_entero(a.getHrFin()) < hora_a_entero(b.getHrFin());
                    });

                    if (!tareas_dia.empty()) {
                        cout << "\n-- " << dia << " --\n";
                        for (const auto& tarea : tareas_dia) {
                            tarea.mostrar();
                            cout << "----------------------\n";
                        }
                    }
                }

                break;
            }
            case 3:
                mostrar_calendario_hash(tareas_por_dia);
                break;
            case 4: {
                if (lista_tareas.empty()) {
                    cout << "\nNo hay tareas para eliminar.\n";
                    break;
                }

                cout << "\n--- Lista de tareas ---\n";
                for (size_t i = 0; i < lista_tareas.size(); ++i) {
                    cout << i + 1 << ". " << lista_tareas[i].getNombre()
                         << " - " << lista_tareas[i].getDia()
                         << " [" << lista_tareas[i].importancia() << "]\n";
                }

                int eliminar;
                cout << "Ingrese el número de la tarea que desea eliminar: ";
                cin >> eliminar;

                if (eliminar < 1 || eliminar > lista_tareas.size()) {
                    cout << "Número inválido. No se eliminó ninguna tarea.\n";
                } else {
                    string dia_tarea = lista_tareas[eliminar - 1].getDia();
                    string nombre = lista_tareas[eliminar - 1].getNombre();
                    auto& vec = tareas_por_dia[dia_tarea];
                    vec.erase(remove_if(vec.begin(), vec.end(), [&](const Responsabilidad& r) {
                        return r.getNombre() == nombre;
                    }), vec.end());
                    lista_tareas.erase(lista_tareas.begin() + (eliminar - 1));
                    registrar_log("Se eliminó la tarea: " + nombre + " - " + dia_tarea);
                    cout << "Tarea eliminada correctamente.\n";
                }

                break;
            }
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }

    } while (opcion != 5);

    return 0;
}
