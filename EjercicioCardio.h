#ifndef EJERCICIO_CARDIO_H
#define EJERCICIO_CARDIO_H

#include "Ejercicio.h"

// ============================================================
//  Clase derivada: EjercicioCardio
//  Hereda de Ejercicio. Agrega atributo propio: frecuenciaCardiaca.
//  Ilustra herencia + polimorfismo (override de mostrarInfo).
// ============================================================
class EjercicioCardio : public Ejercicio {
private:
    int frecuenciaCardiacaObj; // Frecuencia cardíaca objetivo (ppm)

public:
    EjercicioCardio(string id, string nombre, string grupoMuscular,
                    int duracionMin, int intensidad, int frecuenciaCardiacaObj);

    int getFrecuenciaCardiaca() const;
    void setFrecuenciaCardiaca(int ppm);

    void mostrarInfo() const override;
};

#endif // EJERCICIO_CARDIO_H
