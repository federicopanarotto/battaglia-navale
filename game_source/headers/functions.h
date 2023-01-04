#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "library_declaration.h"

void checkTerminalHasColors();
void wfillAllBckg(WINDOW *win, int val);
void wprintcentertext(WINDOW *win, int y, std::string text);
void wfillwithchar(WINDOW *win, int y, int start_x, const char *c);
void wprinttextfillingline(WINDOW *win, int y, int x, int x_max, std::string text);
void wfillwithcharX(WINDOW *win, int y, int start_x, int end_x, char c);

bool checkIfIsNumber(std::string value);
bool checkIfIsValidChar(char value);

#endif