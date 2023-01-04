#include "../headers/library_declaration.h"

void Cella::setContenuto(char contenuto) {
    this->contenuto = contenuto;
}

void Cella::setPunteggio(int punteggio) {
    this->punteggio = punteggio;
}

void Cella::setX(int x) {
    this->x = x;
}

void Cella::setY(int y) {
    this->y = y;
}

char Cella::getContenuto() {
    return contenuto;
}

int Cella::getPunteggio() {
    return punteggio;
}

int Cella::getX() {
    return x;
}

int Cella::getY() {
    return y;
}

void Cella::setValues(Cella c) {
    setContenuto(c.contenuto);
    setPunteggio(c.punteggio);
    setX(c.x);
    setY(c.y);
}

void Cella::setValues(char contenuto, int punteggio, int x, int y) {
    setContenuto(contenuto);
    setPunteggio(punteggio);
    setX(x);
    setY(y);
}

Cella::Cella() {
    return;
}

Cella::Cella(char contenuto, int punteggio, int x, int y) {
    setContenuto(contenuto);
    setPunteggio(punteggio);
    setX(x);
    setY(y);
}