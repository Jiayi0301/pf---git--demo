// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T11L
// Names: CHAI DI SHENG | LEONG JIA YI
// IDs: 1211101961 | 1211101506
// Emails: 1211101961@student.mmu.edu.my | 1211101506@student.mmu.edu.my
// Phones: 0108940336 |  0179882201
// *********************************************************

// TODO: Fill in the missing information above and delete this line.

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
using namespace std;

class Board
{
private:
    vector<vector<char>> map_; // convention to put trailing underscore

public:
    int dimX_, dimY_;
    Board(); // Defult Board Settings
    Board(int dimX, int dimY);

    void init(int dimX, int dimY); // Problems : how to change this value
    void display() const;
    int getDimX() const;
    int getDimY() const;
    char getObject(int x, int y) const;
    void setObject(int x, int y, char ch);
};

class Alien
{
private:
    char symbol;
    int x_, y_;
    int health, attack;

public:
    Alien();
    Alien(int x, int y, char chAlien);

    int getX() const;
    int getY() const;
    int getHealth() const;
    int getAttack() const;

    void moveLeft(Board &game);
    void moveRight(Board &game);
    void moveUp(Board &game);
    void moveDown(Board &game);
};

Board::Board() // DEMO !!! Default Game Settings Rows : 5 Columns : 9
{
    int dimX = 9;
    int dimY = 5;
    init(dimX, dimY);
}

Board::Board(int dimX, int dimY)
{
    init(dimX, dimY);
}

int Board::getDimX() const
{
    return dimX_;
}

int Board::getDimY() const
{
    return dimY_;
}

void Board::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', '<', '>', '^', 'h', 'r', 'p', 'v'};
    int noOfObjects = 14; // number of objects in the objects array
    // create dynamic 2D array using vector
    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }
    // put random characters into the vector array
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void Board::setObject(int x, int y, char ch)
{
    map_[dimY_ - y][x - 1] = ch;

}

Alien::Alien(int x, int y, char chAlien) // make object Alien and specify its coordinates
{
    symbol = chAlien;
    x_ = x;
    y_ = y;
}

int Alien::getX() const
{
    return x_;
}

int Alien::getY() const
{
    return y_;
}

void Alien::moveLeft(Board &game)
{
    int x = getX();
    int y = getY();

    char chTrail = '.';
    game.setObject(x, y, chTrail); // places trail at the current alien's position

    x_ = x - 1;
    game.setObject(x_, y_, symbol); // place alien at next position
}

void Alien::moveRight(Board &game)
{
    int x = getX();
    int y = getY();

    char chTrail = '.';
    game.setObject(x, y, chTrail); // places trail at the current alien's position

    x_ = x + 1;
    game.setObject(x_, y_, symbol); // place alien at next position
}

void Alien::moveUp(Board &game)
{
    int x = getX();
    int y = getY();

    char chTrail = '.';
    game.setObject(x, y, chTrail); // places trail at the current alien's position

    y_ = y + 1;
    game.setObject(x_, y_, symbol); // place alien at next position
}

void Alien::moveDown(Board &game)
{
    int x = getX();
    int y = getY();

    char chTrail = '.';
    game.setObject(x, y, chTrail); // places trail at the current alien's position

    y_ = y - 1;
    game.setObject(x_, y_, symbol); // place alien at next position
}

// Problems : The Alien and zombie information
void Board::display() const
{
    // comment this out during testing
    // system("cls");
    cout << "Alien vs Zombie :.      " << endl;

    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << "  ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (dimY_ - i);
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

void displayMenu()
{
    // system("cls");
    char settings;
    cout << "Default Game Settings" << endl;
    cout << "---------------------" << endl;
    cout << "Board Rows   : 5" << endl;
    cout << "Board Colums : 9" << endl;
    cout << "Zombie Count : 1" << endl;

    cout << "Do you wish to change the game settings (y/n)? => ";
}

// Display Board Settings
// Problems : when settings updated how to go back board & how to change the settings
// void changeDataMenu(int& ncolumn, int& nrow, int& nzombies)
// {
//     cout << "Board Settings  " << endl;
//     cout << "----------------" << endl;
//     cout << "Enter rows => ";
//     cin >> nrow;
//     while (cin.fail() && nrow % 2 == 0)
//     {
//         cin.clear();
//         cin.ignore();
//         cout << "Please enter a odd number." << endl;
//         cout << "Enter rows => ";
//         cin >> nrow;
//     }

//     cout << "Enter columns => ";
//     cin >> ncolumn;
//     while (cin.fail() && ncolumn % 2 == 0)
//     {
//         cin.clear();
//         cin.ignore();
//         cout << "Please enter a odd number." << endl;
//         cout << "Enter rows => ";
//         cin >> ncolumn;
//     }

//     cout << "Zombie Settings " << endl;
//     cout << "----------------" << endl;
//     cout << "Enter number of zombies => ";
//     cin >> nzombies;
//     while (cin.fail())
//     {
//         cin.clear();
//         cin.ignore();
//         cout << "Please enter a number." << endl;
//         cout << "Enter number of zombies => ";
//         cin >> nzombies;
//     }

//     cout << "Settings Updated." << endl;
// }

void ChangeData(int &nrow, int &ncolumn, int &nzombie)
{
    cout << "Board Settings  " << endl;
    cout << "----------------" << endl;

    // Change the rows //
    cout << "Enter rows => ";
    cin >> nrow;
    while (true)
    {
        if (!cin)
        {
            cout << "Please enter odd numbers only" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter rows => ";
            cin >> nrow;
        }
        if (nrow % 2 == 0)
        {
            cout << "Please enter odd numbers only" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter rows => ";
            cin >> nrow;
        }
        if (nrow < 3)
        {
            cout << "Please enter odd numbers greater or equal to 3" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter rows => ";
            cin >> nrow;
        }
        if (nrow > 29)
        {
            cout << "Maximum number of rows is 29" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter rows => ";
            cin >> nrow;
        }
        else
            break;
    }

    // Change the Columns //
    cout << "Enter columns => ";
    cin >> ncolumn;
    while (true)
    {
        if (!cin)
        {
            cout << "Please enter odd numbers only" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter columns => ";
            cin >> ncolumn;
        }
        if (ncolumn % 2 == 0)
        {
            cout << "Please enter odd numbers only" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter columns => ";
            cin >> ncolumn;
        }
        if (ncolumn < 8)
        {
            cout << "Please enter odd numbers greater or equal to 9" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter columns => ";
            cin >> ncolumn;
        }
        if (ncolumn > 29)
        {
            cout << "Maximum number of columns is 29" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter columns => ";
            cin >> ncolumn;
        }
        else
            break;
    }

    // Change the Zombies //
    cout << "" << endl;
    cout << "Zombie Settings  " << endl;
    cout << "----------------" << endl;

    cout << "Enter number of zombies => ";
    cin >> nzombie;
    while (true)
    {
        if (!cin)
        {
            cout << "Please enter numbers only" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter number of zombies => ";
            cin >> nzombie;
        }
        if (nzombie <= 0)
        {
            cout << "Please enter positive numbers only and greater than 0" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter number of zombies => ";
            cin >> nzombie;
        }
        if (nzombie > 9)
        {
            cout << "Maximum number of zombies is 9" << endl;
            cin.clear();
            cin.ignore();
            cout << "Enter number of zombie => ";
            cin >> nzombie;
        }
        else
            break;
    }

    cout << "" << endl;
    cout << "Settings Updated." << endl;
}

// The Alien Place  DEMO !!!
// Problems : Problems of Zombie place

int main()
{
    // srand(1); // use this for fixed map during testing
    srand(time(NULL)); // try this for random map

    string settings;
    displayMenu();
    cin >> settings;

    if (settings == "y" | settings == "Y")
    {
        int row, column, zombie;
        // changeDataMenu(x, y, z);
        ChangeData(row, column, zombie);

        Board game(column, row);

        int x1, y1;
        x1 = row / 2 + 2;
        y1 = column / 2 + 0.5;
        char ch1 = 'A';
        game.setObject(x1, y1, ch1);
        Alien player1(x1, y1, ch1);

        for (int i = 1; i <= zombie; i++) // puts zombies into the map
        {
            int X_ = game.getDimX();
            int Y_ = game.getDimY();

            int x2 = rand() % (X_ + 1);
            int y2 = rand() % (Y_ + 1);

            while (x2 == x1 & y2 == y1)
            {
                int x2 = rand() % (X_ + 1);
                int y2 = rand() % (Y_ + 1);
            }

            char ch2 = i + '0';
            game.setObject(x2, y2, ch2);
        }

        game.display();

        // while (true)
        {
            string command;
            cout << "Command => ";
            cin >> command;

            if (command == "up")
            {
                player1.moveUp(game);
                game.display();
                system("pause");
                // continue;
            }

            else if (command == "down")
            {
                player1.moveDown(game);
                game.display();
                system("pause");
                // continue;
            }

            else if (command == "left")
            {
                player1.moveLeft(game);
                game.display();
                system("pause");
                // continue;
            }

            else if (command == "right")
            {
                player1.moveRight(game);
                game.display();
                system("pause");
                // continue;
            }

            else if (command == "arrow")
            {
            }

            else if (command == "help")
            {
                cout << endl
                     << "Commands" << endl
                     << "1. up      - Move up." << endl
                     << "2. down    - Move down." << endl
                     << "3. left    - Move left." << endl
                     << "4. right   - Move right." << endl
                     << "5. arrow   - Change the direction of the arrow." << endl
                     << "6. help    - Display this user commands." << endl
                     << "7. save    - Save the game." << endl
                     << "8. load    - Load a game." << endl
                     << "9. quit    - Quit the game." << endl
                     << endl;
                system("pause");
                // continue;
            }

            // else if (command == "save")
            // {

            // }

            // else if (command == "load")
            // {

            // }

            else if (command == "quit")
            {
            }

            else
            {
                cout << "Please enter a correct selection!" << endl
                     << endl;
                // continue;
            }
        }
    }

    else if (settings == "n" | settings == "N")
    {
        Board game;
        int x1 = 5, y1 = 3;
        char ch1 = 'A';
        game.setObject(x1, y1, ch1);
        Alien player1(x1, y1, ch1);

        for (int i = 1; i <= 1; i++)
        {
            int X_ = game.getDimX();
            int Y_ = game.getDimY();

            int x2 = rand() % (X_ + 1);
            int y2 = rand() % (Y_ + 1);

            while (x2 == x1 & y2 == y1)
            {
                int x2 = rand() % (X_ + 1);
                int y2 = rand() % (Y_ + 1);
            }

            char ch2 = i + '0';
            game.setObject(x2, y2, ch2);
        }

        game.display();
        while (true)
        {
            string command;
            cout << "Command => ";
            cin >> command;

            if (command == "up")
            {
                player1.moveUp(game);
                game.display();
                system("pause");
                continue;
            }

            else if (command == "down")
            {
                player1.moveDown(game);
                game.display();
                system("pause");
                continue;
            }

            else if (command == "left")
            {
                player1.moveLeft(game);
                game.display();
                system("pause");
                continue;
            }

            else if (command == "right")
            {
                player1.moveRight(game);
                game.display();
                system("pause");
                continue;
            }

            // else if (command == "arrow")
            // {

            // }

            else if (command == "help")
            {
                cout << endl
                     << "Commands" << endl
                     << "1. up      - Move up." << endl
                     << "2. down    - Move down." << endl
                     << "3. left    - Move left." << endl
                     << "4. right   - Move right." << endl
                     << "5. arrow   - Change the direction of the arrow." << endl
                     << "6. help    - Display this user commands." << endl
                     << "7. save    - Save the game." << endl
                     << "8. load    - Load a game." << endl
                     << "9. quit    - Quit the game." << endl;
                system("pause");
                game.display();
                continue;
            }

            // else if (command == "save")
            // {

            // }

            // else if (command == "load")
            // {

            // }

            else if (command == "quit")
            {
            }

            else
            {
                cout << "Please enter a correct selection!" << endl
                     << endl;
                continue;
            }
        }
    }

    else
    {
        cout << "Please enter in only character (y/n)" << endl;
        displayMenu();

        
    }
}
