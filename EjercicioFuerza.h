#ifndef EJERCICIO_FUERZA_H
#define EJERCICIO_FUERZA_H

#include "Ejercicio.h"

// ============================================================
//  Clase derivada: EjercicioFuerza
//  Hereda de Ejercicio. Agrega: series y repeticiones.
// ============================================================
class EjercicioFuerza : public Ejercicio {
private:
    int series;
    int repeticiones;

public:
    EjercicioFuerza(string id, string nombre, string grupoMuscular,
                    int duracionMin, int intensidad, int series, int repeticiones);

    int getSeries()      const;
    int getRepeticiones()const;
    void setSeries(int s);
    void setRepeticiones(int r);

    void mostrarInfo() const override;
};

#endif // EJERCICIO_FUERZA_H
