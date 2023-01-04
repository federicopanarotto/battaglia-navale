#pragma once
#ifndef _MENU_H
#define _MENU_H

#include "library_declaration.h"

void printMenu(WINDOW *win, int y, std::vector<std::string> list, int &selected);
void useMenu(WINDOW *win, std::vector<std::string> list, int &choice, int &selected);

void visualizzaMenuGiocoInizio(WINDOW *terminale);
void visualizzaMenuGiocoFine(WINDOW *terminale, bool &gioca_ancora, int punteggio);

#endif