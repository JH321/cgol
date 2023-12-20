#include <iostream>
#include <forward_list>
#include <vector>

#define GRIDSIZE 100

class grid
{
    private:
        struct cell
        {
            size_t x;
            size_t y;
        };

        std::forward_list<cell> alive_cells;
        int neighbor_grid[GRIDSIZE][GRIDSIZE];

        void update_neighbors();
        void update_alive_cells();
        
    
    public:

        grid();
        grid(std::vector<std::pair<size_t, size_t>> init_cells);
        void update_cells();
        bool is_alive_cell(size_t x, size_t y);

        
        
};