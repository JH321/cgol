#include <iostream>
#include <unordered_set>
#include <vector>

#define GRIDSIZE 100

struct pair_hash
{
    size_t operator()(const std::pair<size_t, size_t>& hashObj) const
    {
        return hashObj.first * 31 + hashObj.second;
    }
};

class grid
{
    private:

        std::unordered_set<std::pair<size_t, size_t>, pair_hash> alive_cells;
        int neighbor_grid[GRIDSIZE][GRIDSIZE];

        void update_neighbors();
        void update_alive_cells();
        void zero_neighbor_grid();
    
    public:

        grid();
        grid(std::vector<std::pair<size_t, size_t>> init_cells);
        void update_cells();
        bool is_alive_cell(size_t x, size_t y);

        
        
};