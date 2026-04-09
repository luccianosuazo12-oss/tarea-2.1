#include "../include/Entrenador.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// -------- Constructor --------
Entrenador::Entrenador(string id, string nombre, string apellido, string especialidad)
    : id(id), nombre(nombre), apellido(apellido), especialidad(especialidad) {}

// -------- Getters --------
string Entrenador::getId()           const { return id; }
string Entrenador::getNombre()       const { return nombre; }
string Entrenador::getApellido()     const { return apellido; }
string Entrenador::getEspecialidad() const { return especialidad; }
const vector<Cliente*>& Entrenador::getClientesAsignados() const { return clientesAsignados; }

// -------- Setters --------
void Entrenador::setNombre(const string& n) {
    if (n.empty()) throw invalid_argument("El nombre no puede estar vacío.");
    nombre = n;
}
void Entrenador::setApellido(const string& a) {
    if (a.empty()) throw invalid_argument("El apellido no puede estar vacío.");
    apellido = a;
}
void Entrenador::setEspecialidad(const string& e) {
    if (e.empty()) throw invalid_argument("La especialidad no puede estar vacía.");
    especialidad = e;
}

// -------- Gestión de clientes --------
void Entrenador::asignarCliente(Cliente* c) {
    if (!c) throw invalid_argument("Cliente inválido.");
    if (tieneCliente(c->getId())) {
        cout << "  El cliente ya está asignado a este entrenador.\n";
        return;
    }
    clientesAsignados.push_back(c);
}

bool Entrenador::tieneCliente(const string& idCliente) const {
    for (const Cliente* c : clientesAsignados)
        if (c->getId() == idCliente) return true;
    return false;
}

Cliente* Entrenador::buscarCliente(const string& idCliente) const {
    for (Cliente* c : clientesAsignados)
        if (c->getId() == idCliente) return c;
    return nullptr;
}

// -------- Info --------
void Entrenador::mostrarInfo() const {
    cout << "  Entrenador ID: " << id
         << " | Nombre: "       << nombre << " " << apellido
         << " | Especialidad: " << especialidad
         << " | Clientes: "     << clientesAsignados.size()
         << endl;
    if (!clientesAsignados.empty()) {
        cout << "    Clientes asignados:\n";
        for (const Cliente* c : clientesAsignados)
            cout << "      -> [" << c->getId() << "] "
                 << c->getNombre() << " " << c->getApellido() << "\n";
    }
}
