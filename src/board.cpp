#include <iostream>
#include <cstdint>

#include "board.hpp"

Board::Board()
{
    // Bitboards para cada jugador.
    // Usando valores binarios, inicialmente vacíos.
    board[X] = 0b000000000; // Bitboard para X
    board[O] = 0b000000000; // Bitboard para O
    turn = X;  // Comienza jugando X

    oneMask = 0b000000001;
    fullMask = 0b111111111;
}

Board::~Board() = default;

bool Board::isLegalMove(int position)
{
    if (position < 0 || position > 8)  // posicion dentro del rango?
        return false;
    if ((board[X] | board[O]) & (oneMask << position))  // posicion es vacia?
        return false;
    return true;
}

bool Board::makeMove(int position)
{
    if (isLegalMove(position)) {
        board[turn] |= (oneMask << position);
        turn = 1-turn == 0 ? X : O;  // cambio de turno
        return true;
    }
    return false;
}

bool Board::checkWin(uint16_t board)
{
    uint16_t winningBoards[8] = {
        0b111000000,  // fila superior
        0b000111000,  // fila media
        0b000000111,  // fila inferior
        0b100100100,  // columna izquierda
        0b010010010,  // columna media
        0b001001001,  // columna derecha
        0b100010001,  // diagonal principal
        0b001010100   // diagonal secundaria
    };
    for (uint16_t wp : winningBoards)
        if ((board & wp) == wp) return true;
    return false;
}

bool Board::hasXWon() { return checkWin(board[X]); }
bool Board::hasOWon() { return checkWin(board[O]); }

bool Board::isFull()
{
    return (board[X] | board[O]) == fullMask;
}

void Board::print()
{
    for (int i = 0; i < 9; i++) {  // 9 casillas
        // cada casilla i se compara con ambos tableros para ver si hay una X o O
        if (board[X] & (oneMask << i))
            std::cout << "X ";
        else if (board[O] & (oneMask << i))
            std::cout << "O ";
        else
            std::cout << "- ";
        if (i % 3 == 2) std::cout << std::endl;  // salto de linea cuando completa una fila
    }
    std::cout << std::endl;
}
