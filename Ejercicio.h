#ifndef EJERCICIO_H
#define EJERCICIO_H

#include <string>
using namespace std;

// ============================================================
//  Clase base abstracta: Ejercicio
//  Representa un ejercicio físico genérico del catálogo.
//  Aplica encapsulamiento (atributos privados + getters/setters)
//  y abstracción (método virtual puro mostrarInfo).
// ============================================================
class Ejercicio {
private:
    string id;               // Identificador único
    string nombre;           // Nombre del ejercicio
    string grupoMuscular;    // Grupo muscular trabajado
    int    duracionMin;      // Duración estimada en minutos
    int    intensidad;       // 1 = Baja | 2 = Media | 3 = Alta

public:
    // -------- Constructor / Destructor --------
    Ejercicio(string id, string nombre, string grupoMuscular,
              int duracionMin, int intensidad);
    virtual ~Ejercicio() = default;

    // -------- Getters --------
    string getId()           const;
    string getNombre()       const;
    string getGrupoMuscular()const;
    int    getDuracionMin()  const;
    int    getIntensidad()   const;
    string getIntensidadStr()const;   // "Baja" / "Media" / "Alta"

    // -------- Setters (con validación) --------
    void setNombre(const string& nombre);
    void setGrupoMuscular(const string& grupo);
    void setDuracionMin(int duracion);
    void setIntensidad(int intensidad);

    // -------- Método polimórfico --------
    virtual void mostrarInfo() const = 0;
};

#endif // EJERCICIO_H
