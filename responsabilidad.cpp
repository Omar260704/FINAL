#include "responsabilidad.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;

// Constructor por defecto
Responsabilidad::Responsabilidad() {
    nombre_actividad = "";
    dia = "";
    hr_inicio = "";
    hr_fin = "";
    prioridad = 0;
}

// Constructor con parámetros
Responsabilidad::Responsabilidad(string _nombre_actividad, string _dia, string _hr_inicio, string _hr_fin, int _prioridad) {
    nombre_actividad = _nombre_actividad;
    dia = _dia;
    hr_inicio = _hr_inicio;
    hr_fin = _hr_fin;
    prioridad = _prioridad;
}

// Función para pedir los datos de la tarea
void Responsabilidad::pedir_datos() {
    cout << "Ingrese el nombre de la actividad (una sola palabra): ";
    cin >> nombre_actividad;

    while (true) {
        cout << "Ingrese el día de la actividad (lunes, martes, miercoles, jueves, viernes, sabado, domingo): ";
        cin >> dia;
        for (auto& c : dia) c = tolower(c);

        if (dia == "lunes" || dia == "martes" || dia == "miercoles" || dia == "miércoles" ||
            dia == "jueves" || dia == "viernes" || dia == "sabado" || dia == "sábado" || dia == "domingo") {
            break;
        } else {
            cout << " Día inválido. Por favor escriba un día de la semana correctamente.\n";
        }
    }

    while (true) {
        cout << "Ingrese la hora de inicio (formato 24h, ej: 08:00): ";
        cin >> hr_inicio;
        if (hora_valida(hr_inicio)) break;
        cout << " Hora inválida. Use el formato correcto (HH:MM).\n";
    }

    while (true) {
        cout << "Ingrese la hora de finalización (formato 24h, ej: 10:30): ";
        cin >> hr_fin;
        if (hora_valida(hr_fin) && hora_a_entero(hr_inicio) < hora_a_entero(hr_fin)) break;  // Validación de hora de fin
        cout << " Hora inválida o la hora de finalización es anterior a la hora de inicio. Use el formato correcto (HH:MM).\n";
    }

    while (true) {
        cout << "Ingrese la prioridad (1 = alta, 2 = media, 3 = baja): ";
        cin >> prioridad;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "¡Entrada inválida! Debe ingresar un número entero.\n";
        } else if (prioridad < 1 || prioridad > 3) {
            cout << "¡Prioridad fuera de rango! Ingrese 1 (alta), 2 (media) o 3 (baja).\n";
        } else {
            cin.ignore(1000, '\n');
            break;
        }
    }

    system("clear"); // o "cls" si estás en Windows
}

// Función para mostrar los datos de la tarea
void Responsabilidad::mostrar() const {
    cout << "Nombre de actividad:     " << nombre_actividad << endl;
    cout << "Día de la actividad:     " << dia << endl;
    cout << "Hora de inicio:          " << hr_inicio << endl;
    cout << "Hora de finalización:    " << hr_fin << endl;
    cout << "Prioridad:               " << importancia() << endl;
}

// Función para obtener la importancia de la tarea en formato texto
string Responsabilidad::importancia() const {
    switch (prioridad) {
        case 1: return "alta";
        case 2: return "media";
        case 3: return "baja";
        default: return "desconocido";
    }
}

// Getter para obtener el día
string Responsabilidad::getDia() const { return dia; }

// Getter para obtener la hora de finalización
string Responsabilidad::getHrFin() const { return hr_fin; }

// Getter para obtener la prioridad
int Responsabilidad::getPrioridad() const { return prioridad; }

// Getter para obtener la hora de inicio
string Responsabilidad::getHrInicio() const { return hr_inicio; }

// Getter para obtener el nombre de la actividad
string Responsabilidad::getNombre() const { return nombre_actividad; }

// ================= FUNCIONES AUXILIARES =================

// Función para validar la hora (formato 24h)
bool hora_valida(const string& hora) {
    if (hora.length() != 5 || hora[2] != ':')
        return false;

    string horas = hora.substr(0, 2);
    string minutos = hora.substr(3, 2);

    for (char c : horas + minutos) {
        if (!isdigit(c)) return false;
    }

    int h = stoi(horas);
    int m = stoi(minutos);

    return h >= 0 && h <= 23 && m >= 0 && m <= 59;
}
// Función para registrar logs en un archivo
void registrar_log(const string& mensaje) {
    ofstream archivo("registro.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "[registro] " << mensaje << endl;
        archivo.close();
    }
}

// Función para convertir la hora en formato "HH:MM" a un número entero
int hora_a_entero(const string& hora) {
    string h = hora.substr(0, 2);
    string m = hora.substr(3, 2);
    return stoi(h + m);
}

// Función para mostrar el calendario de tareas usando una tabla hash (unordered_map)
void mostrar_calendario_hash(const unordered_map<string, vector<Responsabilidad>>& tareas_por_dia) {
    if (tareas_por_dia.empty()) {
        cout << "\nNo hay tareas registradas.\n";
        return;
    }

    cout << "\n======= CALENDARIO SEMANAL (tabla hash) =======\n";

    for (const auto& par : tareas_por_dia) {
        string dia = par.first;
        vector<Responsabilidad> tareas = par.second;

        sort(tareas.begin(), tareas.end(), [](const Responsabilidad& a, const Responsabilidad& b) {
            if (a.getPrioridad() != b.getPrioridad())
                return a.getPrioridad() < b.getPrioridad();
            return hora_a_entero(a.getHrFin()) < hora_a_entero(b.getHrFin());
        });

        cout << "\n-- " << dia << " --\n";
        for (const auto& tarea : tareas) {
            tarea.mostrar();
            cout << "----------------------\n";
        }
    }

    cout << "===============================================\n\n";
}
