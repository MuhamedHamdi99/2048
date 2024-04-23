#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>
#include <SFML/Audio.hpp>

using namespace std;

struct player  // struct to store player information
{
    string name;
    int score,bigTile;
};

int board[4][4]={};
int tempBoard[4][4]={}; // Temporary board for the step back function
int lastBoard[4][4]={};  // stores the last board for the step back function
bool moved=0; // checks if the board has changed
int bigTile=0; // stores the biggest tile in the board
int score;  // stores the score
bool won=0; // show if player has won
bool cont=0;        // shows if the player want to continue
int mode=0;     // stores the selected mode
player playerArr[6]; // array for players info

void newGame();         // initialize the game board, score, big tile, etc...
void getLeaderboard();      //get the stored info from the files
void outLeaderboard(string textInput); // output the info to files
void newValue();        // get a new value on the board
void newGameValue();           // get a new value on the board (only on the game beginning)
void draw();        // updates the view
void drawLeaderboard();         // draw leader board window
void drawPlayer();      // draw player window
void drawLevel();       // draw level window
void drawOther(int windowSelect); // // draw other windows
void tempToLast();  // transfer board to another
void boardToTemp();
void lastToBoard();
void lastToTemp();
void change(int n); // moves the tiles
void combine(int n);        // combine the matched tiles
bool lose();        // check if the player lost
bool win();         // check if he won
bool boardIsFull();     //check if board is full
bool comparePlayers(player a,player b); // help in sorting players

        // initialization
    sf::RenderWindow window(sf::VideoMode(1280, 720), "2048",sf::Style::Fullscreen);
    sf::Texture bgtexture;
    sf::Texture leaderboardtexture;
    sf::Texture playerbgtexture;
    sf::Texture losebgtexture;
    sf::Texture winbgtexture;
    sf::Texture gameoverbgtexture;
    sf::Texture splashtexture;
    sf::Texture leveltexture;
    sf::Texture tiletext2;
    sf::Texture tiletext4;
    sf::Texture tiletext8;
    sf::Texture tiletext16;
    sf::Texture tiletext32;
    sf::Texture tiletext64;
    sf::Texture tiletext128;
    sf::Texture tiletext256;
    sf::Texture tiletext512;
    sf::Texture tiletext1024;
    sf::Texture tiletext2048;
    sf::Texture tiletext4096;
    sf::Texture tiletext8192;
    sf::Texture tiletext16384;
    sf::Sprite bg;
    sf::Sprite leaderboard;
    sf::Sprite playerbg;
    sf::Sprite losebg;
    sf::Sprite winbg;
    sf::Sprite gameoverbg;
    sf::Sprite splash;
    sf::Sprite level;
    sf::Sprite tile2;
    sf::Sprite tile4;
    sf::Sprite tile8;
    sf::Sprite tile16;
    sf::Sprite tile32;
    sf::Sprite tile64;
    sf::Sprite tile128;
    sf::Sprite tile256;
    sf::Sprite tile512;
    sf::Sprite tile1024;
    sf::Sprite tile2048;
    sf::Sprite tile4096;
    sf::Sprite tile8192;
    sf::Sprite tile16384;
    sf::Text scoreAsText;
    sf::Text bigTileAsText;
    sf::Text bestAsText;
    sf::Text playerName[5];
    sf::Text playerScoreAsText[5];
    sf::Text playerBigTileAsText[5];
    sf::Font font;
    sf::Text textToDisplay;
    sf::SoundBuffer bsw,bsl,bsp;
    sf::Sound sound,sound1,sound2;

int main()
{
    long long time1 = time(NULL);
    long long lastTime = 0;
    int windowSelect=0;
    int windowlastSelected=0;
    srand(time(NULL));
    if (!(          // load files
    leveltexture.loadFromFile("level.png")&&
    splashtexture.loadFromFile("Splash.png")&&
    gameoverbgtexture.loadFromFile("over.png")&&
    losebgtexture.loadFromFile("lost.png")&&
    winbgtexture.loadFromFile("won.png")&&
    playerbgtexture.loadFromFile("Player.png")&&
    leaderboardtexture.loadFromFile("Leaderboard.png")&&
    bgtexture   .loadFromFile("bg.png")      &&
    tiletext2   .loadFromFile("Tile2.png")   &&
    tiletext4   .loadFromFile("Tile4.png")   &&
    tiletext8   .loadFromFile("Tile8.png")   &&
    tiletext16  .loadFromFile("Tile16.png")  &&
    tiletext32  .loadFromFile("Tile32.png")  &&
    tiletext64  .loadFromFile("Tile64.png")  &&
    tiletext128 .loadFromFile("Tile128.png") &&
    tiletext256 .loadFromFile("Tile256.png") &&
    tiletext512 .loadFromFile("Tile512.png") &&
    tiletext1024.loadFromFile("Tile1024.png")&&
    tiletext2048.loadFromFile("Tile2048.png")&&
    tiletext4096.loadFromFile("Tile4096.png")&&
    tiletext8192.loadFromFile("Tile8192.png")&&
    tiletext16384.loadFromFile("Tile16384.png")
          ))
        return EXIT_FAILURE;
        //load sound
    if(!((bsw.loadFromFile("win.wav"))&&(bsl.loadFromFile("lose1.wav"))&&(bsp.loadFromFile("nova.wav"))))
    {
        return EXIT_FAILURE;
    }
    sound.setBuffer(bsw);
    sound1.setBuffer(bsl);
    sound2.setBuffer(bsp);
    /*setTextures for every file we upload */
    level.setTexture(leveltexture);
    splash.setTexture(splashtexture);
    playerbg.setTexture(playerbgtexture);
    losebg.setTexture(losebgtexture);
    winbg.setTexture(winbgtexture);
    gameoverbg.setTexture(gameoverbgtexture);
    leaderboard.setTexture(leaderboardtexture);
    bg.setTexture(bgtexture);
    tile2.setTexture(tiletext2);
    tile4.setTexture(tiletext4);
    tile8.setTexture(tiletext8);
    tile16.setTexture(tiletext16);
    tile32.setTexture(tiletext32);
    tile64.setTexture(tiletext64);
    tile128.setTexture(tiletext128);
    tile256.setTexture(tiletext256);
    tile512.setTexture(tiletext512);
    tile1024.setTexture(tiletext1024);
    tile2048.setTexture(tiletext2048);
    tile4096.setTexture(tiletext4096);
    tile8192.setTexture(tiletext8192);
    tile16384.setTexture(tiletext16384);

    //load font
    if (!font.loadFromFile("comicbd.ttf"))
        return EXIT_FAILURE;
    scoreAsText.setPosition(265,435);
    scoreAsText.setColor(sf::Color::White);
    scoreAsText.setFont(font);
    scoreAsText.setCharacterSize(48);
    bigTileAsText.setPosition(345,125);
    bigTileAsText.setColor(sf::Color::White);
    bigTileAsText.setFont(font);
    bigTileAsText.setCharacterSize(74);
    textToDisplay.setFont(font);
    textToDisplay.setColor(sf::Color::White);
    textToDisplay.setPosition(90,235);
    textToDisplay.setCharacterSize(86);
    string textInput="";
        int arrow=0;  // shows for the direction
        window.clear(); // clear the screen
        window.draw(splash);
        window.display();
        sf::sleep(sf::milliseconds(3000)); // sleep for 3 sec
        while (window.isOpen()&& win()) // game loop
    {
        time1 = time(NULL); // get the time
        arrow=0;
        sf::Event event;        // pull events
        while (window.pollEvent(event))
        {
            // Window close button or escape key is pressed: it will exit
            if ((event.type == sf::Event::Closed) ||
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }
            if (event.type == sf::Event::KeyPressed) // check for direction
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Up: arrow=1;
                    break;
                    case sf::Keyboard::Down: arrow=2;
                    break;
                    case sf::Keyboard::Right: arrow=3;
                    break;
                    case sf::Keyboard::Left: arrow=4;
                    break;
                }

            }
            if (event.type == sf::Event::TextEntered && windowSelect==0) // gets player name
                {
                    if (event.text.unicode >= 32 && event.text.unicode <= 128 && event.text.unicode!=' ' && textInput.length()<=10)
                    {
                        textInput += static_cast<char> (event.text.unicode);
                        textToDisplay.setString(textInput);
                    }
                    else if (event.text.unicode == 8 && textInput.length()>0) // deletes if the press backspace
                    {
                        textInput.erase (textInput.length()-1);
                        textToDisplay.setString(textInput);
                    }
                }
            if (event.type == sf::Event::MouseButtonPressed&&
                event.mouseButton.button == sf::Mouse::Left)            //shows where mouse is clicked
            {
                if  ((((sf::Mouse::getPosition(window).x >= 60 && sf::Mouse::getPosition(window).x <= 285)&&
                    (sf::Mouse::getPosition(window).y >= 540 && sf::Mouse::getPosition(window).y <= 640)))&&
                    (windowSelect==2)) //when you press in that place it will active newGame
                        {
                            newGame();
                        }
                if  ((((sf::Mouse::getPosition(window).x >= 266 && sf::Mouse::getPosition(window).x <= 331)&&
                    (sf::Mouse::getPosition(window).y >= 140 && sf::Mouse::getPosition(window).y <= 205)))&&
                    ((windowSelect==2) || (windowSelect==3) || (windowSelect==4)))
                        {
                            sound1.stop();
                            sound.stop();
                            lastToBoard();
                            lastToTemp();
                            windowSelect=2;
                        }
                if  ((((sf::Mouse::getPosition(window).x >= 60 && sf::Mouse::getPosition(window).x <= 285)&&
                    (sf::Mouse::getPosition(window).y >= 540 && sf::Mouse::getPosition(window).y <= 640))||
                    ((sf::Mouse::getPosition(window).x >= 640 && sf::Mouse::getPosition(window).x <= 1215)&&
                    (sf::Mouse::getPosition(window).y >= 72 && sf::Mouse::getPosition(window).y <= 647)))&&
                    (windowSelect==4))
                        {
                            sound1.stop();
                            newGame();
                            windowSelect=2;

                        }
                if  ((((sf::Mouse::getPosition(window).x >= 60 && sf::Mouse::getPosition(window).x <= 285)&&
                    (sf::Mouse::getPosition(window).y >= 540 && sf::Mouse::getPosition(window).y <= 640)))&&
                    (windowSelect==3))
                        {
                            sound1.stop();
                            sound.stop();
                            newGame();
                            windowSelect=2;

                        }
                if  (((sf::Mouse::getPosition(window).x >= 640 && sf::Mouse::getPosition(window).x <= 1215)&&
                    (sf::Mouse::getPosition(window).y >= 72 && sf::Mouse::getPosition(window).y <= 647))&&
                    (windowSelect==3))
                        {
                            sound.stop();
                            windowSelect=2;
                            cont=1;
                        }
                if  (((sf::Mouse::getPosition(window).x >= 310 && sf::Mouse::getPosition(window).x <= 565)&&
                    (sf::Mouse::getPosition(window).y >= 540 && sf::Mouse::getPosition(window).y <= 640))&&
                    ((windowSelect==2) || (windowSelect==3) || (windowSelect==4)))
                        {
                            windowlastSelected=windowSelect;
                            windowSelect=1;
                        }
                if  (((sf::Mouse::getPosition(window).x >= 515 && sf::Mouse::getPosition(window).x <= 765)&&
                    (sf::Mouse::getPosition(window).y >= 570 && sf::Mouse::getPosition(window).y <= 670))&&
                    (windowSelect==1))
                        {
                            windowSelect=windowlastSelected;
                        }
                if  (((sf::Mouse::getPosition(window).x >= 352 && sf::Mouse::getPosition(window).x <= 936)&&
                    (sf::Mouse::getPosition(window).y >= 230 && sf::Mouse::getPosition(window).y <= 355))&&
                    (windowSelect==5))
                        {
                            mode=1;
                            newGame();
                            getLeaderboard();
                            windowSelect=2;
                        }
                if  (((sf::Mouse::getPosition(window).x >= 352 && sf::Mouse::getPosition(window).x <= 936)&&
                    (sf::Mouse::getPosition(window).y >= 375 && sf::Mouse::getPosition(window).y <= 500))&&
                    (windowSelect==5))
                        {
                            mode=2;
                            newGame();
                            getLeaderboard();
                            windowSelect=2;
                        }
                if  (((sf::Mouse::getPosition(window).x >= 352 && sf::Mouse::getPosition(window).x <= 936)&&
                    (sf::Mouse::getPosition(window).y >= 520 && sf::Mouse::getPosition(window).y <= 645))&&
                    (windowSelect==5))
                        {
                            mode=3;
                            newGame();
                            getLeaderboard();
                            windowSelect=2;
                        }
                if  (((sf::Mouse::getPosition(window).x >= 515 && sf::Mouse::getPosition(window).x <= 765)&&
                    (sf::Mouse::getPosition(window).y >= 570 && sf::Mouse::getPosition(window).y <= 670))&&
                    (windowSelect==0)&& textInput.length()>0)
                        {
                            playerArr[5].name = textInput;
                            windowSelect=5;
                        }
            }
        }
        if (windowSelect==0){ // show the selected screen
        drawPlayer();
        }else if (windowSelect==1){
        drawLeaderboard();
        }else if (windowSelect==5){
        drawLevel();
        }else if (windowSelect>2){
        drawOther(windowSelect);
        }else if (windowSelect==2){

        if ((time1 - lastTime)>160)         // plays the sound
        {
            sound2.play();
            lastTime=time1;
        }
        scoreAsText.setString(to_string(score));
        bigTileAsText.setString(to_string(bigTile));
        moved=0; // reset the variable
        draw(); //display changes
        change(arrow);
        combine(arrow);
        change(arrow);
        if (moved)
        {
            newValue();
            tempToLast();
            boardToTemp();
        }
        if (lose())
        {
            windowSelect=4;
            sound2.stop();
            lastTime=0;
            sound1.play();
            outLeaderboard(textInput);
            getLeaderboard();
        }
        if (won && !cont)
        {
            windowSelect=3;
            sound2.stop();
            lastTime=0;
            sound.play();

        }

    cout <<"Your score is : "<<score<<endl;
    }
    }

    return EXIT_SUCCESS;
}

bool comparePlayers(player a,player b)
{
    if (a.score!=b.score)                   //check about score of both players
        return a.score>b.score;         //arrange both players acording to their score
        return a.bigTile>b.bigTile;         //arrange both players acording to their bigtile if thire score hasnot arrange them
}
/*check if the board is full */
bool boardIsFull()
{
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            if (board[i][j]== 0)
                return 0;
    return 1;
}
/*this function check rows and columns if we could combine 2 tiles or not   */
bool lose()
{
    bool lost=1;
    if (boardIsFull())
    {
            for (int i=1;i<4;i++)
            for (int j=0;j<4;j++)
                if (board[i][j]== board[i-1][j] && board[i][j]!=0)
                    lost=0;
            for (int i=2;i>-1;i--)
            for (int j=0;j<4;j++)
                if (board[i][j]== board[i+1][j] && board[i][j]!=0)
                    lost=0;
            for (int i=0;i<4;i++)
            for (int j=2;j>-1;j--)
                if (board[i][j]== board[i][j+1] && board[i][j]!=0)
                    lost=0;
            for (int i=0;i<4;i++)
            for (int j=1;j<4;j++)
                if (board[i][j]== board[i][j-1] && board[i][j]!=0)
                    lost=0;
            return lost;

    }
    return 0;
}
/*you win win your bigTile = 2048*/
bool win()
{
    if (bigTile==2048)
    {
        won=1;
    }
    return 1;
}
/*this function works to draw background , board and tile as well*/
void draw()
{
    window.draw(bg);
    window.draw(bigTileAsText);
    window.draw(scoreAsText);
    window.draw(bestAsText);
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            if (board[i][j])
            {
                switch (board[i][j]){
                case 2   :
                    tile2.setPosition(140*j+655,140*i+87);
                    window.draw(tile2);
                    break;
                case 4   :
                    tile4.setPosition(140*j+655,140*i+87);
                    window.draw(tile4);
                    break;
                case 8   :
                    tile8.setPosition(140*j+655,140*i+87);
                    window.draw(tile8);
                    break;
                case 16  :
                    tile16.setPosition(140*j+655,140*i+87);
                    window.draw(tile16);
                    break;
                case 32  :
                    tile32.setPosition(140*j+655,140*i+87);
                    window.draw(tile32);
                    break;
                case 64  :
                    tile64.setPosition(140*j+655,140*i+87);
                    window.draw(tile64);
                    break;
                case 128 :
                    tile128.setPosition(140*j+655,140*i+87);
                    window.draw(tile128);
                    break;
                case 256 :
                    tile256.setPosition(140*j+655,140*i+87);
                    window.draw(tile256);
                    break;
                case 512 :
                    tile512.setPosition(140*j+655,140*i+87);
                    window.draw(tile512);
                    break;
                case 1024:
                    tile1024.setPosition(140*j+655,140*i+87);
                    window.draw(tile1024);
                    break;
                case 2048:
                    tile2048.setPosition(140*j+655,140*i+87);
                    window.draw(tile2048);
                    break;
                case 4096:
                    tile4096.setPosition(140*j+655,140*i+87);
                    window.draw(tile4096);
                    break;
                case 8192:
                    tile8192.setPosition(140*j+655,140*i+87);
                    window.draw(tile8192);
                    break;
                case 16384:
                    tile16384.setPosition(140*j+655,140*i+87);
                    window.draw(tile16384);
                    break;
                }
            }
        }
    }
    window.display();
    sf::sleep(sf::milliseconds(30));
}
// this function draw the name of top 5 players with score and bigTile
void drawLeaderboard()
{
    window.clear();
    window.draw(leaderboard);
    for (int i=0;i<5;i++)
    {
        window.draw(playerName[i]);
        window.draw(playerScoreAsText[i]);
        window.draw(playerBigTileAsText[i]);
    }
    window.display();
}
// it draw window that you should write your name in
void drawPlayer()
{
    window.clear();
    window.draw(playerbg);
    window.draw(textToDisplay);
    window.display();
}
/*it work just to draw levels*/
void drawLevel()
{
    window.clear();
    window.draw(level);
    window.display();
}
/*this function works to draw if you win win board and lose */
void drawOther(int windowSelect)
{
    scoreAsText.setString(to_string(score));
    bigTileAsText.setString(to_string(bigTile));
    window.draw(bg);
    window.draw(bigTileAsText);
    window.draw(scoreAsText);
    window.draw(bestAsText);
    for (int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            if (board[i][j])
            {
                switch (board[i][j]){
                case 2   :
                    tile2.setPosition(140*j+655,140*i+87);
                    window.draw(tile2);
                    break;
                case 4   :
                    tile4.setPosition(140*j+655,140*i+87);
                    window.draw(tile4);
                    break;
                case 8   :
                    tile8.setPosition(140*j+655,140*i+87);
                    window.draw(tile8);
                    break;
                case 16  :
                    tile16.setPosition(140*j+655,140*i+87);
                    window.draw(tile16);
                    break;
                case 32  :
                    tile32.setPosition(140*j+655,140*i+87);
                    window.draw(tile32);
                    break;
                case 64  :
                    tile64.setPosition(140*j+655,140*i+87);
                    window.draw(tile64);
                    break;
                case 128 :
                    tile128.setPosition(140*j+655,140*i+87);
                    window.draw(tile128);
                    break;
                case 256 :
                    tile256.setPosition(140*j+655,140*i+87);
                    window.draw(tile256);
                    break;
                case 512 :
                    tile512.setPosition(140*j+655,140*i+87);
                    window.draw(tile512);
                    break;
                case 1024:
                    tile1024.setPosition(140*j+655,140*i+87);
                    window.draw(tile1024);
                    break;
                case 2048:
                    tile2048.setPosition(140*j+655,140*i+87);
                    window.draw(tile2048);
                    break;
                case 4096:
                    tile4096.setPosition(140*j+655,140*i+87);
                    window.draw(tile4096);
                    break;
                case 8192:
                    tile8192.setPosition(140*j+655,140*i+87);
                    window.draw(tile8192);
                    break;
                case 16384:
                    tile16384.setPosition(140*j+655,140*i+87);
                    window.draw(tile16384);
                    break;
                }
            }
        }
    }
    switch (windowSelect)
    {
        case 3: window.draw(winbg);
        break;
        case 4: if (won)
                    window.draw(gameoverbg);
                else
                    window.draw(losebg);
        break;
    }
    window.display();
}
/*this function works to check if the direction you pressed
 could move the tiles or not */
void change(int n)
{
    int avalible=1;
    if (n==1)

    {
        while (avalible)
        {
            avalible=0;
            for (int i=2;i>-1;i--)
            for (int j=0;j<4;j++)
                if (board[i][j]==0 && board[i+1][j]!=0)
                {
                    board[i][j]=board[i+1][j];
                    board[i+1][j]=0;
                    avalible=1;
                    moved=1;
                    draw();
                }
        }
    }
    if (n==2)
    {
        while (avalible)
        {
            avalible=0;
            for (int i=1;i<4;i++)
            for (int j=0;j<4;j++)
                if (board[i][j]==0 && board[i-1][j]!=0)
                {
                    board[i][j]=board[i-1][j];
                    board[i-1][j]=0;
                    avalible=1;
                    moved=1;
                    draw();
                }
        }
    }
    if (n==3)
    {
        while (avalible)
        {
            avalible=0;
            for (int i=0;i<4;i++)
            for (int j=1;j<4;j++)
                if (board[i][j]==0 && board[i][j-1]!=0)
                {
                    board[i][j]=board[i][j-1];
                    board[i][j-1]=0;
                    avalible=1;
                    moved=1;
                    draw();
                }
        }
    }
    if (n==4)
    {
        while (avalible)
        {
            avalible=0;
            for (int i=0;i<4;i++)
            for (int j=2;j>-1;j--)
                if (board[i][j]==0 && board[i][j+1]!=0)
                {
                    board[i][j]=board[i][j+1];
                    board[i][j+1]=0;
                    avalible=1;
                    moved=1;
                    draw();
                }
        }
    }
}
/*this function works to check if we have 2 tiles have the same value
and then by your direction it will combine them  */
void combine (int n)
{
    if (n==1)
    {
            for (int i=1;i<4;i++)
            for (int j=0;j<4;j++)
                if (board[i][j]== board[i-1][j] && board[i][j]!=0)
                {
                    board[i-1][j]+=board[i][j];
                    board[i][j]=0;
                    moved=1;
                    score+=board[i-1][j];
                    if (board[i-1][j]>bigTile)
                        bigTile=board[i-1][j];
                    draw();
                }
    }
    if (n==2)

    {
            for (int i=2;i>-1;i--)
            for (int j=0;j<4;j++)
                if (board[i][j]== board[i+1][j] && board[i][j]!=0)
                {
                    board[i+1][j]+=board[i][j];
                    board[i][j]=0;
                    moved=1;
                    score+=board[i+1][j];
                    if (board[i+1][j]>bigTile)
                        bigTile=board[i+1][j];
                    draw();
                }
    }
    if (n==3)
    {
            for (int i=0;i<4;i++)
            for (int j=2;j>-1;j--)
                if (board[i][j]== board[i][j+1] && board[i][j]!=0)
                {
                    board[i][j+1]+=board[i][j];
                    board[i][j]=0;
                    moved=1;
                    score+=board[i][j+1];
                    if (board[i][j+1]>bigTile)
                        bigTile=board[i][j+1];
                    draw();
                }
    }
    if (n==4)
    {
            for (int i=0;i<4;i++)
            for (int j=1;j<4;j++)
                if (board[i][j]== board[i][j-1] && board[i][j]!=0)
                {
                    board[i][j-1]+=board[i][j];
                    board[i][j]=0;
                    moved=1;
                    score+=board[i][j-1];
                    if (board[i][j-1]>bigTile)
                        bigTile=board[i][j-1];
                    draw();
                }
    }
}
/*this function works to get input from the game the player name ,his score and big tile
and put all of this in array and sort it with top 5 */
void outLeaderboard(string textInput)
{
    playerArr[5].name = textInput;
    playerArr[5].bigTile=bigTile;
    playerArr[5].score=score;
    sort(playerArr,playerArr+6,comparePlayers);
    if (mode==1)
    {
        ofstream scoreBoardOut("ScoreBoardEasy.bin");
        for (int i=0;i<5;i++)
        scoreBoardOut<<playerArr[i].name<<" "<<playerArr[i].score<<" "<<playerArr[i].bigTile<<"\n";
        scoreBoardOut.close();
    }
    if (mode==2)
    {
        ofstream scoreBoardOut("ScoreBoardNormal.bin");
        for (int i=0;i<5;i++)
        scoreBoardOut<<playerArr[i].name<<" "<<playerArr[i].score<<" "<<playerArr[i].bigTile<<"\n";
        scoreBoardOut.close();
    }
    if (mode==3)
    {
        ofstream scoreBoardOut("ScoreBoardHard.bin");
        for (int i=0;i<5;i++)
        scoreBoardOut<<playerArr[i].name<<" "<<playerArr[i].score<<" "<<playerArr[i].bigTile<<"\n";
        scoreBoardOut.close();
    }
}
// this function write on file
void getLeaderboard()
{
    if (mode==1)
    {
        ifstream scoreBoardIn ("ScoreBoardEasy.bin");
    if (!static_cast<bool>(scoreBoardIn))
    {
        for (int i=0;i<5;i++)
        {
        playerArr[i].name="Noun";
        playerArr[i].score=0;
        playerArr[i].bigTile=0;
        }
    }
    else{
    for (int i=0;i<5;i++)
        scoreBoardIn>>playerArr[i].name>>playerArr[i].score>>playerArr[i].bigTile;
    }
    }
    if (mode==2)
    {
        ifstream scoreBoardIn ("ScoreBoardNormal.bin");
    if (!static_cast<bool>(scoreBoardIn))
    {
        for (int i=0;i<5;i++){
        playerArr[i].name="Noun";
        playerArr[i].score=0;
        playerArr[i].bigTile=0;
        }
    }
    else{
    for (int i=0;i<5;i++)
        scoreBoardIn>>playerArr[i].name>>playerArr[i].score>>playerArr[i].bigTile;
    }
    }
    if (mode==3)
    {
        ifstream scoreBoardIn ("ScoreBoardHard.bin");
    if (!static_cast<bool>(scoreBoardIn))
    {
        for (int i=0;i<5;i++){
        playerArr[i].name="Noun";
        playerArr[i].score=0;
        playerArr[i].bigTile=0;
        }
    }
    else{
    for (int i=0;i<5;i++)
        scoreBoardIn>>playerArr[i].name>>playerArr[i].score>>playerArr[i].bigTile;
    }
    }
    bestAsText.setString(to_string(playerArr[0].score));
    bestAsText.setPosition(265,320);
    bestAsText.setColor(sf::Color::White);
    bestAsText.setFont(font);
    bestAsText.setCharacterSize(48);
    for (int i=0;i<5;i++)
    {
        playerName[i].setString(playerArr[i].name);
        playerName[i].setPosition(100,60+(i*100));
        playerName[i].setColor(sf::Color::White);
        playerName[i].setFont(font);
        playerName[i].setCharacterSize(74);

        playerScoreAsText[i].setString(to_string(playerArr[i].score));
        playerScoreAsText[i].setPosition(580,60+(i*100));
        playerScoreAsText[i].setColor(sf::Color::White);
        playerScoreAsText[i].setFont(font);
        playerScoreAsText[i].setCharacterSize(74);

        playerBigTileAsText[i].setString(to_string(playerArr[i].bigTile));
        playerBigTileAsText[i].setPosition(920,60+(i*100));
        playerBigTileAsText[i].setColor(sf::Color::White);
        playerBigTileAsText[i].setFont(font);
        playerBigTileAsText[i].setCharacterSize(74);
    }
}
/*this function works to copy tempBoard to lastBoard*/
void tempToLast()
{
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            lastBoard[i][j]= tempBoard[i][j];
}
/*this function works to copy lastBoard to temptBoard*/
void lastToTemp()
{
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            tempBoard[i][j]= lastBoard[i][j];
}
/*this function works to copy the board to tempBoard*/
void boardToTemp()
{
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            tempBoard[i][j]= board[i][j];
}
/*this function works to copy lastBoard to Board*/
void lastToBoard()
{
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            board[i][j]= lastBoard[i][j];
}
/*newValue this function works until you lose
by adding the value random in the board
But the value varies according to the mods
Easy the value will be 2 100%,
normal the value will be 2 and 4
2:4=9:1
and the hard mod have more values 2,4,8and 16
2:4:8:16 = 4:3:2:1*/
void newValue()
{
    if (mode==3)
    {
        while(1)
    {
        int i=rand()%4, j=rand()%4, z=rand()%10;
        if (board[i][j]==0)
        {
            if (z<4)
                board[i][j]= 2;
            else if (z<7)
                board[i][j]= 4;
            else if (z<9)
                board[i][j]= 8;
            else
                board[i][j]= 16;
            break;
        }
    }
    }
    if (mode==2)
    {
        while(1)
    {
        int i=rand()%4, j=rand()%4, z=rand()%10;
        if (board[i][j]==0)
        {
            if (z<9)
                board[i][j]= 2;
            else
                board[i][j]= 4;
            break;
        }
    }
    }
    if (mode==1)
    {
        while(1)
    {
        int i=rand()%4, j=rand()%4;
        if (board[i][j]==0)
        {
                board[i][j]= 2;
            break;
        }
    }
    }
}
/*this function works only when you press new game add value random in the board
the value will be 2*/
void newGameValue()
{
        int i=rand()%4, j=rand()%4;
            board[i][j]= 2;
}
/*this is function newGame make the board in rows and column = 0 and add newGame
value and new value*/
void newGame()
{
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            board[i][j]= 0;
    newGameValue();
    newValue();
    moved=0;
    bigTile=0;
    score=0;
    won=0;
    cont=0;
    boardToTemp();
    tempToLast();
}
