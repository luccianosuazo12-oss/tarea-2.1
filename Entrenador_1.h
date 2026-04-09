#ifndef ENTRENADOR_H
#define ENTRENADOR_H

#include "Cliente.h"
#include <string>
#include <vector>
using namespace std;

// ============================================================
//  Clase: Entrenador
//  Representa al profesional que crea rutinas para sus clientes.
//  Asociación con Cliente (un entrenador TIENE varios clientes).
//  La Rutina queda registrada con el ID del entrenador que la creó.
// ============================================================
class Entrenador {
private:
    string id;                      // Identificador único (ej: "ENT001")
    string nombre;                  // Nombre del entrenador
    string apellido;                // Apellido del entrenador
    string especialidad;            // Ej: "Musculación", "Cardio", "Funcional"
    vector<Cliente*> clientesAsignados; // Clientes bajo su cargo

public:
    // -------- Constructor / Destructor --------
    Entrenador(string id, string nombre, string apellido, string especialidad);
    ~Entrenador() = default;        // No destruye clientes (son del gestor)

    // -------- Getters --------
    string getId()          const;
    string getNombre()      const;
    string getApellido()    const;
    string getEspecialidad()const;
    const vector<Cliente*>& getClientesAsignados() const;

    // -------- Setters --------
    void setNombre     (const string& n);
    void setApellido   (const string& a);
    void setEspecialidad(const string& e);

    // -------- Gestión de clientes --------
    void    asignarCliente(Cliente* c);
    bool    tieneCliente  (const string& idCliente) const;
    Cliente* buscarCliente(const string& idCliente) const;

    // -------- Info --------
    void mostrarInfo() const;
};

#endif // ENTRENADOR_H
