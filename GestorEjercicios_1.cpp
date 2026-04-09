#include "../include/GestorEjercicios.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdexcept>
using namespace std;

// ============================================================
//  Constructor / Destructor
// ============================================================
GestorEjercicios::GestorEjercicios() : semanaActual(1) {
    cargarDatosDemostracion();
}

GestorEjercicios::~GestorEjercicios() {
    for (Ejercicio*   e : catalogo)    delete e;
    for (Cliente*     c : clientes)    delete c;
    for (Entrenador*  e : entrenadores) delete e;
}

// ============================================================
//  Helpers privados
// ============================================================
Ejercicio* GestorEjercicios::buscarPorId(const string& id) const {
    for (Ejercicio* e : catalogo)
        if (e->getId() == id) return e;
    return nullptr;
}

bool GestorEjercicios::idExiste(const string& id) const {
    return buscarPorId(id) != nullptr;
}

string GestorEjercicios::generarIdEjercicio() const {
    return "EJ" + to_string(catalogo.size() + 1);
}

string GestorEjercicios::generarIdRutina() const {
    int total = 0;
    for (const Cliente* c : clientes)
        total += (int)c->getHistorialRutinas().size();
    return "RUT" + to_string(total + 1);
}

// ============================================================
//  CRUD Ejercicios
// ============================================================
void GestorEjercicios::crearEjercicio() {
    cout << "\n--- CREAR EJERCICIO ---\n";
    string nombre, grupo;
    int    tipo, duracion, intensidad;

    cout << "Tipo (1=Cardio, 2=Fuerza): "; cin >> tipo; cin.ignore();
    if (tipo != 1 && tipo != 2) { cout << "Tipo invalido.\n"; return; }

    cout << "Nombre del ejercicio: ";          getline(cin, nombre);
    cout << "Grupo muscular trabajado: ";      getline(cin, grupo);
    cout << "Duracion estimada (minutos): ";   cin >> duracion;
    cout << "Intensidad (1=Baja, 2=Media, 3=Alta): "; cin >> intensidad;

    try {
        string newId = generarIdEjercicio();
        if (tipo == 1) {
            int fc;
            cout << "Frecuencia cardiaca objetivo (ppm): "; cin >> fc;
            catalogo.push_back(new EjercicioCardio(newId, nombre, grupo, duracion, intensidad, fc));
        } else {
            int s, r;
            cout << "Numero de series: ";      cin >> s;
            cout << "Repeticiones por serie: ";cin >> r;
            catalogo.push_back(new EjercicioFuerza(newId, nombre, grupo, duracion, intensidad, s, r));
        }
        cout << "Ejercicio creado con ID: " << newId << endl;
    } catch (const exception& ex) {
        cout << "Error al crear ejercicio: " << ex.what() << endl;
    }
    cin.ignore();
}

void GestorEjercicios::actualizarEjercicio() {
    cout << "\n--- ACTUALIZAR EJERCICIO ---\n";
    listarTodosEjercicios();
    cout << "Ingrese ID del ejercicio a actualizar: ";
    string id; cin >> id; cin.ignore();

    Ejercicio* e = buscarPorId(id);
    if (!e) { cout << "Ejercicio no encontrado.\n"; return; }

    cout << "Nuevo nombre (Enter para mantener): ";
    string tmp; getline(cin, tmp);
    if (!tmp.empty()) e->setNombre(tmp);

    cout << "Nuevo grupo muscular (Enter para mantener): ";
    getline(cin, tmp);
    if (!tmp.empty()) e->setGrupoMuscular(tmp);

    cout << "Nueva duracion en min (0 para mantener): ";
    int val; cin >> val;
    if (val > 0) e->setDuracionMin(val);

    cout << "Nueva intensidad 1-3 (0 para mantener): ";
    cin >> val;
    if (val > 0) e->setIntensidad(val);

    cout << "Ejercicio actualizado correctamente.\n";
    cin.ignore();
}

void GestorEjercicios::eliminarEjercicio() {
    cout << "\n--- ELIMINAR EJERCICIO ---\n";
    listarTodosEjercicios();
    cout << "Ingrese ID del ejercicio a eliminar: ";
    string id; cin >> id; cin.ignore();

    for (auto it = catalogo.begin(); it != catalogo.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            catalogo.erase(it);
            cout << "Ejercicio eliminado.\n";
            return;
        }
    }
    cout << "Ejercicio no encontrado.\n";
}

void GestorEjercicios::consultarEjercicio() const {
    cout << "\n--- CONSULTAR EJERCICIO ---\n";
    cout << "Ingrese ID del ejercicio: ";
    string id; cin >> id; cin.ignore();

    Ejercicio* e = buscarPorId(id);
    if (!e) { cout << "Ejercicio no encontrado.\n"; return; }
    e->mostrarInfo();
}

void GestorEjercicios::listarTodosEjercicios() const {
    cout << "\n--- CATALOGO DE EJERCICIOS (" << catalogo.size() << ") ---\n";
    if (catalogo.empty()) { cout << "  (No hay ejercicios registrados)\n"; return; }
    for (const Ejercicio* e : catalogo) e->mostrarInfo();
}

void GestorEjercicios::buscarPorIntensidad() const {
    cout << "\n--- BUSCAR POR INTENSIDAD ---\n";
    cout << "Intensidad buscada (1=Baja, 2=Media, 3=Alta): ";
    int nivel; cin >> nivel; cin.ignore();

    bool encontrado = false;
    for (const Ejercicio* e : catalogo) {
        if (e->getIntensidad() == nivel) {
            e->mostrarInfo();
            encontrado = true;
        }
    }
    if (!encontrado) cout << "  No se encontraron ejercicios con esa intensidad.\n";
}

// ============================================================
//  Clientes
// ============================================================
void GestorEjercicios::crearCliente() {
    cout << "\n--- REGISTRAR CLIENTE ---\n";
    string id, nombre, apellido, correo; int edad;
    cout << "ID cliente: ";    cin >> id; cin.ignore();
    if (buscarClientePorId(id)) { cout << "ID ya existe.\n"; return; }
    cout << "Nombre: ";        getline(cin, nombre);
    cout << "Apellido: ";      getline(cin, apellido);
    cout << "Correo: ";        getline(cin, correo);
    cout << "Edad: ";          cin >> edad; cin.ignore();
    try {
        clientes.push_back(new Cliente(id, nombre, apellido, correo, edad));
        cout << "Cliente registrado.\n";
    } catch (const exception& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void GestorEjercicios::listarClientes() const {
    cout << "\n--- CLIENTES REGISTRADOS (" << clientes.size() << ") ---\n";
    if (clientes.empty()) { cout << "  (No hay clientes)\n"; return; }
    for (const Cliente* c : clientes) c->mostrarInfo();
}

Cliente* GestorEjercicios::buscarClientePorId(const string& id) const {
    for (Cliente* c : clientes)
        if (c->getId() == id) return c;
    return nullptr;
}

// ============================================================
//  Generación de Rutina
// ============================================================
void GestorEjercicios::generarRutina() {
    cout << "\n--- GENERAR RUTINA ---\n";

    // Seleccionar entrenador
    listarEntrenadores();
    cout << "ID del entrenador que crea la rutina: ";
    string idEntrenador; cin >> idEntrenador; cin.ignore();
    Entrenador* entrenador = buscarEntrenadorPorId(idEntrenador);
    if (!entrenador) { cout << "Entrenador no encontrado.\n"; return; }

    // Seleccionar cliente (solo entre los asignados al entrenador)
    if (entrenador->getClientesAsignados().empty()) {
        cout << "Este entrenador no tiene clientes asignados.\n";
        return;
    }
    cout << "\nClientes de " << entrenador->getNombre() << ":\n";
    for (const Cliente* c : entrenador->getClientesAsignados())
        c->mostrarInfo();

    cout << "ID del cliente: "; string idCliente; cin >> idCliente; cin.ignore();
    Cliente* cliente = entrenador->buscarCliente(idCliente);
    if (!cliente) { cout << "Cliente no encontrado o no asignado a este entrenador.\n"; return; }

    cout << "Nombre de la rutina: "; string nomRutina; getline(cin, nomRutina);
    cout << "Cantidad de ejercicios a incluir: "; int cantidad; cin >> cantidad; cin.ignore();
    cout << "Intensidad deseada (1=Baja, 2=Media, 3=Alta, 0=Cualquiera): ";
    int intensidadFiltro; cin >> intensidadFiltro; cin.ignore();

    // Obtener IDs prohibidos (semana anterior)
    vector<string> prohibidos = cliente->getEjerciciosSemanaAnterior(semanaActual);

    // Filtrar candidatos del catálogo
    vector<Ejercicio*> candidatos;
    for (Ejercicio* e : catalogo) {
        if (intensidadFiltro != 0 && e->getIntensidad() != intensidadFiltro) continue;
        bool repetido = false;
        for (const string& pid : prohibidos)
            if (e->getId() == pid) { repetido = true; break; }
        if (!repetido) candidatos.push_back(e);
    }

    if ((int)candidatos.size() < cantidad) {
        cout << "No hay suficientes ejercicios disponibles sin repetir semana anterior.\n";
        cout << "Disponibles: " << candidatos.size() << " | Solicitados: " << cantidad << "\n";
        if (candidatos.empty()) return;
        cout << "Se generara la rutina con los " << candidatos.size() << " disponibles.\n";
        cantidad = (int)candidatos.size();
    }

    // Crear la rutina con el ID del entrenador registrado
    Rutina* rutina = new Rutina(generarIdRutina(), nomRutina, semanaActual, entrenador->getId());
    for (int i = 0; i < cantidad; i++)
        rutina->agregarEjercicio(candidatos[i]);

    cliente->agregarRutina(rutina);
    rutina->mostrarRutina();

    cout << "  (Rutina creada por: " << entrenador->getNombre()
         << " " << entrenador->getApellido() << " | Especialidad: "
         << entrenador->getEspecialidad() << ")\n";

    if (!prohibidos.empty())
        cout << "  (Se excluyeron " << prohibidos.size()
             << " ejercicios de la semana anterior para evitar repeticion)\n";
}

// ============================================================
//  Semana
// ============================================================
void GestorEjercicios::configurarSemana() {
    cout << "Semana actual (" << semanaActual << "). Nueva semana: ";
    int s; cin >> s; cin.ignore();
    if (s < 1) { cout << "Valor invalido.\n"; return; }
    semanaActual = s;
    cout << "Semana configurada a: " << semanaActual << endl;
}

int GestorEjercicios::getSemanaActual() const { return semanaActual; }

// ============================================================
//  Entrenadores
// ============================================================
void GestorEjercicios::crearEntrenador() {
    cout << "\n--- REGISTRAR ENTRENADOR ---\n";
    string id, nombre, apellido, especialidad;
    cout << "ID entrenador (ej: ENT003): "; cin >> id; cin.ignore();
    if (buscarEntrenadorPorId(id)) { cout << "ID ya existe.\n"; return; }
    cout << "Nombre: ";       getline(cin, nombre);
    cout << "Apellido: ";     getline(cin, apellido);
    cout << "Especialidad (ej: Musculacion, Cardio, Funcional): ";
    getline(cin, especialidad);
    try {
        entrenadores.push_back(new Entrenador(id, nombre, apellido, especialidad));
        cout << "Entrenador registrado correctamente.\n";
    } catch (const exception& ex) {
        cout << "Error: " << ex.what() << endl;
    }
}

void GestorEjercicios::listarEntrenadores() const {
    cout << "\n--- ENTRENADORES REGISTRADOS (" << entrenadores.size() << ") ---\n";
    if (entrenadores.empty()) { cout << "  (No hay entrenadores)\n"; return; }
    for (const Entrenador* e : entrenadores) e->mostrarInfo();
}

void GestorEjercicios::asignarClienteAEntrenador() {
    cout << "\n--- ASIGNAR CLIENTE A ENTRENADOR ---\n";
    listarEntrenadores();
    cout << "ID del entrenador: "; string idE; cin >> idE; cin.ignore();
    Entrenador* ent = buscarEntrenadorPorId(idE);
    if (!ent) { cout << "Entrenador no encontrado.\n"; return; }

    listarClientes();
    cout << "ID del cliente a asignar: "; string idC; cin >> idC; cin.ignore();
    Cliente* cli = buscarClientePorId(idC);
    if (!cli) { cout << "Cliente no encontrado.\n"; return; }

    ent->asignarCliente(cli);
    cout << "Cliente " << cli->getNombre() << " asignado a "
         << ent->getNombre() << " correctamente.\n";
}

Entrenador* GestorEjercicios::buscarEntrenadorPorId(const string& id) const {
    for (Entrenador* e : entrenadores)
        if (e->getId() == id) return e;
    return nullptr;
}

// ============================================================
//  Datos de demostración
// ============================================================
void GestorEjercicios::cargarDatosDemostracion() {
    // Ejercicios Cardio
    catalogo.push_back(new EjercicioCardio("EJ1", "Trote en cinta",  "Piernas",    30, 2, 140));
    catalogo.push_back(new EjercicioCardio("EJ2", "Bicicleta",       "Piernas",    40, 1, 120));
    catalogo.push_back(new EjercicioCardio("EJ3", "Saltar la cuerda","Full body",  15, 3, 160));
    catalogo.push_back(new EjercicioCardio("EJ4", "Eliptica",        "Full body",  25, 2, 135));

    // Ejercicios Fuerza
    catalogo.push_back(new EjercicioFuerza("EJ5", "Sentadilla",   "Cuadriceps", 20, 2, 4, 12));
    catalogo.push_back(new EjercicioFuerza("EJ6", "Press banca",  "Pecho",      25, 3, 3, 10));
    catalogo.push_back(new EjercicioFuerza("EJ7", "Peso muerto",  "Espalda",    30, 3, 4,  8));
    catalogo.push_back(new EjercicioFuerza("EJ8", "Curl biceps",  "Biceps",     15, 1, 3, 15));
    catalogo.push_back(new EjercicioFuerza("EJ9", "Triceps polea","Triceps",    15, 1, 3, 15));
    catalogo.push_back(new EjercicioFuerza("EJ10","Plancha",      "Core",       10, 2, 3,  1));

    // Clientes de ejemplo
    clientes.push_back(new Cliente("C001", "Lucciano",    "Suazo", "lucciano@gmail.com",    28));
    clientes.push_back(new Cliente("C002", "Benjamin", "Gonzalez",  "pelotudo23@gmail.com", 35));

    // Entrenadores de ejemplo
    entrenadores.push_back(new Entrenador("ENT001", "Simon",  "Saavedra", "Musculacion"));
    entrenadores.push_back(new Entrenador("ENT002", "Claudia","Vega",    "Cardio y Funcional"));

    // Asignar clientes a entrenadores
    entrenadores[0]->asignarCliente(clientes[0]); // Simon -> Lucciano
    entrenadores[1]->asignarCliente(clientes[1]); // Claudia -> Benjamin

    cout << "  [Sistema] Datos de demostracion cargados: "
         << catalogo.size()    << " ejercicios, "
         << clientes.size()    << " clientes, "
         << entrenadores.size()<< " entrenadores.\n";
}
