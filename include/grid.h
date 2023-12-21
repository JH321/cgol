#include <iostream>
#include <unordered_set>
#include <vector>
#include <utility>
#define DEFAULTGRIDSIZE 20
/**
 * @brief This class is for creating a function object that will serve
 *        as a hash function for a std::pair object. This is necessary
 *        to create an std::unordered_set object of std::pair keys. 
*/
struct pair_hash
{
    size_t operator()(const std::pair<size_t, size_t>& hashObj) const
    {
        return hashObj.first * 31 + hashObj.second;
    }
};

/**
 * @brief The grid class will create a grid object that represents the two
 *        dimensional grid world of Conway's game of life. It has methods to
 *        initialize a grid with a certain preset of alive cells and to update
 *        the grid to the next generation of cells.
*/
class grid
{
    private:
        
        //set to keep track of which cells are alive in the current generation
        std::unordered_set<std::pair<size_t, size_t>, pair_hash> alive_cells;
        
        //2d vector to keep track of the number of neighbors that a cell has in 
        //the current generation
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