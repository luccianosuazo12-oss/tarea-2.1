#ifndef RUTINA_H
#define RUTINA_H

#include "Ejercicio.h"
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  Clase: Rutina
//  Composición con Ejercicio (una rutina CONTIENE ejercicios).
//  Calcula tiempo total y verifica repetición entre semanas.
// ============================================================
class Rutina {
private:
    string idRutina;
    string nombreRutina;
    int    semana;                 // Número de semana asignada
    string idEntrenador;           // ID del entrenador que creó la rutina
    vector<Ejercicio*> ejercicios; // Punteros polimórficos

public:
    Rutina(string idRutina, string nombreRutina, int semana, string idEntrenador);
    ~Rutina() = default;           // No destruye los ejercicios (son del catálogo)

    // -------- Getters --------
    string getIdRutina()      const;
    string getNombreRutina()  const;
    int    getSemana()        const;
    string getIdEntrenador()  const;
    const vector<Ejercicio*>& getEjercicios() const;

    // -------- Operaciones --------
    void agregarEjercicio(Ejercicio* e);
    int  calcularTiempoTotal() const;  // Suma duraciones en minutos
    bool contieneEjercicio(const string& idEjercicio) const;

    void mostrarRutina() const;
};

#endif // RUTINA_H
