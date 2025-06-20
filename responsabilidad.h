#ifndef RESPONSABILIDAD_H
#define RESPONSABILIDAD_H

#include <string>
#include <vector>
#include <unordered_map>  // Incluir esta librería para usar unordered_map

using namespace std;

class Responsabilidad {
private:
    string nombre_actividad;
    string dia;
    string hr_inicio;
    string hr_fin;
    int prioridad;

public:
    Responsabilidad();
    Responsabilidad(string nombre_actividad, string dia, string hr_inicio, string hr_fin, int prioridad);
    void pedir_datos();
    void mostrar() const;
    string importancia() const;

    string getDia() const;
    string getHrFin() const;
    int getPrioridad() const;
    string getHrInicio() const;
    string getNombre() const;
};

// Funciones auxiliares que no son parte de la clase
bool hora_valida(const string& hora);
void registrar_log(const string& mensaje);
int hora_a_entero(const string& hora);
void mostrar_calendario_hash(const unordered_map<string, vector<Responsabilidad>>& tareas_por_dia);

#endif // RESPONSABILIDAD_H
