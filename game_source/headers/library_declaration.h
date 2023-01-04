#pragma once
#ifndef LIBRARY_DEC_H
#define LIBRARY_DEC_H

#ifdef __linux__
    #include <ncurses.h>
#elif _WIN32
    #include <ncursesw/ncurses.h>
#endif

#define ENABLE_DEBUG__ false

// Dichiarazione delle librerie globali a tutti i file
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <signal.h>
#include "functions.h"
#include "menu.h"
#include "Cella.hpp"
#include "AreaGioco.hpp"
using namespace std;

// Costanti riservate alla dimensione del terminale
const int Y_DIM_TERMINALE = 28;
const int X_DIM_TERMINALE = 65;
const int X_CENTER = X_DIM_TERMINALE/2;

// Costanti riservate alla struttura del gioco
const char ACQUA = '~';
const char NAVE_COLPITA = 'C';
const char COLPO_A_VUOTO = 'X';
const char POS_NAVE = 'N';
const int SIZE = 10;

// Se il debug è abilitato mostra i config del gioco di DEBUG
#if ENABLE_DEBUG__
    const int NUM_NAVI = 30;
    const int COLPI = 2;
    const int MAX_PUNTEGGIO = 2;
    const int PUNTEGGIO_MAX_NAVI = 10;
#else
    const int NUM_NAVI = 20;
    const int COLPI = 25;
    const int MAX_PUNTEGGIO = 15;
    const int PUNTEGGIO_MAX_NAVI = 5;
#endif

#endif