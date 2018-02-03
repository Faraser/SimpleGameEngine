#include "Grid.h"

Grid::Grid(int width, int height, int cellSize) :
        m_width(width),
        m_height(height),
        m_cellSize(cellSize) {
    m_numXCells = static_cast<int>(std::ceil(static_cast<float>(m_width) / cellSize));
    m_numYCells = static_cast<int>(std::ceil(static_cast<float>(m_height) / cellSize));

    m_cells.resize(m_numYCells * m_numXCells);

    // Allocate all the cells
    const int BALLS_TO_RESERVE = 20;
    m_cells.resize(m_numYCells * m_numXCells);
    for (int i=0; i<m_cells.size(); i++) {
        m_cells[i].balls.reserve(BALLS_TO_RESERVE);
    }
}

Grid::~Grid() {

}

Cell* Grid::getCell(int x, int y) {
    if (x < 0) { x = 0; }
    if (x >= m_numXCells) { x = m_numXCells; }
    if (y < 0) { y = 0; }
    if (y >= m_numYCells) { y = m_numYCells; }

    return &m_cells[y * m_numXCells + x];
//    return m_cells[x * (m_numXCells - 1) + y];
}

Cell* Grid::getCell(const glm::vec2& pos) {
    if (pos.x < 0) return &m_cells[0];
    if (pos.x >= m_width) return &m_cells[0];
    if (pos.y < 0) return &m_cells[0];
    if (pos.x >= m_height) return &m_cells[0];

    int cellX = static_cast<int>(pos.x / m_cellSize);
    int cellY = static_cast<int>(pos.y / m_cellSize);

    return getCell(cellX, cellY);
}

void Grid::addBall(Ball* ball) {
    Cell* cell = getCell(ball->position);
    addBall(ball, cell);
}

void Grid::addBall(Ball* ball, Cell* cell) {
    cell->balls.push_back(ball);
    ball->ownerCell = cell;
    ball->cellVectorIndex = cell->balls.size() - 1;
}

void Grid::removeBallFromCell(Ball* ball) {
    std::vector<Ball*>& balls = ball->ownerCell->balls;
    // Normal vector swap
    balls[ball->cellVectorIndex] = balls.back();
    balls.pop_back();
    // Update vector index
    if (ball->cellVectorIndex < balls.size()) {
        balls[ball->cellVectorIndex]->cellVectorIndex = ball->cellVectorIndex;
    }
    // Set the index of ball to -1
    ball->cellVectorIndex = -1;
    ball->ownerCell = nullptr;
}


