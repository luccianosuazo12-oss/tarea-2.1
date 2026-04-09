#ifndef CLIENTE_H
#define CLIENTE_H

#include "Rutina.h"
#include <string>
#include <vector>
using namespace std;

// ============================================================
//  Clase: Cliente
//  Representa a un usuario del sistema de entrenamiento.
//  Composición con Rutina (un cliente puede tener varias rutinas).
//  Lógica de no-repetición: verifica ejercicios de semana anterior.
// ============================================================
class Cliente {
private:
    string id;
    string nombre;
    string apellido;
    string correo;
    int    edad;
    vector<Rutina*> historialRutinas; // Historial de rutinas asignadas

public:
    Cliente(string id, string nombre, string apellido,
            string correo, int edad);
    ~Cliente();

    // -------- Getters --------
    string getId()      const;
    string getNombre()  const;
    string getApellido()const;
    string getCorreo()  const;
    int    getEdad()    const;

    // -------- Setters --------
    void setNombre (const string& n);
    void setApellido(const string& a);
    void setCorreo (const string& c);
    void setEdad   (int e);

    // -------- Rutinas --------
    void agregarRutina(Rutina* r);
    const vector<Rutina*>& getHistorialRutinas() const;

    // Devuelve IDs de ejercicios usados en la semana anterior a 'semanaActual'
    vector<string> getEjerciciosSemanaAnterior(int semanaActual) const;

    void mostrarInfo() const;
};

#endif // CLIENTE_H
