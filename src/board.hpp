#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>

enum MARK {X, O};

class Board
{
    uint16_t board[2];
    MARK turn;

    uint16_t oneMask, fullMask;

    bool isLegalMove(int position);  // Verificar si la posición es legal
    bool checkWin(uint16_t board);  //

    public:
        Board();  // Constructor prototype
        ~Board();  // Destructor prototype

        void print();  // Función para imprimir el tablero en una forma legible
        bool makeMove(int position);  // Función para hacer una jugada

        bool hasXWon();  // Verificar si X ha ganado
        bool hasOWon();  // Verificar si O ha ganado
        bool isFull();  // Verificar si el tablero está lleno
};

#endif //BOARD_HPP
