

#include "grid.h"
#include "ansi_escapes.h"

int main(int argc, char *argv[])
{
    std::cout << "Conway's game of Life\n";
    std::cout << "Press the return key to display each generation\n";

    std::cin.get();

    setupConsole();

    grid current_generation;

    current_generation.randomize();

    while (true)
    {
        current_generation.draw();

        std::cin.get();

        grid next_genration;

        calculate(current_generation, next_genration);

        current_generation.update(next_genration);
    }

    std::cout << "\x1b[" << 0 << ";" << row_max - 1 << "H";
    restoreConsole();
}


