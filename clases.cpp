#include "clases.hpp"

// ---------- NivelTaxonomico ----------
std::string nivelToString(NivelTaxonomico nivel) {
    switch (nivel) {
        case NivelTaxonomico::RECORDAR: return "Recordar";
        case NivelTaxonomico::ENTENDER: return "Entender";
        case NivelTaxonomico::APLICAR: return "Aplicar";
        case NivelTaxonomico::ANALIZAR: return "Analizar";
        case NivelTaxonomico::EVALUAR: return "Evaluar";
        case NivelTaxonomico::CREAR: return "Crear";
        default: return "Desconocido";
    }
}

// ---------- Pregunta ----------
Pregunta::Pregunta(int id, std::string tipo, NivelTaxonomico nivel,
                   std::string enunciado, std::string respuestaCorrecta, int tiempoEstimado)
    : id(id), tipo(tipo), nivel(nivel), enunciado(enunciado),
      respuestaCorrecta(respuestaCorrecta), tiempoEstimado(tiempoEstimado) {}

int Pregunta::getId() const { return id; }

NivelTaxonomico Pregunta::getNivel() const { return nivel; }

int Pregunta::getTiempoEstimado() const { return tiempoEstimado; }

void Pregunta::mostrar() const {
    std::cout << "ID: " << id << "\n"
              << "Tipo: " << tipo << "\n"
              << "Nivel: " << nivelToString(nivel) << "\n"
              << "Enunciado: " << enunciado << "\n"
              << "Respuesta: " << respuestaCorrecta << "\n"
              << "Tiempo estimado: " << tiempoEstimado << " min\n";
}

// ---------- BancoPreguntas ----------
void BancoPreguntas::agregarPregunta(const Pregunta& pregunta) {
    preguntas.push_back(pregunta);
}

bool BancoPreguntas::eliminarPregunta(int id) {
    for (auto it = preguntas.begin(); it != preguntas.end(); ++it) {
        if (it->getId() == id) {
            preguntas.erase(it);
            return true;
        }
    }
    return false;
}

bool BancoPreguntas::modificarPregunta(int id, const Pregunta& nuevaPregunta) {
    for (auto& pregunta : preguntas) {
        if (pregunta.getId() == id) {
            pregunta = nuevaPregunta;
            return true;
        }
    }
    return false;
}

Pregunta* BancoPreguntas::consultarPregunta(int id) {
    for (auto& pregunta : preguntas) {
        if (pregunta.getId() == id) {
            return &pregunta;
        }
    }
    return nullptr;
}

std::vector<Pregunta> BancoPreguntas::buscarPorNivel(NivelTaxonomico nivel) const {
    std::vector<Pregunta> resultado;
    for (const auto& pregunta : preguntas) {
        if (pregunta.getNivel() == nivel) {
            resultado.push_back(pregunta);
        }
    }
    return resultado;
}

void BancoPreguntas::mostrarTodas() const {
    if (preguntas.empty()) {
        std::cout << "No hay preguntas registradas.\n";
        return;
    }
    for (const auto& p : preguntas) {
        p.mostrar();
        std::cout << "-------------------\n";
    }
}

// ---------- Examen ----------
void Examen::agregarPregunta(const Pregunta& pregunta) {
    preguntasSeleccionadas.push_back(pregunta);
}

int Examen::calcularTiempoTotal() const {
    int total = 0;
    for (const auto& p : preguntasSeleccionadas) {
        total += p.getTiempoEstimado();
    }
    return total;
}

void Examen::mostrarResumen() const {
    std::cout << "\n--- EXAMEN GENERADO ---\n";
    for (const auto& p : preguntasSeleccionadas) {
        p.mostrar();
        std::cout << "-------------------\n";
    }
    std::cout << "Tiempo total estimado: " << calcularTiempoTotal() << " minutos\n";
}

// ---------- Menu ----------
void Menu::mostrarMenuOpciones() {
    std::cout << "\n--- MENÚ ---\n"
              << "1. Agregar pregunta\n"
              << "2. Eliminar pregunta\n"
              << "3. Modificar pregunta\n"
              << "4. Consultar pregunta\n"
              << "5. Buscar preguntas por nivel\n"
              << "6. Mostrar todas\n"
              << "7. Generar examen\n"
              << "0. Salir\n"
              << "Opción: ";
}

void Menu::agregarPregunta() {
    std::string tipo, enunciado, respuesta;
    int nivel, tiempo;

    std::cout << "Tipo: ";
    std::getline(std::cin, tipo);

    std::cout << "Nivel (0-5): ";
    std::cin >> nivel;
    std::cin.ignore();

    std::cout << "Enunciado: ";
    std::getline(std::cin, enunciado);

    std::cout << "Respuesta: ";
    std::getline(std::cin, respuesta);

    std::cout << "Tiempo estimado: ";
    std::cin >> tiempo;
    std::cin.ignore();

    banco.agregarPregunta(Pregunta(siguienteId++, tipo, static_cast<NivelTaxonomico>(nivel),
                                   enunciado, respuesta, tiempo));
    std::cout << "Pregunta agregada.\n";
}

void Menu::eliminarPregunta() {
    int id;
    std::cout << "ID a eliminar: ";
    std::cin >> id;
    std::cin.ignore();

    if (banco.eliminarPregunta(id))
        std::cout << "Eliminada con éxito.\n";
    else
        std::cout << "No se encontró la pregunta.\n";
}

void Menu::modificarPregunta() {
    int id, nivel, tiempo;
    std::string tipo, enunciado, respuesta;

    std::cout << "ID a modificar: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Nuevo tipo: ";
    std::getline(std::cin, tipo);

    std::cout << "Nuevo nivel (0-5): ";
    std::cin >> nivel;
    std::cin.ignore();

    std::cout << "Nuevo enunciado: ";
    std::getline(std::cin, enunciado);

    std::cout << "Nueva respuesta: ";
    std::getline(std::cin, respuesta);

    std::cout << "Nuevo tiempo: ";
    std::cin >> tiempo;
    std::cin.ignore();

    Pregunta nueva(id, tipo, static_cast<NivelTaxonomico>(nivel), enunciado, respuesta, tiempo);
    if (banco.modificarPregunta(id, nueva))
        std::cout << "Modificada con éxito.\n";
    else
        std::cout << "No se encontró la pregunta.\n";
}

void Menu::consultarPregunta() {
    int id;
    std::cout << "ID a consultar: ";
    std::cin >> id;
    std::cin.ignore();

    Pregunta* p = banco.consultarPregunta(id);
    if (p)
        p->mostrar();
    else
        std::cout << "No encontrada.\n";
}

void Menu::buscarPorNivel() {
    int nivel;
    std::cout << "Nivel (0-5): ";
    std::cin >> nivel;
    std::cin.ignore();

    auto resultados = banco.buscarPorNivel(static_cast<NivelTaxonomico>(nivel));
    if (resultados.empty()) {
        std::cout << "No se encontraron preguntas.\n";
    } else {
        for (const auto& p : resultados) {
            p.mostrar();
            std::cout << "-------------------\n";
        }
    }
}

void Menu::generarExamen() {
    int nivel, cantidad;
    std::cout << "Nivel (0-5): ";
    std::cin >> nivel;
    std::cin.ignore();
    std::cout << "Cantidad de preguntas: ";
    std::cin >> cantidad;
    std::cin.ignore();

    auto disponibles = banco.buscarPorNivel(static_cast<NivelTaxonomico>(nivel));
    if ((int)disponibles.size() < cantidad) {
        std::cout << "No hay suficientes preguntas.\n";
        return;
    }

    examen = Examen();
    for (int i = 0; i < cantidad; ++i) {
        examen.agregarPregunta(disponibles[i]);
    }

    examen.mostrarResumen();
}

void Menu::ejecutar() {
    int opcion = -1;
    while (opcion != 0) {
        mostrarMenuOpciones();
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (opcion) {
            case 1: agregarPregunta(); break;
            case 2: eliminarPregunta(); break;
            case 3: modificarPregunta(); break;
            case 4: consultarPregunta(); break;
            case 5: buscarPorNivel(); break;
            case 6: banco.mostrarTodas(); break;
            case 7: generarExamen(); break;
            case 0: std::cout << "Saliendo...\n"; break;
            default: std::cout << "Opción inválida.\n";
        }
    }
}
