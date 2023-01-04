#include "../headers/library_declaration.h"

int AreaGioco::getPunteggio() {
    return this->punteggio;
}

AreaGioco::AreaGioco() {
    this->colpo_tentativo = 1;
    this->punteggio = 0;
    this->gioco_terminato = false;
}

void AreaGioco::creaAreaGioco() {
    for(int i = 0; i < SIZE; i++) {
        vector<Cella> riga;
        for(int j = 0; j < SIZE; j++) {
            Cella cella(ACQUA, 0, i, j);
            riga.push_back(cella);
        }
        area.push_back(riga);
    }
}

void AreaGioco::visualizzaAreaGioco(WINDOW *win) {
    int center_matrix = X_CENTER+(getmaxx(win)-22)/2;
    WINDOW *matrix = newwin(11, 22, getmaxy(win)/2, center_matrix);

    for(int i = 0; i < area.size(); i++) {
        wmove(matrix, i, 0);
        for(int j = 0; j < area.size(); j++) {
            if(j == 0) {
                string val = to_string(i+1);
                if(val.length() > 1) {
                    wprintw(matrix, val.c_str());
                    wprintw(matrix, " ");
                } else {
                    wprintw(matrix, " ");
                    wprintw(matrix, val.c_str());
                    wprintw(matrix, " ");
                }
            }
            waddch(matrix, area[i][j].getContenuto());
            wprintw(matrix, " ");
        }
    }
    wprintw(matrix, "  ");
    for(int i = 65; i < 75; i++) {
        waddch(matrix, char(i));
        if(i == 74) {
            break;
        }
        wprintw(matrix, " ");
    }
    wfillwithchar(win, 12, 1, "~");
    refresh();
    wrefresh(matrix);
    wrefresh(win);
}

Cella AreaGioco::generaNave() {
    Cella nave;
    int x = rand() % SIZE;
    int y = rand() % SIZE;

    for(int i = 0; i < navi.size(); i++) {
        while(x == navi[i].getX() && y == navi[i].getY()) {
            x = rand() % SIZE;
            y = rand() % SIZE;
        }
    }

    int punteggio = rand() % PUNTEGGIO_MAX_NAVI + 1;
    nave.setValues(POS_NAVE, punteggio, x, y);
    return nave;
}

void AreaGioco::visualizzaPosizioniNavi() {
    for(int i = 0; i < NUM_NAVI; i++) {
        if(area[navi[i].getX()][navi[i].getY()].getContenuto() != NAVE_COLPITA) {
            area[navi[i].getX()][navi[i].getY()].setContenuto(POS_NAVE);
        }
    }
}

void AreaGioco::generaPosizioniNavi() {
    for(int i = 0; i < NUM_NAVI; i++) {
        Cella nave;
        navi.push_back(nave);
    }
    for(int i = 0; i < NUM_NAVI; i++) {
        navi[i] = generaNave();
        area[navi[i].getX()][navi[i].getY()].setPunteggio(navi[i].getPunteggio());
    }
    #if ENABLE_DEBUG__
        visualizzaPosizioniNavi();
    #endif
}

int AreaGioco::trasformaCoordCharInInt(char coord, int start_i, int end_i) {
    for(int i = start_i, counter = 0; i < end_i; i++, counter++) {
        if(coord == (char)i) {
            return counter;
        }
    }
    return -1;
}

void AreaGioco::aggiornaPunteggio(int value) {
    this->punteggio += value;
}

void AreaGioco::inserisciCoordinate(WINDOW *win, int &x, int &y) {
    char c_coords[7];
    int y_int, x_int;
    char y_char, x_char;
    bool error = false;
    bool error_enter = false;
    string coords;

    wclear(win);
    curs_set(1);
    echo();
    outputNumColpo(win, 0, 1);

    do {
        error = false;
        error_enter = false;
        mvwprintw(win, 1, 1, "Inserisci le coordinate [colonna][riga] > ");
        refresh();
        wrefresh(win);

        int value;
        int counter = 0;

        do {
            wmove(win, 1, 43+counter);
            counter < 8 ? echo() : noecho();  
            value = wgetch(win);

            switch(value) {
                case 8:
                    if(counter == 0) {
                        break;
                    }
                    counter--;
                    wmove(win, 1, 43+counter);
                    wprintw(win, " ");
                    coords.pop_back();
                    break;
                default:
                    if(counter <= 7 && value != '\n') {
                        counter++;
                        coords.push_back(value);
                    }
            }
        } while(value != '\n');

        #if ENABLE_DEBUG__
            if(coords == ":exit:") {
                exit(1);
            }
        #endif
        
        y_char = coords[0];
        if(checkIfIsValidChar(y_char)) {
            y_int = trasformaCoordCharInInt(y_char, 65, 75);
            coords.erase(coords.begin());
        } else {
            error = true;
        }
        if(checkIfIsNumber(coords) && !error) {
            x_int = stoi(coords);
            x_int--;
        } else {
            error = true;
        }
        if(x_int >= SIZE || x_int < 0 || y_int > SIZE || y_int < 0) {
            error = true;
        }

        if(error) {
            counter = 0;
            coords = "";
            mvwprintw(win, 2, 1, "COORDINATE NON VALIDE!");
            wfillwithchar(win, 1, 43, " ");
        }

        refresh();
        wrefresh(win);
    } while(error);

    noecho();
    curs_set(0);

    x_sparata = coords;
    y_sparata = y_char;
    x = x_int;
    y = y_int;
}

void AreaGioco::controlloCoordinate(WINDOW *win, int x, int y) {
    Cella cella(area[x][y]);

    wclear(win);
    outputSparo(win, 2, 1);

    if(cella.getContenuto() == ACQUA && cella.getPunteggio() > 0) {
        wattron(win, COLOR_PAIR(10));
        mvwprintw(win, 3, 1, "HAI COLPITO UNA NAVE!");
        cella.setContenuto(NAVE_COLPITA);
    } else if(cella.getContenuto() == ACQUA && cella.getPunteggio() == 0) {
        wattron(win, COLOR_PAIR(13));
        mvwprintw(win, 3, 1, "FLOP NELL'ACQUA!");
        cella.setContenuto(COLPO_A_VUOTO);
    } else if(cella.getContenuto() == COLPO_A_VUOTO || cella.getContenuto() == NAVE_COLPITA) {
        wattron(win, COLOR_PAIR(12));
        mvwprintw(win, 3, 1, "HAI COLPITO QUESTA CELLA IN PRECEDENZA");
        mvwprintw(win, 4, 1, "COLPO SPRECATO!");
    } else {
        #if ENABLE_DEBUG__
            if(cella.getContenuto() == POS_NAVE && cella.getPunteggio() > 0) {
                wattron(win, COLOR_PAIR(10));
                mvwprintw(win, 3, 1, "HAI COLPITO UNA NAVE!");
                wattroff(win, COLOR_PAIR(10));
                wattron(win, COLOR_PAIR(14));
                wprintw(win, " DEBUG!");
                cella.setContenuto(NAVE_COLPITA);
                wattroff(win, COLOR_PAIR(14));
            }
        #endif
    }
    wattroff(win, COLOR_PAIR(10));
    wattroff(win, COLOR_PAIR(12));
    wattroff(win, COLOR_PAIR(13));

    aggiornaPunteggio(cella.getPunteggio());
    cella.setPunteggio(0);
    area[x][y].setValues(cella);

    outputPunteggio(win, 1, 1);
    refresh();
    wrefresh(win);
}

void AreaGioco::outputPunteggio(WINDOW *win, int y, int x) {
    wattron(win, A_REVERSE);
    string punteggio_output = "PUNTEGGIO: " + to_string(punteggio);
    mvwprintw(win, y, x, punteggio_output.c_str());
    string output_max = "PER VINCERE: " + to_string(MAX_PUNTEGGIO);
    mvwprintw(win, y, getmaxx(win)-output_max.length()-1, output_max.c_str());
    wattroff(win, A_REVERSE);
}

void AreaGioco::outputSparo(WINDOW *win, int y, int x) {
    wattron(win, COLOR_PAIR(11));
    string colpito_output;
    if(colpo_tentativo == 1) {
        colpito_output = "TARGET: --";
    } else {
        colpito_output = "TARGET: " + y_sparata + x_sparata;
    }
    mvwprintw(win, y, x, colpito_output.c_str());
    wattroff(win, COLOR_PAIR(11));
    wfillwithchar(win, 5, 1, "~");
}

void AreaGioco::outputNumColpo(WINDOW *win, int y, int x) {
    wattron(win, A_REVERSE);
    string output_num_colpo = "[COLPO " + to_string(colpo_tentativo++) + "/" + to_string(COLPI) + "]";
    mvwprintw(win, y, x, output_num_colpo.c_str());
    wattroff(win, A_REVERSE);
}