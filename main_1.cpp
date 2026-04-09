// ============================================================
//  Sistema de Gestión de Rutinas de Entrenamiento
//  Archivo: main.cpp
//  Punto de entrada del programa. Controla el menú principal.
// ============================================================
#include "include/GestorEjercicios.h"
#include <iostream>
#include <limits>
using namespace std;

// ---- Prototipos ----
void mostrarMenuPrincipal(int semana);
void mostrarMenuEjercicios();
void limpiarEntrada();

int main() {
    cout << "=========================================\n";
    cout << "  SISTEMA DE RUTINAS DE ENTRENAMIENTO   \n";
    cout << "=========================================\n\n";

    GestorEjercicios gestor;

    int opcion = 0;
    do {
        mostrarMenuPrincipal(gestor.getSemanaActual());
        cout << "Opcion: "; cin >> opcion; limpiarEntrada();

        switch (opcion) {

        // --------- CRUD EJERCICIOS ---------
        case 1: {
            int sub = 0;
            mostrarMenuEjercicios();
            cout << "Opcion: "; cin >> sub; limpiarEntrada();
            switch (sub) {
                case 1: gestor.crearEjercicio();       break;
                case 2: gestor.actualizarEjercicio();  break;
                case 3: gestor.eliminarEjercicio();    break;
                case 4: gestor.consultarEjercicio();   break;
                case 5: gestor.listarTodosEjercicios();break;
                case 6: gestor.buscarPorIntensidad();  break;
                default: cout << "Opcion invalida.\n"; break;
            }
            break;
        }

        // --------- CLIENTES ---------
        case 2:
            gestor.crearCliente();
            break;

        case 3:
            gestor.listarClientes();
            break;

        // --------- ENTRENADORES ---------
        case 4:
            gestor.crearEntrenador();
            break;

        case 5:
            gestor.listarEntrenadores();
            break;

        case 6:
            gestor.asignarClienteAEntrenador();
            break;

        // --------- RUTINAS ---------
        case 7:
            gestor.generarRutina();
            break;

        // --------- CONFIGURACIÓN ---------
        case 8:
            gestor.configurarSemana();
            break;

        case 0:
            cout << "\nSaliendo del sistema. Hasta luego!\n";
            break;

        default:
            cout << "Opcion invalida. Intente de nuevo.\n";
            break;
        }

    } while (opcion != 0);

    return 0;
}

void mostrarMenuPrincipal(int semana) {
    cout << "\n========================================\n";
    cout << "  MENU PRINCIPAL  |  Semana: " << semana << "\n";
    cout << "========================================\n";
    cout << "  1. Gestion de Ejercicios (CRUD)\n";
    cout << "  2. Registrar nuevo Cliente\n";
    cout << "  3. Listar Clientes\n";
    cout << "  4. Registrar nuevo Entrenador\n";
    cout << "  5. Listar Entrenadores\n";
    cout << "  6. Asignar Cliente a Entrenador\n";
    cout << "  7. Generar Rutina para Cliente\n";
    cout << "  8. Configurar Semana actual\n";
    cout << "  0. Salir\n";
    cout << "----------------------------------------\n";
}

void mostrarMenuEjercicios() {
    cout << "\n  --- GESTION DE EJERCICIOS ---\n";
    cout << "  1. Crear ejercicio\n";
    cout << "  2. Actualizar ejercicio\n";
    cout << "  3. Eliminar ejercicio\n";
    cout << "  4. Consultar ejercicio por ID\n";
    cout << "  5. Listar todos los ejercicios\n";
    cout << "  6. Buscar por intensidad\n";
}

void limpiarEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
