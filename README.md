Short console program to simulate Conway's Game of Life.

Uses an algorithm that loops through alive cells to produce the next generation of cells.
Essentially is O(# of alive cells) in terms of runtime at the cost of O(n^2) auxiliary space
where n is the dimension of the world grid that cells live on.
