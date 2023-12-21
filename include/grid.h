#include <iostream>
#include <unordered_set>
#include <vector>
#include <utility>
#define DEFAULTGRIDSIZE 20

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
        std::vector<std::vector<size_t>> neighbor_grid;

        void update_neighbors();
        void update_alive_cells();
        void zero_neighbor_grid();
    
    public:

        grid();
        grid(std::vector<std::pair<size_t, size_t>> init_cells, size_t num_rows, size_t num_cols);
        void update_cells();
        bool is_alive_cell(size_t x, size_t y);

        void print_grid();

        
        
};