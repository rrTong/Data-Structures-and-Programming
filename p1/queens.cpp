//
//queens.cpp
//

//Classes
#include <iostream> //for cout

class Queens
{
private:
    int solution[9] = {};
    bool notEaten(int rows, int cols);
    bool isDone();
public:
    void getSol(int rows, int cols);
};

int main()
{
    Queens queens;
    int row = 1;
    int col = 1;

    queens.getSol(row, col);
    return 0;
}

void Queens::getSol(int rows, int cols)
{
    while(!isDone())
    {
        if(rows > 8)
        {
            solution[cols] = 0;
            cols = cols - 1;
            rows = solution[cols] + 1;
        }
        if(notEaten(rows, cols))
        {
            solution[cols] = rows;
            cols = cols + 1;
            rows = 1;
        }
        else
        {
            rows = rows + 1;
            if(rows > 8)
            {
                solution[cols] = 0;
                cols = cols - 1;
                rows = solution[cols] + 1;
            }
        }
    }
    for(int i = 1; i < 9; i++)
    {
        std::cout << solution[i];
        if(i == 8)
            std::cout << ' ';
        else
            std::cout << ',';
    }
    std::cout << std::endl;
}

bool Queens::isDone()
{
    for(int i = 1; i <= 9; i++)
        if(solution[i] == 0)
            return false;
    return true;
}

bool Queens::notEaten(int rows, int cols)
{
    for(int i = 1; i < cols; i++)
        if(rows == solution[i])
            return false;
        else if (rows == solution[i] + (cols - i))
            return false;
        else if (rows == solution[i] + (i - cols))
            return false;
    return true;
}

