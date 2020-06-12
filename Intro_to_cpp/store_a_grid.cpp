#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

enum class State {kEmpty,kObstacle};

std::string CellString(const State& state)
{
    switch (state)
    {
    case State::kEmpty:
        return "0   ";
        break;
    case State::kObstacle:
        return "⛰   ";
        break;  
    default:
        break;
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


int main()
{
    /*
    std::vector<std::vector<int>> board = {{0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0}};
    */
    auto board = ReadBoardFile("1.board");

    PrintBoard(board);



}