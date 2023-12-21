#include <grid.h>

/**
 * @brief Default constructor for a grid object. Initializes neighbor_grid to all zeros.
*/
grid::grid()
{
    for(size_t i = 0; i < DEFAULTGRIDSIZE; ++i)
    {
        for(size_t j = 0 ; j < DEFAULTGRIDSIZE; ++j)
        {
            neighbor_grid[i][j] = 0;
        }
    }


}

/**
 * @brief Overloaded constructor for grid object. 
 *        Can specify initial conditions (initial alive cells and grid dimensions).
 * 
 * @param init_cells The initial alive cells.
 * @param num_rows Number of rows in world grid.
 * @param num_cols Number of columns in world grid.
*/
grid::grid(std::vector<std::pair<size_t, size_t>> init_cells, size_t num_rows, size_t num_cols) 
: neighbor_grid(num_rows)
{

    for(size_t i = 0; i < num_rows; ++i)
    {
        neighbor_grid[i].resize(num_cols);
    }
    zero_neighbor_grid();

    for(size_t i = 0; i < init_cells.size(); ++i)
    {
        auto& curr_cell = init_cells[i];
        alive_cells.insert(std::make_pair(curr_cell.first, curr_cell.second));
    }
}


/**
 * @brief Helper method that zeros out the neighbor_grid member.
*/
void grid::zero_neighbor_grid()
{
    size_t num_rows = neighbor_grid.size();
    for(size_t i = 0; i < num_rows; ++i)
    {
        size_t num_cols = neighbor_grid[i].size();
        for(size_t j = 0 ; j < num_cols; ++j)
        {
            neighbor_grid[i][j] = 0;
        }
    }
}

/**
 * @brief Helper method that updates the neighbor_grid member.
 *        In the current generation, update the number of neighbors
 *        for a cell based on the alive cells. Essentially, for each
 *        cell alive, increment the neighbor count for all its neighbors 
 *        inside the neighbor_grid member.
*/
void grid::update_neighbors()
{
    size_t num_rows = neighbor_grid.size();
    size_t num_cols = neighbor_grid[0].size();
    zero_neighbor_grid();
    for(auto& curr : alive_cells)
    {
        size_t x = curr.first;
        size_t y = curr.second;
        if(x > 0)
            ++neighbor_grid[x - 1][y];
        if(y > 0)
            ++neighbor_grid[x][y - 1];
        if(x > 0 && y > 0)
            ++neighbor_grid[x - 1][y - 1];
        if(x < num_rows - 1 && y > 0)
            ++neighbor_grid[x + 1][y - 1];
        if(x < num_rows - 1)
            ++neighbor_grid[x + 1][y];
        if(x < num_rows - 1 && y < num_cols - 1)
            ++neighbor_grid[x + 1][y + 1];
        if(y < num_cols - 1)
            ++neighbor_grid[x][y + 1];
        if(x > 0 && y < num_cols - 1)
            ++neighbor_grid[x - 1][y + 1];
    }
}

/**
 * @brief Helper method that updates the cells that are alive
 *        for the next generation. Loop through all the alive cells
 *        in the current generation. For each alive cell, look at the
 *        all the neighbor cells. For each neighbor cell, if the neighbor count
 *        is 3 (meaning that particular cell has 3 neighbors), store it as an
 *        cell that becomes alive in the next generation. Loop through all the
 *        alive cells again. For each cell, add it to the next generation of
 *        alive cells if the cell has a neighbor count of 2 or 3 (the specific cell
 *        survives to the next generation).
*/
void grid::update_alive_cells()
{
    std::unordered_set<std::pair<size_t, size_t>, pair_hash> temp_cells{};
    size_t num_rows = neighbor_grid.size();
    size_t num_cols = neighbor_grid[0].size();
    //reproduce next generation cells
    for(auto& curr : alive_cells)
    {
        size_t x = curr.first;
        size_t y = curr.second;
        if(x > 0)
            if(neighbor_grid[x - 1][y] == 3)
                temp_cells.insert(std::make_pair(x - 1, y));
        if(y > 0)
            if(neighbor_grid[x][y - 1] == 3)
                temp_cells.insert(std::make_pair(x, y - 1));
        if(x > 0 && y > 0)
            if(neighbor_grid[x - 1][y - 1] == 3)
                temp_cells.insert(std::make_pair(x - 1, y - 1));
        if(x < num_rows - 1 && y > 0)
            if(neighbor_grid[x + 1][y - 1] == 3)
                temp_cells.insert(std::make_pair(x + 1, y - 1));
        if(x < num_rows - 1)
            if(neighbor_grid[x + 1][y] == 3)
                temp_cells.insert(std::make_pair(x + 1, y));
        if(x < num_rows - 1 && y < num_cols - 1)
            if(neighbor_grid[x + 1][y + 1] == 3)
                temp_cells.insert(std::make_pair(x + 1, y + 1));
        if(y < num_cols - 1)
            if(neighbor_grid[x][y + 1] == 3)
                temp_cells.insert(std::make_pair(x, y + 1));
        if(x > 0 && y < num_cols - 1)
            if(neighbor_grid[x - 1][y + 1] == 3)
                temp_cells.insert(std::make_pair(x - 1, y + 1));
    }

    //kill current generation cells
    for(auto& curr : alive_cells)
    {
        size_t x = curr.first;
        size_t y = curr.second;
        if(neighbor_grid[x][y] == 2 || neighbor_grid[x][y] == 3)
        {
            temp_cells.insert(std::make_pair(x, y));
        }
    }

    alive_cells.swap(temp_cells);
}

/**
 * @brief Updates the cells for the next generation.
*/
void grid::update_cells()
{
    update_neighbors();
    update_alive_cells();
}

/**
 * @brief Determine if a cell at given coordinates is alive.
 * 
 * @param x Row of cell to check if alive.
 * @param y Column of cell to check if alive.
*/
bool grid::is_alive_cell(size_t x, size_t y)
{
    return alive_cells.count(std::make_pair(x, y)) > 0;
}

/**
 * @brief Prints the current generation grid world to console.
*/
void grid::print_grid()
{
    size_t num_rows = neighbor_grid.size();
    
    for(size_t i = 0; i < num_rows; ++i)
    {
        size_t num_cols = neighbor_grid[i].size();
        for(size_t j = 0; j < num_cols; ++j)
        {
            std::cout << ((is_alive_cell(i, j)) ? "o" : "-");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
}
