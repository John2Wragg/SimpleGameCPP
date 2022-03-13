//
//  main.cpp
//  Snake_Game
//
//

#include <iostream>
#include <conio.h> // Windows library only.
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x,y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail; //length of tail
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir; // This holds the direction of the snake.
bool hasPrinted = false; // used later in printing the tail.


void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2; // This centres the snake at the start
    y = height / 2;
    fruitX = rand() % width; // random placement of fruit
    fruitY = rand() % height;
    score = 0; // initalising score to 0 at start
    
}
void Draw()
{
    system("cls"); // to clear terminal at start of game
    
    for (int i = 0; i<width+1; i++){ // Printing top line of map.
        std::cout << "#";
        
    }
    cout << endl; // move to next line.
    
    // printing perimeter
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j==0) // first character
                cout << "#";
            if (j == x && i == y)
                cout << "O"; // printing head of snake
            else if (i == fruitY && j == fruitX)
                cout << "F"; // printing fruit.
            else
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // if current x and current y co-ordinate equal the tail cordinates. Then we print the tail.
                        hasPrinted = true; // stating we have printed the tail
                    }

                }
                if (!hasPrinted) // if we didn't print the tail, then print a blank space.
                {
                    cout << " ";
                }
           
                
            if (j == width-1)
                cout << "#";
                
        }
        cout << endl; // move to next line
    }
    
    
    
    for (int i = 0; i<width+1; i++){ // printing bottom line / wall.
    cout << "#";
    }
    
    cout << "Score: " << score << endl;
    
    
    
    
    
    
}
void Input() // getting player input "WASD" keys. Note: only works on windows.
{
    if (_kbhit()) // checks whether the keyboard button is pressed.
    {
        switch (_getch()) // gets the code of the key which is pressed.
        {
            case "a":
                dir = LEFT;
                break;
            case "d":
                dir = RIGHT;
                break;
            case "s":
                dir = DOWN;
                break;
            case "w":
                dir = UP;
                break;
            case "x":
                gameOver = true;
                break;
            
                
        }
    }
}
void Logic()
{
    int prevX = tailX[0]; // previous co-ordinates of tail.
    int prevY = tailY[0];
    
    int prev2X, prev2Y;
    tailX[0] = x; // setting the first element to follow the head of the snake.
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) // creating movement of the tail.
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    switch (dir)
    {
        case LEFT: // If press left then take 1 off the x co-ordinate.
            x--;
            break;
        case RIGHT: // if right, add 1 to x co-ordinate.
            x++;
            break;
        case UP:// add 1 to y co-ordinate
            y++;
            break;
        case DOWN: //subtract 1 from y co-ordinate
            y--;
            break;
        default:
            break;
            
    }
//    if (x > width || x < 0 || y > height || y < 0){
//        gameOver= true; // if exit the map, then game over.
//    }
    
    // Alternate view: snake can move from right to left going through walls. Uncomment above to change game structure to end game when hit a wall.
    if (x >= width) // if x exceeeds the width, then reposition x coordinate to 0.
    {
        x = 0;
    } else if (x < 0) // if x moves less than 0, then reposition x to the width - 1 (as the width itself is the barrier).
    {
        x = width - 1;
    }
    
    if (y >= height)
    {
        y = 0;
    }else if (y < 0)
    {
        y = height - 1;
    }
    
    // End game if snake hits itself.
    for (int i = 0; i<nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y) // x coordinate and y coordinate = tail coordinates.
        {
            gameOver = true;
        }
    }
    
    
    if (x == fruitX && y == fruitY) // if you collide with the fruit, increase score and reposition the fruit. Increase the tail length.
    {
        
        score += 10;
        fruitX = rand() % width; // random placement of fruit again after eaten
        fruitY = rand() % height;
        nTail ++; // increating tail length by 1
        
    }
        
    
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        
    }

}
