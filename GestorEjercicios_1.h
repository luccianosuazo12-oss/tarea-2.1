#ifndef GESTOR_EJERCICIOS_H
#define GESTOR_EJERCICIOS_H

#include "Ejercicio.h"
#include "EjercicioCardio.h"
#include "EjercicioFuerza.h"
#include "Rutina.h"
#include "Cliente.h"
#include "Entrenador.h"
#include <vector>
#include <string>
using namespace std;

// ============================================================
//  Clase: GestorEjercicios
//  Fachada principal del sistema.
//  Gestiona el catálogo de ejercicios, clientes y generación
//  de rutinas. Aplica el principio de responsabilidad única.
// ============================================================
class GestorEjercicios {
private:
    vector<Ejercicio*> catalogo;   // Todos los ejercicios disponibles
    vector<Cliente*>   clientes;   // Clientes registrados
    vector<Entrenador*> entrenadores; // Entrenadores registrados
    int semanaActual;              // Semana vigente del sistema

    // ---- Helpers privados ----
    Ejercicio* buscarPorId(const string& id) const;
    bool       idExiste   (const string& id) const;
    string     generarIdEjercicio() const;
    string     generarIdRutina()    const;

public:
    GestorEjercicios();
    ~GestorEjercicios();

    // ==================== CRUD Ejercicios ====================
    void crearEjercicio();
    void actualizarEjercicio();
    void eliminarEjercicio();
    void consultarEjercicio()       const;
    void listarTodosEjercicios()    const;
    void buscarPorIntensidad()      const;

    // ==================== Clientes ====================
    void crearCliente();
    void listarClientes()           const;
    Cliente* buscarClientePorId(const string& id) const;

    // ==================== Entrenadores ====================
    void crearEntrenador();
    void listarEntrenadores()       const;
    void asignarClienteAEntrenador();
    Entrenador* buscarEntrenadorPorId(const string& id) const;

    // ==================== Rutinas ====================
    void generarRutina();

    // ==================== Semana ====================
    void configurarSemana();
    int  getSemanaActual() const;

    // ==================== Utilidades ====================
    void cargarDatosDemostracion(); // Precarga datos para pruebas
};

#endif // GESTOR_EJERCICIOS_H
