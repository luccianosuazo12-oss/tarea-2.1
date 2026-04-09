#include "../include/Rutina.h"
#include <iostream>
#include <algorithm>
using namespace std;

Rutina::Rutina(string idRutina, string nombreRutina, int semana, string idEntrenador)
    : idRutina(idRutina), nombreRutina(nombreRutina), semana(semana), idEntrenador(idEntrenador) {}

// -------- Getters --------
string Rutina::getIdRutina()      const { return idRutina; }
string Rutina::getNombreRutina()  const { return nombreRutina; }
int    Rutina::getSemana()        const { return semana; }
string Rutina::getIdEntrenador()  const { return idEntrenador; }
const vector<Ejercicio*>& Rutina::getEjercicios() const { return ejercicios; }

// -------- Operaciones --------
void Rutina::agregarEjercicio(Ejercicio* e) {
    ejercicios.push_back(e);
}

int Rutina::calcularTiempoTotal() const {
    int total = 0;
    for (const Ejercicio* e : ejercicios)
        total += e->getDuracionMin();
    return total;
}

bool Rutina::contieneEjercicio(const string& idEjercicio) const {
    for (const Ejercicio* e : ejercicios)
        if (e->getId() == idEjercicio) return true;
    return false;
}

void Rutina::mostrarRutina() const {
    cout << "\n  === Rutina: " << nombreRutina
         << " (ID: " << idRutina << ") | Semana: " << semana
         << " | Entrenador: " << idEntrenador << " ===\n";
    if (ejercicios.empty()) {
        cout << "  (Sin ejercicios asignados)\n";
        return;
    }
    for (const Ejercicio* e : ejercicios)
        e->mostrarInfo();
    cout << "  >> Tiempo total estimado: " << calcularTiempoTotal() << " minutos\n";
}
