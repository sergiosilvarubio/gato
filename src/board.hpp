#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <vector>

enum MARK {X, O};

class Board
{
    uint16_t board[2];
    MARK turn;

    uint16_t oneMask = 0b000000001;
    uint16_t fullMask = 0b111111111;

    bool isLegalMove(int position);  // Verificar si la posición es legal
    bool checkWin(uint16_t board);  //

    public:
        Board();  // Constructor prototype
        Board(uint16_t x, uint16_t o, MARK turn);
        ~Board();  // Destructor prototype

        int evaluate(int depth);  // Función de evaluación
        std::vector<int> generateAllLegalMoves();

        uint16_t getXBoard() const;
        uint16_t getOBoard() const;
        MARK getActiveTurn() const;

        void setActiveBitboard(uint16_t bitboard);

        void print();  // Función para imprimir el tablero en una forma legible
        bool makeMove(int position);  // Función para hacer una jugada
        void undoMove(int position);  // Función para deshacer una jugada

        bool hasXWon();  // Verificar si X ha ganado
        bool hasOWon();  // Verificar si O ha ganado
        bool isFull();  // Verificar si el tablero está lleno
        bool endGame();
};

#endif //BOARD_HPP
