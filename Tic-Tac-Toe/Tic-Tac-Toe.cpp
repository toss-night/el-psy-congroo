#include <iostream>

class TicTacToe
{
public:
    unsigned char field[3][3];
    TicTacToe()
    {
        for (size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                field[i][j] = 254;
            }      
        }
    }
    
    void makeMove(char ch)
    {
        int row, col;      
        while(true)
        {
            std::cout << "enter col(1-3): ";
            std::cin >> col;
            std::cout << "enter row(1-3): ";
            std::cin >> row;
            if (row >= 1 && row <= 3 && col >= 1 && col <= 3)
            {
                if (field[row - 1][col - 1] == 254)
                {
                    field[row - 1][col - 1] = ch;
                    break;
                }
                else
                {
                    std::cout << "this place is already occupied, try again\n";                    
                }                
            }
            else
            {
                std::cout << "error, try again" << std::endl;                
            }
        }
    }
    void printBoard()
    {
        for (size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                std::cout << field[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    unsigned char checkWin()
    {
        for (int i = 0; i < 3; i++) {
            if (field[i][0] != 254 && field[i][0] == field[i][1] && field[i][1] == field[i][2])
            {
                return field[i][0];
            }
        }
        for (int j = 0; j < 3; j++) {
            if (field[0][j] != 254 && field[0][j] == field[1][j] && field[1][j] == field[2][j])
            {
                return field[0][j];
            }
        }       
        if (field[0][0] != 254 && field[0][0] == field[1][1] && field[2][2] == field[1][1])
        {
            return field[1][1];
        }
        if (field[0][2] != 254 && field[0][2] == field[1][1] && field[2][0] == field[0][2])
        {
            return field[1][1];
        }
        return 254;
    }
    bool isDraw()
    {
        if (checkWin() != 254) { return false; }
        for (size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 3; j++) 
            {
                if (field[i][j]==254)
                {
                    return false;
                }
            }
        }
        return true;
    }
};

void game(TicTacToe& a)
{   
    char player = 'x';
    while(true)
    {                     
        a.printBoard();
        std::cout << "move " << player << std::endl;
        a.makeMove(player);
        if (a.checkWin() != 254)
        {
            std::cout << "player \"" << a.checkWin() << "\" win" << "\n";
            break;
        }
        if (a.isDraw())
        {
            std::cout << "draw\n";
            break;
        }
        std::cout << std::endl;

        player = (player == 'x') ? 'o' : 'x';
    }
    std::cout << "\n";
    a.printBoard();
    
}

int main()
{
    TicTacToe a;   
    game(a);
}

