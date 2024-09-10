#include <iostream>

#include "board.hpp"

Board::Board()
{
    // Bitboards para cada jugador.
    // Usando valores binarios, inicialmente vacíos.
    board[X] = 0b000000000; // Bitboard para X
    board[O] = 0b000000000; // Bitboard para O
    turn = X;  // Comienza jugando X
}

Board::Board(uint16_t x, uint16_t o, MARK turn): board{x, o}, turn(turn) {}

Board::~Board() = default;

uint16_t Board::getXBoard() const { return board[X]; }
uint16_t Board::getOBoard() const { return board[O]; }
MARK Board::getActiveTurn() const { return turn; }

int Board::evaluate(int depth)
{
    /* Si ha ganado, devolvemos un puntaje positivo
     * Se resta la profundidad para penalizar las victorias que ocurren en niveles más profundos.
     * Esto hace que el algoritmo prefiera ganar más rápidamente si es posible.
     */
    if (hasXWon())
        return (turn == X) ? (10 - depth) : (depth - 10);  // Si 'X' ha ganado, es bueno para el maximizador (X)
    if (hasOWon())
        return (turn == O) ? (10 - depth) : (depth - 10); // Si 'O' ha ganado, es bueno para el minimizador (O)
    if (isFull())
        return 0;  // Empate
}

std::vector<int> Board::generateAllLegalMoves()
{
    std::vector<int> legalMoves;
    for (int i = 0; i < 9; i++)
        if (isLegalMove(i))
            legalMoves.push_back(i);
    return legalMoves;
}

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

void Board::undoMove(int position)
{
    board[turn] ^= (oneMask << position);
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

bool Board::endGame()
{
    return hasXWon() || hasOWon() || isFull();
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
