#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

//////////////////

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

std::string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰   ";
    case State::kPath: return "🚗  ";
    case State::kStart: return "🚦  ";
    case State::kFinish: return "🏁  ";
    default: return "0   "; 
  }
}

std::vector<State> ParseLine(const std::string& line)
{
    std::istringstream stream(line);

    int value;
    char comma;
    std::vector<State> vec;
    while (stream >> value >> comma && comma == ',')
    {
        switch (value)
        {
        case 0:
            vec.push_back(State::kEmpty);
            break;
        case 1:
            vec.push_back(State::kObstacle);
            break;
        }
    }

    return vec;
}

void PrintBoard(const std::vector<std::vector<State>>& board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j< board[i].size(); j++)
            std::cout << CellString(board[i][j]);

        std::cout << "\n";
    }

}

std::vector<std::vector<State>> ReadBoardFile(const char* path)
{
    std::ifstream myfile(path);
    std::vector<std::vector<State>> board;
    if(myfile)
    {
        std::string line;
        while(getline(myfile,line))
        {
            board.push_back(ParseLine(line));
        }
        return board;
    }

}

/////////////////////////////////

bool Compare(const std::vector<int>& a, const std::vector<int>& b) {
  int f1 = a[2] + a[3];
  int f2 = b[2] + b[3];
  return f1 > f2; 
}

bool CheckValidCell(const int& x, const int& y, std::vector<std::vector<State>>& grid) {
  bool on_grid_x = (x >= 0 && x < grid.size());
  bool on_grid_y = (y >= 0 && y < grid[0].size());
  if (on_grid_x && on_grid_y)
    return grid[x][y] == State::kEmpty;
  return false;
}

void CellSort(std::vector<std::vector<int>>* v) {
  std::sort(v->begin(), v->end(), Compare);
}

int Heuristic(const int& x1, const int& y1 ,const int& x2,const int& y2)
{
    return std::abs(x2-x1) + std::abs(y2-y1);
}

void AddToOpen(const int& x,const int& y,const int& g,const int& h, std::vector<std::vector<int>>& openlist, std::vector<std::vector<State>>& grid)
{
    openlist.push_back(std::vector<int> {x,y,g,h});
    grid[x][y] = State::kClosed;
}

void ExpandNeighbors (const std::vector<int>& curNode, const int goal[2],
                      std::vector<std::vector<int>>& openlist,
                      std::vector<std::vector<State>>& grid)
{
  int curX = curNode[0];
  int curY = curNode[1];
  int g = curNode[2];
  for (int i = 0; i < 4; i++) 
  {
    int nextX = curX + delta[i][0];
    int nextY = curY + delta[i][1];
    if ( CheckValidCell(nextX, nextY, grid) )
    {
      int h = Heuristic(nextX, nextY, goal[0], goal[1]);
      AddToOpen(nextX, nextY, g+1, h, openlist, grid);
    }
  }
}

std::vector<std::vector<State>> Search(std::vector<std::vector<State>>& grid, const int init[2], const int goal[2])
{
    std::vector<std::vector<int>> open {};


    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0],goal[1]);
    AddToOpen(x, y, g, h, open, grid);

    while(open.size())
    {
        CellSort(&open);
        auto current = open.back();
        open.pop_back();
        x = current[0];
        y = current[1];
        grid[x][y] = State::kPath;

        if (x == goal[0] && y == goal[1]) {
            grid[ init[0] ][ init[1] ] = State::kStart;
            grid[ goal[0] ][ goal[1] ] = State::kFinish;
            return grid;
        }
        
        ExpandNeighbors(current, goal, open, grid);
    }

    std::cout << "No Paths Found!" << "\n";

    return std::vector<std::vector<State>> {};
}

int main()
{
    int init[2] = {0, 0}; // or: int init[2]{0, 0}; or: int init[] = {0, 0}
    int goal[2] = {4, 5};
    auto board = ReadBoardFile("1.board");
    auto solution = Search(board,init,goal);
    PrintBoard(solution);
}