#pragma once
#ifndef CELLA_HPP
#define CELLA_HPP

#include "library_declaration.h"

class Cella {
    private:
        char contenuto;
        int punteggio;
        int x;
        int y;

    public:
        void setContenuto(char contenuto);
        void setPunteggio(int punteggio);
        void setX(int x);
        void setY(int y);
        
        char getContenuto();
        int  getPunteggio();
        int  getX();
        int  getY();

        void setValues(Cella c);
        void setValues(char contenuto, int punteggio, int x, int y);
        Cella();
        Cella(char contenuto, int punteggio, int x, int y);
};

#endif
