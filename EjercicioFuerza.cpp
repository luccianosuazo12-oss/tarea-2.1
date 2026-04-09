#include "../include/EjercicioFuerza.h"
#include <iostream>
#include <stdexcept>
using namespace std;

EjercicioFuerza::EjercicioFuerza(string id, string nombre, string grupoMuscular,
                                 int duracionMin, int intensidad, int series, int repeticiones)
    : Ejercicio(id, nombre, grupoMuscular, duracionMin, intensidad),
      series(series), repeticiones(repeticiones) {}

int  EjercicioFuerza::getSeries()       const { return series; }
int  EjercicioFuerza::getRepeticiones() const { return repeticiones; }

void EjercicioFuerza::setSeries(int s) {
    if (s <= 0) throw invalid_argument("Las series deben ser mayores a 0.");
    series = s;
}
void EjercicioFuerza::setRepeticiones(int r) {
    if (r <= 0) throw invalid_argument("Las repeticiones deben ser mayores a 0.");
    repeticiones = r;
}

void EjercicioFuerza::mostrarInfo() const {
    cout << "  [FUERZA] ID: " << getId()
         << " | Nombre: "     << getNombre()
         << " | Musculo: "    << getGrupoMuscular()
         << " | Duracion: "   << getDuracionMin() << " min"
         << " | Intensidad: " << getIntensidadStr()
         << " | Series: "     << series
         << " | Reps: "       << repeticiones
         << endl;
}
