#ifndef CLASES_HPP
#define CLASES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <limits>

// Enumeración de nivel taxonómico
enum class NivelTaxonomico {
    RECORDAR,
    ENTENDER,
    APLICAR,
    ANALIZAR,
    EVALUAR,
    CREAR
};

std::string nivelToString(NivelTaxonomico nivel);

// Clase Pregunta
class Pregunta {
private:
    int id;
    std::string tipo;
    NivelTaxonomico nivel;
    std::string enunciado;
    std::string respuestaCorrecta;
    int tiempoEstimado;

public:
    Pregunta(int id, std::string tipo, NivelTaxonomico nivel,
             std::string enunciado, std::string respuestaCorrecta, int tiempoEstimado);

    int getId() const;
    NivelTaxonomico getNivel() const;
    int getTiempoEstimado() const;
    void mostrar() const;
};

// Clase BancoPreguntas
class BancoPreguntas {
private:
    std::vector<Pregunta> preguntas;

public:
    void agregarPregunta(const Pregunta& pregunta);
    bool eliminarPregunta(int id);
    bool modificarPregunta(int id, const Pregunta& nuevaPregunta);
    Pregunta* consultarPregunta(int id);
    std::vector<Pregunta> buscarPorNivel(NivelTaxonomico nivel) const;
    void mostrarTodas() const;
};

// Clase Examen
class Examen {
private:
    std::vector<Pregunta> preguntasSeleccionadas;

public:
    void agregarPregunta(const Pregunta& pregunta);
    int calcularTiempoTotal() const;
    void mostrarResumen() const;
};

// Clase Menu
class Menu {
private:
    BancoPreguntas banco;
    Examen examen;
    int siguienteId = 1;

    void mostrarMenuOpciones();
    void agregarPregunta();
    void eliminarPregunta();
    void modificarPregunta();
    void consultarPregunta();
    void buscarPorNivel();
    void generarExamen();

public:
    void ejecutar();
};

#endif // CLASES_HPP
