#include "../include/Ejercicio.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// -------- Constructor --------
Ejercicio::Ejercicio(string id, string nombre, string grupoMuscular,
                     int duracionMin, int intensidad)
    : id(id), nombre(nombre), grupoMuscular(grupoMuscular),
      duracionMin(duracionMin), intensidad(intensidad)
{
    if (duracionMin <= 0)
        throw invalid_argument("La duracion debe ser mayor a 0.");
    if (intensidad < 1 || intensidad > 3)
        throw invalid_argument("La intensidad debe ser 1 (Baja), 2 (Media) o 3 (Alta).");
}

// -------- Getters --------
string Ejercicio::getId()            const { return id; }
string Ejercicio::getNombre()        const { return nombre; }
string Ejercicio::getGrupoMuscular() const { return grupoMuscular; }
int    Ejercicio::getDuracionMin()   const { return duracionMin; }
int    Ejercicio::getIntensidad()    const { return intensidad; }

string Ejercicio::getIntensidadStr() const {
    switch (intensidad) {
        case 1: return "Baja";
        case 2: return "Media";
        case 3: return "Alta";
        default: return "Desconocida";
    }
}

// -------- Setters (con validación) --------
void Ejercicio::setNombre(const string& n) {
    if (n.empty()) throw invalid_argument("El nombre no puede estar vacío.");
    nombre = n;
}

void Ejercicio::setGrupoMuscular(const string& g) {
    if (g.empty()) throw invalid_argument("El grupo muscular no puede estar vacío.");
    grupoMuscular = g;
}

void Ejercicio::setDuracionMin(int d) {
    if (d <= 0) throw invalid_argument("La duración debe ser mayor a 0.");
    duracionMin = d;
}

void Ejercicio::setIntensidad(int i) {
    if (i < 1 || i > 3) throw invalid_argument("Intensidad inválida (1-3).");
    intensidad = i;
}
