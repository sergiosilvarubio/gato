#include "board.hpp"

#include <iostream>

int main()
{
    Board board;
    board.print();  // Mostrar el tablero inicial

    // Para realizar una jugada
    // se definen los siguientes valores para cada casilla
    // 0 | 1 | 2
    // 3 | 4 | 5
    // 6 | 7 | 8

    // Pruebas de algunas jugadas

    // Prueba de Juego: Gana X diagonal principal
    board.makeMove(0);
    board.makeMove(2);
    board.makeMove(4);
    board.makeMove(6);
    board.makeMove(8);

    /*
    // Prueba de Juego: Empate
    board.makeMove(1);
    board.makeMove(0);
    board.makeMove(2);
    board.makeMove(5);
    board.makeMove(3);
    board.makeMove(6);
    board.makeMove(4);
    board.makeMove(7);
    board.makeMove(8);
    */

    board.print();  // Mostrar el tablero

    // Comprobar si hay un ganador
    if (board.hasXWon()) {
        std::cout << "X ha ganado" << std::endl;
    } else if (board.hasOWon()) {
        std::cout << "O ha ganado" << std::endl;
    } else if (board.isFull()) {
        std::cout << "Empate" << std::endl;
    } else {
        std::cout << "Nadie ha ganado todavía." << std::endl;
    }

    return 0;
}