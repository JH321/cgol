#include <iostream>
#include <grid.h>
#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    std::vector<std::pair<size_t, size_t>> vec{{3, 3}, {3, 4}, {3, 5}, {2, 5}, {1, 4}};
    grid grid{vec, 20, 20};
    while(true)
    {
        grid.print_grid();
        grid.update_cells();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}