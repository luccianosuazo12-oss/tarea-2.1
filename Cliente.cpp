#include "../include/Cliente.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Cliente::Cliente(string id, string nombre, string apellido,
                 string correo, int edad)
    : id(id), nombre(nombre), apellido(apellido), correo(correo), edad(edad) {}

// El destructor libera las rutinas creadas dinámicamente para este cliente
Cliente::~Cliente() {
    for (Rutina* r : historialRutinas) delete r;
}

// -------- Getters --------
string Cliente::getId()       const { return id; }
string Cliente::getNombre()   const { return nombre; }
string Cliente::getApellido() const { return apellido; }
string Cliente::getCorreo()   const { return correo; }
int    Cliente::getEdad()     const { return edad; }

// -------- Setters --------
void Cliente::setNombre (const string& n) {
    if (n.empty()) throw invalid_argument("El nombre no puede estar vacío.");
    nombre = n;
}
void Cliente::setApellido(const string& a) {
    if (a.empty()) throw invalid_argument("El apellido no puede estar vacío.");
    apellido = a;
}
void Cliente::setCorreo (const string& c) { correo = c; }
void Cliente::setEdad   (int e) {
    if (e < 0 || e > 120) throw invalid_argument("Edad inválida.");
    edad = e;
}

// -------- Rutinas --------
void Cliente::agregarRutina(Rutina* r) {
    historialRutinas.push_back(r);
}

const vector<Rutina*>& Cliente::getHistorialRutinas() const {
    return historialRutinas;
}

// Retorna los IDs de ejercicios usados en la semana (semanaActual - 1)
vector<string> Cliente::getEjerciciosSemanaAnterior(int semanaActual) const {
    vector<string> ids;
    int semanaAnterior = semanaActual - 1;
    for (const Rutina* r : historialRutinas) {
        if (r->getSemana() == semanaAnterior) {
            for (const Ejercicio* e : r->getEjercicios())
                ids.push_back(e->getId());
        }
    }
    return ids;
}

void Cliente::mostrarInfo() const {
    cout << "  Cliente ID: " << id
         << " | Nombre: "   << nombre << " " << apellido
         << " | Correo: "   << correo
         << " | Edad: "     << edad
         << " | Rutinas registradas: " << historialRutinas.size()
         << endl;
}
