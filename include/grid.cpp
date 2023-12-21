#include <grid.h>

grid::grid()
{
    for(size_t i = 0; i < GRIDSIZE; ++i)
    {
        for(size_t j = 0 ; j < GRIDSIZE; ++j)
        {
            neighbor_grid[i][j] = 0;
        }
    }


}

grid::grid(std::vector<std::pair<size_t, size_t>> init_cells)
{
    zero_neighbor_grid();

    for(size_t i = 0; i < init_cells.size(); ++i)
    {
        auto& curr_cell = init_cells[i];
        alive_cells.insert(std::make_pair(curr_cell.first, curr_cell.second));
    }
}

void grid::zero_neighbor_grid()
{
    for(size_t i = 0; i < GRIDSIZE; ++i)
    {
        for(size_t j = 0 ; j < GRIDSIZE; ++j)
        {
            neighbor_grid[i][j] = 0;
        }
    }
}

void grid::update_neighbors()
{
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
        if(x < GRIDSIZE - 1 && y > 0)
            ++neighbor_grid[x + 1][y - 1];
        if(x < GRIDSIZE - 1)
            ++neighbor_grid[x + 1][y];
        if(x < GRIDSIZE - 1 && y < GRIDSIZE - 1)
            ++neighbor_grid[x + 1][y + 1];
        if(y < GRIDSIZE - 1)
            ++neighbor_grid[x][y + 1];
        if(x > 0 && y < GRIDSIZE - 1)
            ++neighbor_grid[x - 1][y + 1];
    }
}

void grid::update_alive_cells()
{
    std::unordered_set<std::pair<size_t, size_t>, pair_hash> temp_cells{};
    
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
        if(x < GRIDSIZE - 1 && y > 0)
            if(neighbor_grid[x + 1][y - 1] == 3)
                temp_cells.insert(std::make_pair(x + 1, y - 1));
        if(x < GRIDSIZE - 1)
            if(neighbor_grid[x + 1][y] == 3)
                temp_cells.insert(std::make_pair(x + 1, y));
        if(x < GRIDSIZE - 1 && y < GRIDSIZE - 1)
            if(neighbor_grid[x + 1][y + 1] == 3)
                temp_cells.insert(std::make_pair(x + 1, y + 1));
        if(y < GRIDSIZE - 1)
            if(neighbor_grid[x][y + 1] == 3)
                temp_cells.insert(std::make_pair(x, y + 1));
        if(x > 0 && y < GRIDSIZE - 1)
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