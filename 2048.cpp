#include<iostream>
#include<vector>
#include<time.h>
#include<stdlib.h>
using namespace std;

const int NEWTILE = 50;

struct board
{
  int arr[4][4];

};

class game
{
private:
  board *gameBoard;
  vector<board*> stack;
  //goes up by 1 each move
  int turnCount;
  //goes up by adding total of combined tiles
  int scoreCount;

public:
  game()
  {
    turnCount = 0;
    scoreCount = 0;
    gameBoard = new board;

    for(int i = 0; i <4; i++ )
    {
      for(int j =0; j<4; j++)
      {
        gameBoard->arr[i][j] = 0;
      }
    }
    addTile();

    stack.push_back(gameBoard);
  }

  int newTile()
  {
    int randTile;
    srand(time(NULL));

    int x = (rand() %100);
    //creates 50 percent chance for 2 or 4
    if (x < NEWTILE)
    {
      randTile = 4;
    }
    else
    {
      randTile = 2;
    }
    return randTile;
  }



  void addTile()
  {
    board*temp = new board;
    temp = gameBoard;

    pair<int,int> coordinates;
    vector<pair<int,int> > pairs;
    //get random 2 or 4 for new tile
    int randNum = newTile();

    //find empty tiles
    for(int i = 0; i < 4; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        if(temp->arr[i][j] == 0)
        {
          coordinates = make_pair(i,j);
          pairs.push_back(coordinates);
        }
      }
    }

    srand(time(NULL));
    //get random tile in vector of pairs
    int randTile = (rand() & pairs.size());

    temp->arr[pairs[randTile].first][pairs[randTile].second] = randNum;

    gameBoard = temp;
    stack.push_back(temp);
    pairs.clear();


  }

  void display()
  {
    board *temp = gameBoard;
    for (int i =0; i < 4; i++)
    {
      for (int j =0; j < 4; j++)
      {
        cout<< temp->arr[i][j] << " ";

      }
      cout <<endl;
    }

  }

  void moveUp()
  {
    board *temp = new board;
    temp = gameBoard;

    for(int i = 0; i < 4; i++) //row = up & down
    {
      for(int j = 0; j < 4; j++) // column = left & right
      {
        //parse board bottom to top
        if(temp->arr[j][i]==0)
        {

          for(int k = j+1; k < 4; k++)
          {
            //if tile above is not empty swap with tile below
            if(temp->arr[k][i]!=0)
            {

              temp->arr[j][i] = temp->arr[k][i];
              //set tile in column below to zero
              temp->arr[k][i] = 0;
              break;
            }

          }
        }

      }
    }
    //merge the column below to column above
    for(int i =0; i < 4; i++)
    {
      for(int j=0; j < 4; j++)
      {
        //merge tile above and swap with tile below
        if((temp->arr[j][i]!=0)&&(temp->arr[j][i] == temp->arr[j+1][i]))
        {
          temp->arr[j][i] *=2;
          temp->arr[j+1][i] = 0;
          scoreCount += temp->arr[j][i];

        }
      }
    }


    gameBoard = temp;

    stack.push_back(temp);


  }
  void moveDown()
  {
    board *temp = new board;
    temp = gameBoard;

    for(int i = 0; i < 4; i++) //row = up & down
    {
      for(int j = 0; j < 4; j++) // column = left & right
      {
        //parse board from bottom to top
        if(temp->arr[j][i]==0)
        {
          //find tile below
          for(int k = j-1; k < 4; k++)
          {
            //if tile below is not empty swap with top tile
            if(temp->arr[k][i]!=0)
            {
              temp->arr[j][i] = temp->arr[k][i];
              temp->arr[k][i] = 0;
            }

          }
        }

      }
    }

    for(int i =0; i < 4; i++)
    {
      for(int j=0; j < 4; j++)
      {
        //if tile below is not empty merge and swap tiles
        if((temp->arr[j][i]!=0)&&(temp->arr[j][i] == temp->arr[j-1][i]))
        {
          temp->arr[j][i] *=2;
          temp->arr[j-1][i] = 0;
          scoreCount += temp->arr[j][i];

        }
      }
    }


    gameBoard = temp;

    stack.push_back(temp);



  }
  void moveLeft()
  {
    board *temp = new board;
    temp = gameBoard;

      for(int i = 0; i < 4; i++) // row
      {
        for(int j = 0; j < 4; j++) // column
        {
          //parse board from right to left
          if(temp->arr[i][j]==0)
          {
            //if right tile is not empty swap with left tile
            for(int k = j+1; k < 4; k++)
            {

              if(temp->arr[i][k]!=0)
              {
                temp->arr[i][j] = temp->arr[i][k];
                temp->arr[i][k] = 0;
                break;
              }

            }
          }

        }
      }
      for(int i =0; i < 4; i++)
      {
        for(int j=0; j < 4 -1; j++)
        {
          if((temp->arr[i][j]!=0)&&(temp->arr[i][j] == temp->arr[i][j+1]))
          {
            temp->arr[i][j] *=2;
            temp->arr[i][j+1] = 0;
            scoreCount += temp->arr[i][j];

          }
        }
      }

      gameBoard = temp;

      stack.push_back(temp);

  }
  void moveRight()
  {
    board *temp = new board;
    temp = gameBoard;

      for(int i = 0; i < 4; i++) // row
      {
        for(int j = 4 -1; j >=0; j--) // column
        {
          //if tile is empty shift column to the right
          if(temp->arr[i][j]==0)
          {
            //parse board from righ to left
            for(int k = j-1; k >=0; k--)
            {

              //if not an empty tile, swap with right tile
              if(temp->arr[i][k]!=0)
              {
                temp->arr[i][j] = temp->arr[i][k];
                temp->arr[i][k] = 0;
                break;
              }

            }
          }

        }
      }
      //parse from righ to left
      for(int i =0; i < 4; i++)
      {
        for(int j=4-1; j >=0; j--)
        {
          //current tile is not empty and current tile is equal to tile to the left
          if((temp->arr[i][j]!=0)&&(temp->arr[i][j] == temp->arr[i][j-1]))
          {
            //add tiles, swap tile
            temp->arr[i][j] *=2;
            temp->arr[i][j-1] = 0;
            scoreCount += temp->arr[i][j];

          }
        }
      }

      gameBoard = temp;

      stack.push_back(temp);

  }



  void moveTile(char &move)
  {

    switch(move)
    {
      //move up
      case 'w':
      moveUp();
      turnCount++;
      break;

      //move left
      case 'a':
      moveLeft();
      turnCount++;
      //move down
      case 's':
      moveDown();
      turnCount++;
      break;
      //move right
      case 'd':
      moveRight();
      turnCount++;
      break;
  }
}




  bool isWin()
  {
    board *temp = gameBoard;
    for(int i =0; i < 4; i++)
    {
      for(int j =0; j <4; j++)
      {
        if (temp->arr[i][j] == 2048)
        {
          return false;
        }
      }
    }
    return true;
  }

  bool isLoose()
  {
    board *temp = gameBoard;
    for(int i =0; i < 4; i++)
    {
      for(int j =0; j <4; j++)
      {
        if (temp->arr[i][j] == 0)
        {
          return true;
        }
      }
    }
    return false;
  }
  void undo()
  {

    board *temp = new board;
    //get last board from turnCount
    turnCount--;
    if(turnCount >=0)
    {

      //remove last board from stack
      stack.pop_back();


      temp = stack.at(turnCount);

      //stack.at(turnCount)->arr[i][j];


      gameBoard = temp;
      stack.push_back(temp);
    }



  }
  void turn()
  {
    char userInput;
    while(isLoose())
    {
      if(!isWin())
      {
        cout<<"congratulations!" << endl;
        break;
      }
      else
      {
        display();
        cin>>userInput;
        if(userInput == 'u')
        {
          undo();
        }
        moveTile(userInput);

        addTile();
        cout <<"score: " << scoreCount << endl;
        cout << "turn: " << turnCount << endl;

      }
    }
    cout << "you lost, better luck next time" << endl;
  }
};

int main()
{
  game();
  game g;

  cout <<"enter w, a, s, d, u for up, left, down, right, undo" << endl;
  g.turn();

}
