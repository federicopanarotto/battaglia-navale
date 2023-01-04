#pragma once
#ifndef AREAGIOCO_HPP
#define AREAGIOCO_HPP

#include "library_declaration.h"

class AreaGioco {
    private:
        std::vector<std::vector<Cella>> area;
        std::vector<Cella> navi;

        std::string x_sparata;
        std::string y_sparata;
        int colpo_tentativo;
        int punteggio;

        Cella generaNave();
        int trasformaCoordCharInInt(char coord, int start_i, int end_i);

    public:
        int getPunteggio();
        
        void creaAreaGioco();
        void visualizzaAreaGioco(WINDOW *win);
        void aggiornaPunteggio(int value);
        void generaPosizioniNavi();
        void inserisciCoordinate(WINDOW *win, int &x, int &y);
        void controlloCoordinate(WINDOW *win, int x, int y);

        AreaGioco();
        int center;
        bool gioco_terminato;

        void visualizzaPosizioniNavi();
        void outputPunteggio(WINDOW *win, int y, int x);
        void outputSparo(WINDOW *win, int y, int x);
        void outputNumColpo(WINDOW *win, int y, int x);
};

#endif