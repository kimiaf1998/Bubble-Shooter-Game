// ESSENTIAL HEADER FILES
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#define ROWS 2800//***was14
#define COLS 4500//***was15
#define PI 3.141592653589
using namespace std;
using namespace sf;
// A STRUCT IN ORDER TO CONTAIN THE X,Y COORDINATES + COLOR OD EACH BULLET
struct trateState
{
    int X[2*ROWS-2+COLS];
    int Y[2*ROWS-2+COLS];
    int COLOR[2*ROWS-2+COLS];
}TS;
// DECLARING SOME GLOBAL INSTANTS
       sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
       sf::RenderWindow window(desktop, "Trust in SeedS",sf::Style::Fullscreen);

       sf::Texture frogTexture;
       sf::Sprite frogSprite;
       sf::Texture backgroundTexture;
       sf::Sprite backgroundSprite;
       sf::Texture arrowTexture;
       sf::Sprite arrowSprite;
       sf::Texture skullTexture;
       sf::Sprite skullSprite;
       sf::Font ARIAL_FONT;
       sf::Font BEAUTY_FONT;
       sf::Text startText;
       sf::Text finishText;
       sf::Text scoreText;
       sf::Text scoreWordText;
       sf::Text playerWordText;
       sf::Text playerText;
       sf::Text frogText;
       sf::CircleShape toShootBullet;
       sf::Event::MouseMoveEvent mouseMove;
       sf::Event::MouseButtonEvent mouseButton;
       sf::CircleShape CIRCLES[2*ROWS-2+COLS];
       sf::Text newGameText;
       sf::Text loadGameText;
       sf::Text aboutText;
       sf::Text exitText;
       sf::Texture speakerTexture;
       sf::Texture pauseBackgroundTexture;
       sf::Sprite pauseBackgroundSprite;
       sf::Texture pauseTexture;
       sf::Sprite pauseSprite;
       sf::Text pauseText;
       sf::Text pauseText1;
       sf::Text pauseText2;
       sf::Text pauseText3;
       sf::Text pauseText4;
       sf::Texture menuBackTexture;
       sf::Sprite menuBackSprite;
       sf::Font MENUFONT;
       sf::Text restartText;
       sf::Text OK;
       sf::Texture gameoverbackTexture;
       sf::Sprite  gameoverbackSprite;
       sf::Texture happyBackTexture;
       sf::Sprite  happyBackSprite;
       sf::Texture sadBackTexture;
       sf::Sprite  sadBackSprite;
       sf::Text gameOverText;
       sf::Text wonText;
       sf::Text looseText;
       sf::Text tScoreText;


       sf::Event event;
// VARIABLE DEFINING
bool escapePressed=false;
bool isOpenForTheFirst=true;
bool mute=false;
int hitIndex;
int counter=0;
int BLUE=0,YELLOW=0,RED=0,GREEN=0; //FIRST BULLET COLOR COUNTER (USEFULL FOR INITIALIZE)
int newX,newY;
//***int death=0;                       //COUNTS TRAVERSED STEPS TOWARD THE SKULL
int currentNumberOfBullets=10;     //REMAINED BULLETS
int Mouse_X=0;                     //CURRENT X POSITION OF THE MOUSE
int Mouse_Y=0;                     //CURRENT Y POSITION OF THE MOUSE
int toShootColor=0;                //COLOR OF "TO_SHOOT" BULLET
double TAN=1;                      //TAN OF THE ORIENTION OF  "TOSHOOT" BULLET
double TETHA=45;                    // DEGREE OF TAN
double RADIAN;
int currentScore=0;                  //CURRENT SCORE
bool won=false;					   //WINNING STATE
int sameColored=0;                 //NUMBER OF THE SAMECOLORED BULLETS(WILL BE INITIALIZED IN RESEMBLANCECHECK)
int begginingWith=0;               //will Specify Which element is at the beggining?
string frogSays="Nice !";          //WHAT THE FROG SAYS!!!
string movePortion="Up";            //SPECIFIES WHICH PORTION THE TRAIL IS MOVING
// FUNCTION PROTYPES

void gameOverDraw();                        //DRAWS THE ESSENTIAL OBJECTS OF THE GAMEOVER MENU
void drawAbout();                           //DRAWS THE ESSENTIAL OBJECTS OF THE ABOUT MENU
void doDraw();                              //DRAWS THE ESSENTIAL OBJECTS OF THE PAUSE MENU
void setSound();
void loadGame();                            //loads the last played game
int findTheFirst();                         //RETURNS THE FIRST DIFFERENT_COLOR (index of)BULLET AFTER THE SAMECOLOR STATUS
double getDistance(Vector2f,Vector2f);     //RETURNS THE DISTANE BETWEEN TWO OBJECTS
void drawPlease();
double numToResX(double);                 //CONVERTS SELF RESOLUTION TO STANDARD ONE FOR X PARAMETERS
double numToResY(double);                 //CONVERTS SELF RESOLUTION TO STANDARD ONE FOR Y PARAMETERS
sf::Color toColor(int);            //CONVERTS AND RETURNS THE RANDOM COLOR NUMBER AS A SFML COLOR OBJECT
void which();                      //WHICH ELEMENT OF THE STRUCT IS THE BEGGINING
int pauseState();                 //SHOWS THE PAUSE MENU AND RETURNS THE CLICKED ITEM
void screenLoad();                 //SHOWS THE TRAIL AND THE FROG AND THE COLOR AND THE WAY AND THE SKULL AND THE SCORE
void startMenu();                  //SHOWS THE FIRST MENU WHICH CONTAINS PLAY, ABOUT AND EXIT
string toString(int);              //CONVERTS INT TO STRING
void playZuma();                   //STARTS PLAYING ZUMA GAME
void exitZuma();                   //BREAKS(EXITS) PLAYING ZUMA GAME
void aboutZuma();                  //SHOWS THE "ABOUT" PART OF THE GAME(IN ORDER TO HELP + ADVERTISEMENTS)
void frogColor();                  //PUT A RANDOM COLOR INSIDE THE FROG
void setFree();                    //INITIALIZE THE TRAILS WITH NULL OR ZERO
void preStart();                   //INITIALIZE FIRST 10 PLACE OF THE TRAIL WITH BULLETS
void shootingSimulation();         //SIMULATES THE SHOOTING  IN ANIMATION AND ARRAY_CHANGING
void gameOver();                   //WILL BE SHOWED AFTER WIN(OR BE CALLED BY GAMEOVER) TO SHOW THE SCORE AND TRY AGAIN MENU
void placement(int);                  //WILL BE CALELD IF THE SHOOTED BULLETS IMPACTED TO THE TRAIL/ WILL SHIFT THE TRAIL IN ORDER TO PLACING THE SHOOTED COLOR / WILL DECREASE death VARRIABLE / WILL UPDATE ARRAY OF THE TRAIL
void linkTrail();                  //LINKS(CONNECTS) TWO SEPARATED PARTS OF THE TRAIL
void scoreUpdate(int score);       //UPDATE currentScore VALUE
int getRandomColor();              //RETURNS A RANDOM COLOR BETWEEN 1 & 4 / WILL BE USED IN FIRST INITIALIZING +  frogColor();
void shiftBullet(int,string);       //SHIFTS A BULLET TO THE GIVEN ORIENTION
bool resemblanceCheck();           //CHECKS EXISTENCE OF THREE OR MORE SAMECOLORED BULLETS
bool isFinished();                 //CHECKS IF THE GAME IS FINISHED OR NO/RETURNS TRUE IF IS FINISHED
double setShootOriention(int,int); //SETS THE ARROW TO THE MOUSE / RETURNS THE TANGANT OF THE MOUSE ORIENTION IN ORDER TO SHOOT IN LATER!
// MAIN FUNCTION
int main()
{
    window.setFramerateLimit(60);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    if (!frogTexture.loadFromFile("frog.png"));
    {
        // error...
    }
    frogSprite.setTexture(frogTexture);
    if (!backgroundTexture.loadFromFile("background.png"));
    {
        // error...
    }
    backgroundSprite.setTexture(backgroundTexture);
    if (!arrowTexture.loadFromFile("arrow.png"));
    {
        // error...
    }
    arrowSprite.setTexture(arrowTexture);
    if (!skullTexture.loadFromFile("skull.png"));
    {
        // error...
    }
    skullSprite.setTexture(skullTexture);
    if(!ARIAL_FONT.loadFromFile("arial.ttf"))
    {

    }
    if(!BEAUTY_FONT.loadFromFile("ITCEDSCR.TTF"))
    {

    }
    if (!pauseTexture.loadFromFile("pause.png"))
    {
        // error...
    }
    pauseSprite.setTexture(pauseTexture);
    if (!pauseBackgroundTexture.loadFromFile("pauseBackground.png"))
    {
        // error...
    }
    pauseBackgroundSprite.setTexture(backgroundTexture);
    if(!gameoverbackTexture.loadFromFile("menuBack.png"))
    {
        //error
    }
    srand(time(NULL));
        while (window.isOpen())
        {
            startMenu();
            if(isOpenForTheFirst)
            {
                setSound();
                isOpenForTheFirst=false;
            }
            Mouse_X=sf::Mouse::getPosition().x;
            Mouse_Y=sf::Mouse::getPosition().y;
            //------------get input------------
            while (window.pollEvent(event))
            {
                switch(event.type)
                {
                    case sf::Event::Closed:
                        exitZuma();
                        break;
                    case sf::Event::MouseMoved :
                    {
                        //new game
                        if(Mouse_X>=numToResX(579)  && Mouse_X<=numToResX(929) && Mouse_Y>=396 && Mouse_Y<=numToResY(553))
                            newGameText.setColor(sf::Color::Black);
                        else
                            newGameText.setColor(sf::Color::White);
                        //load game
                        if(Mouse_X>=numToResX(979)  && Mouse_X<=numToResX(1329) && Mouse_Y>=396 && Mouse_Y<=numToResY(553))
                            loadGameText.setColor(sf::Color::White);
                        else
                            loadGameText.setColor(sf::Color::Black);
                        //about game
                        if(Mouse_X>=numToResX(579)  && Mouse_X<=numToResX(929) && Mouse_Y>=596 && Mouse_Y<=numToResY(753))
                            aboutText.setColor(sf::Color::White);
                        else
                            aboutText.setColor(sf::Color::Black);
                        //exit game
                        if(Mouse_X>=numToResX(979)  && Mouse_X<=numToResX(1329) && Mouse_Y>=596 && Mouse_Y<=numToResY(753))
                            exitText.setColor(sf::Color::Black);
                        else
                            exitText.setColor(sf::Color::White);
                    }
                    case sf::Event::MouseButtonPressed:
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            if(Mouse_X>=numToResX(579) && Mouse_X <=numToResX(929) && Mouse_Y>=numToResY(396) && Mouse_Y<=numToResY(553))
                            {
                                setFree();
                                preStart();
                                playZuma();
                            }
                            else if(Mouse_X>=numToResX(979) && Mouse_X <=numToResX(1329) && Mouse_Y>=numToResY(396) && Mouse_Y<=numToResY(553))
                                loadGame();
                            else if(Mouse_X>=numToResX(579) && Mouse_X <=numToResX(929) && Mouse_Y>=numToResY(596) && Mouse_Y<=numToResY(753))
                                aboutZuma();
                            else if(Mouse_X>=numToResX(979) && Mouse_X <=numToResX(1329) && Mouse_Y>=numToResY(596) && Mouse_Y<=numToResY(753))
                                exitZuma();
                            else if(Mouse_X>=numToResX(30) && Mouse_X <=numToResX(80) && Mouse_Y>=numToResY(1010) && Mouse_Y<=numToResY(1060))
                                setSound();
                        }
                        break;
                    case sf::Event::KeyPressed:
                        switch(event.key.code)
                        {
                            case sf::Keyboard::Escape:
                                exitZuma();
                                break;
                        }
                    break;
                }
            }
        }
}
// LINKED FUNCTIONS(IS BETTER TO PUT IN A HEADER!
void drawAbout()
{
    window.clear();
    window.draw(menuBackSprite);

    sf::Text TrustText;
    sf::Text d1;
    sf::Text d2;
    sf::Text d3;
    sf::Text l1;
    sf::Text l2;
    sf::Text l3;
    sf::Text l4;
    sf::Text l5;
    sf::Text S10;
    sf::Text S20;
    sf::Text S30;
    sf::Text S40;


    sf::CircleShape OKCircle;
    sf::CircleShape blueCircle,redCircle,yellowCircle,greenCircle;
    OKCircle.setRadius(43);
    blueCircle.setRadius(43);
    redCircle.setRadius(43);
    yellowCircle.setRadius(43);
    greenCircle.setRadius(43);
    OKCircle.setPosition(860,950);
    OKCircle.setFillColor(sf::Color::Blue);
    blueCircle.setPosition(570,750);
    blueCircle.setFillColor(sf::Color::Blue);
    redCircle.setPosition(760,750);
    redCircle.setFillColor(sf::Color::Yellow);
    yellowCircle.setPosition(960,750);
    yellowCircle.setFillColor(sf::Color::Red);
    greenCircle.setPosition(1140,750);
    greenCircle.setFillColor(sf::Color::Green);

    sf::RectangleShape backRect(Vector2f(numToResX(100),numToResY(100)));

    TrustText.setFont(BEAUTY_FONT);
    TrustText.setString("Trust In SeedS");
    TrustText.setColor(sf::Color::White);
    TrustText.setPosition(680,100);
    TrustText.setCharacterSize(86);
    d1.setFont(ARIAL_FONT);
    d1.setString("Zuma");
    d1.setColor(sf::Color::White);
    d1.setPosition(860,275);
    d1.setCharacterSize(35);
    d2.setFont(ARIAL_FONT);
    d2.setString("Developed by Kimia Afshari");
    d2.setColor(sf::Color::White);
    d2.setPosition(740,868);
    d2.setCharacterSize(25);
    d3.setFont(ARIAL_FONT);
    d3.setString("2017 - 01 - 18");
    d3.setColor(sf::Color::White);
    d3.setPosition(830,908);
    d3.setCharacterSize(25);
    l1.setFont(ARIAL_FONT);
    l1.setString("Zuma deluxe is one of the most challenging and addictive game ever. The purpose of this game is to");
    l1.setColor(sf::Color::White);
    l1.setPosition(170,400);
    l1.setCharacterSize(35);
    l2.setFont(ARIAL_FONT);
    l2.setString("find the secrets of Zuma and protect the ancient civilizations.There are several colored balls in a chain");
    l2.setColor(sf::Color::White);
    l2.setPosition(170,470);
    l2.setCharacterSize(35);
    l3.setFont(ARIAL_FONT);
    l3.setString("who are coming towards the skull. Make groups of three or more balls of the same color and destroy");
    l3.setColor(sf::Color::White);
    l3.setPosition(170,530);
    l3.setCharacterSize(35);
    l4.setFont(ARIAL_FONT);
    l4.setString("them. Use Your Mouse and try to avoid the balls reach the skull or the game will end. It won't be easy");
    l4.setColor(sf::Color::White);
    l4.setPosition(170,590);
    l4.setCharacterSize(35);
    l5.setFont(ARIAL_FONT);
    l5.setString("but if you want to win, try not to lose the time.");
    l5.setColor(sf::Color::White);
    l5.setPosition(170,650);
    l5.setCharacterSize(35);
    OK.setFont(ARIAL_FONT);
    OK.setString("OK");
    OK.setPosition(880,975);

    S10.setFont(ARIAL_FONT);
    S10.setString("10");
    S10.setPosition(595,775);
    S10.setColor(sf::Color::White);

    S20.setFont(ARIAL_FONT);
    S20.setString("20");
    S20.setPosition(785,775);
    S20.setColor(sf::Color::White);

    S30.setFont(ARIAL_FONT);
    S30.setString("30");
    S30.setPosition(985,775);
    S30.setColor(sf::Color::White);

    S40.setFont(ARIAL_FONT);
    S40.setString("40");
    S40.setPosition(1165,775);
    S40.setColor(sf::Color::White);

    window.draw(TrustText);
    window.draw(d1);
    window.draw(d2);
    window.draw(d3);
    window.draw(l1);
    window.draw(l2);
    window.draw(l3);
    window.draw(l4);
    window.draw(l5);
    window.draw(OKCircle);
    window.draw(greenCircle);
    window.draw(redCircle);
    window.draw(yellowCircle);
    window.draw(blueCircle);
    window.draw(OK);
    window.draw(S10);
    window.draw(S20);
    window.draw(S30);
    window.draw(S40);


}
void aboutZuma()
{
    bool cont=true;
    while(window.isOpen() && cont)
    {
        Mouse_X=sf::Mouse::getPosition().x;
        Mouse_Y=sf::Mouse::getPosition().y;
        drawAbout();
        window.display();
        while (window.pollEvent(event))
            {
                switch(event.type)
                {
                    case sf::Event::Closed:
                        exitZuma();
                        break;
                    case sf::Event::MouseMoved :
                    {
                        //OK
                        if(Mouse_X>=numToResX(860)  && Mouse_X<=numToResX(945) && Mouse_Y>=numToResY(950) && Mouse_Y<=numToResY(1037))
                            OK.setColor(sf::Color::Red);
                        else
                            OK.setColor(sf::Color::White);
                    }
                    case sf::Event::MouseButtonPressed:
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            if(Mouse_X>=numToResX(860)  && Mouse_X<=numToResX(945) && Mouse_Y>=numToResY(950) && Mouse_Y<=numToResY(1037))
                            {
                                window.clear();
                                cont=false;
                                startMenu();

                            }
                        }
                        break;
                    case sf::Event::KeyPressed:
                        switch(event.key.code)
                        {
                            case sf::Keyboard::Escape:
                                exitZuma();
                                break;
                        }
                    break;
                }
            }
    }

}
void doDraw()
{
    backgroundSprite.setPosition(numToResX(0),numToResY(0));
    backgroundSprite.setScale(numToResX(1),numToResY(1));
    pauseSprite.setPosition(numToResX(620),numToResY(170));
    pauseSprite.setScale(numToResX(3),numToResY(3));
    pauseText.setPosition(numToResX(840),numToResY(160));
    pauseText1.setPosition(numToResX(816),numToResY(340));
    pauseText2.setFont(ARIAL_FONT);
    pauseText2.setCharacterSize(57);
    pauseText2.setString("Restart");
    pauseText2.setPosition(numToResX(825),numToResY(395));
    pauseText3.setFont(ARIAL_FONT);
    pauseText3.setCharacterSize(52);
    pauseText3.setString("Turn sound off");
    pauseText3.setPosition(numToResX(760),numToResY(500));
    pauseText4.setFont(ARIAL_FONT);
    pauseText4.setCharacterSize(57);
    pauseText4.setString("Exit");
    pauseText4.setPosition(numToResX(870),numToResY(592));

    window.draw(pauseBackgroundSprite);
    window.draw(pauseSprite);
    window.draw(pauseText2);
    window.draw(pauseText3);
    window.draw(pauseText4);
}
int pauseState()
{
    window.clear();
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch(event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::MouseMoved:
                    {
                        Mouse_X=sf::Mouse::getPosition().x;
                        Mouse_Y=sf::Mouse::getPosition().y;
                        //restart
                        if(Mouse_X>=numToResX(830) && Mouse_X <=numToResX(1005) && Mouse_Y>=numToResY(408) && Mouse_Y<=numToResY(448))
                            pauseText2.setColor(sf::Color::Red);
                        else
                            pauseText2.setColor(sf::Color::White);
                        //turn sound
                        if(Mouse_X>=numToResX(760) && Mouse_X <=numToResX(1095) && Mouse_Y>=numToResY(508) && Mouse_Y<=numToResY(548))
                            pauseText3.setColor(sf::Color::Red);
                        else
                            pauseText3.setColor(sf::Color::White);
                        //exit
                        if(Mouse_X>=numToResX(875) && Mouse_X <=numToResX(968) && Mouse_Y>=numToResY(608) && Mouse_Y<=numToResX(648))
                            pauseText4.setColor(sf::Color::Red);
                        else
                            pauseText4.setColor(sf::Color::White);
                        break;

                    }
                    case sf::Event::KeyPressed :
                        if(event.key.code == sf::Keyboard::Escape)
                            return 4;
                        break;
                    case sf::Event::MouseButtonPressed:
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            if(Mouse_X>=numToResX(830) && Mouse_X <=numToResX(1005) && Mouse_Y>=numToResY(408) && Mouse_Y<=numToResY(448))
                                return 1;
                            else if(Mouse_X>=numToResX(760) && Mouse_X <=numToResX(1095) && Mouse_Y>=numToResY(508) && Mouse_Y<=numToResY(548))
                                return 2;
                            else if(Mouse_X>=numToResX(875) && Mouse_X <=numToResX(968) && Mouse_Y>=numToResY(608) && Mouse_Y<=numToResY(648))
                                return 3;
                        }
                        break;
                }
        }
        doDraw();
        window.display();
    }
}
void setSound()
{
    if(!mute)
    {
        //remember to mute the sound
        //change the mute logo :
        if(!speakerTexture.loadFromFile("mutespeaker.png"))
        {
            //error
        }
        mute=true;
    }
    else
    {
        //remember to mute the sound
        //change the mute logo :
        if(!speakerTexture.loadFromFile("Speaker.png"))
        {
            //error
        }
        mute=false;
    }
}
void startMenu()
{

    sf::Texture newGameTexture;
    sf::RectangleShape newGameRect(sf::Vector2f(numToResX(350),numToResY(150)));
    sf::Texture loadGameTexture;
    sf::RectangleShape loadGameRect(sf::Vector2f(numToResX(350),numToResY(150)));
    sf::Texture aboutTexture;
    sf::RectangleShape aboutRect(sf::Vector2f(numToResX(350),numToResY(150)));
    sf::Texture exitTexture;
    sf::RectangleShape exitRect(Vector2f(numToResX(350),numToResY(150)));
    sf::RectangleShape speakerRect(Vector2f(numToResX(50),numToResY(50)));
    if(!menuBackTexture.loadFromFile("menuback.png"))
    {
        //error
    }
    if(!MENUFONT.loadFromFile("arial.ttf"))
    {
        //error
    }
    menuBackSprite.setTexture(menuBackTexture);
    speakerRect.setTexture(&speakerTexture);
    newGameRect.setFillColor(sf::Color::Red);
    loadGameRect.setFillColor(sf::Color::Yellow);
    aboutRect.setFillColor(sf::Color::Green);
    exitRect.setFillColor(sf::Color::Blue);
    speakerRect.setFillColor(sf::Color::White);
    newGameText.setFont(ARIAL_FONT);
    loadGameText.setFont(ARIAL_FONT);
    aboutText.setFont(ARIAL_FONT);
    exitText.setFont(ARIAL_FONT);
    newGameText.setString("New Game");
    loadGameText.setString("Load Game");
    aboutText.setString("About");
    exitText.setString("Exit");


    menuBackSprite.setPosition(numToResX(0),numToResY(0));
    newGameRect.setPosition(numToResX(580),numToResY(400));
    loadGameRect.setPosition(numToResX(980),numToResY(400));
    aboutRect.setPosition(numToResX(580),numToResY(600));
    exitRect.setPosition(numToResX(980),numToResY(600));
    speakerRect.setPosition(numToResX(30),numToResY(1010));
    newGameText.setPosition(numToResX(678),numToResY(460));
    loadGameText.setPosition(numToResX(1075),numToResY(460));
    aboutText.setPosition(numToResX(711),numToResY(655));
    exitText.setPosition(numToResX(1126),numToResY(655));

    window.draw(menuBackSprite);
    window.draw(newGameRect);
    window.draw(loadGameRect);
    window.draw(aboutRect);
    window.draw(exitRect);
    window.draw(speakerRect);
    window.draw(newGameText);
    window.draw(loadGameText);
    window.draw(aboutText);
    window.draw(exitText);

    window.display();

}
void playZuma()
{
    window.clear();
    while (window.isOpen())
    {
        counter++;
        which();
        bool setFrogAngle=false;
        bool mouseClicked=false;
        bool paused=false;
        //----------get input----------
        while (window.pollEvent(event))
        {
            //For keyboard activities
            switch(event.type)
            {
                case sf::Event::Closed:
                    exitZuma();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                    	case sf::Keyboard::Escape:
                        {
                            switch(pauseState())
                            {
                                //restart
                                case 1 :
                                {
                                    setFree();
                                    preStart();
                                    playZuma();
                                    break;
                                }
                                //turn sound
                                case 2 :
                                {
                                    setSound();
                                    break;
                                }
                                //exit
                                    case 3 :
                                {
                                    exitZuma();
                                    break;
                                }
                                //resume
                                case 4 :
                                {
                                    cout<<"HELLO";
                                    break;
                                }

                            }
                        }
                    }
                case sf::Event::MouseMoved:
                    setFrogAngle=true;
                    mouseMove=event.mouseMove;
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        mouseClicked=true;

                        mouseButton=event.mouseButton;
                    }
            }
        }

        //------------ game logic ------------
        if(counter%1 ==0 )
        {
            for(int i=begginingWith+currentNumberOfBullets-1;i>=begginingWith;i--)
        	{
            	if(TS.X[i]==numToResX(114)  && TS.Y[i]>numToResY(80) && TS.Y[i]<=numToResY(1080) )
                {
                    if(i==begginingWith+currentNumberOfBullets-1)
                        movePortion="UP";
            	    shiftBullet(i,"UP");
                }
            	else if(TS.X[i]==numToResX(1710) && TS.Y[i]>=numToResY(80) && TS.Y[i] <= numToResY(1080))
                {
                    if(i==begginingWith+currentNumberOfBullets-1)
                        movePortion="BOTTOM";
                    shiftBullet(i,"BOTTOM");
                }
            	else if(TS.Y[i]==numToResY(80) && TS.X[i]>=numToResX(114) && TS.X[i]<numToResX(1920))
                {
                    if(i==begginingWith+currentNumberOfBullets-1)
                        movePortion="RIGHT";
                    shiftBullet(i,"RIGHT");
                }



        	}
        	which();
           //*** death++;
    	}
        cout<<"x[end] :  "<<TS.X[currentNumberOfBullets+begginingWith-1]<<endl;
        //cout<<"Oriention : "<<movePortion<<endl;
		if(setFrogAngle == true)
        {
            //set shooter angle :
            Mouse_X=sf::Mouse::getPosition().x;
            Mouse_Y=sf::Mouse::getPosition().y;
            TAN=setShootOriention(Mouse_X,Mouse_Y);
            TETHA=atan(TAN)*180/PI;
            TETHA = TETHA<0 ? fabs(TETHA) : 180 - fabs(TETHA) ;
            TAN=-TAN;
        }

        if(mouseClicked == true)
        {

            frogSays="Well !";
            //shoot :


            shootingSimulation();  //estesnaa'an harekate partaabe ro injaa neshoon midim
            if(resemblanceCheck())
   			{

       			// remove & call to_score :
                linkTrail();
        		scoreUpdate(sameColored); //will update the currentScore
    		}
    		which();
            frogColor();
        }

        //------------display------------
        if(!isFinished())
        {
            window.clear();
            screenLoad();
            window.display();
        }
        else
        {
            gameOver();
        }
    }
}
void which()
{
    int i;
    for(i=0;i<2*ROWS-2+COLS;i++)
        if(TS.COLOR[i]!=0)
        {
            begginingWith=i;
            break;
        }
}
void setFree()
{
    int i;
    for(i=0;i<2*ROWS-2+COLS;i++)
    {
        TS.X[i]=0;
        TS.Y[i]=0;
        TS.COLOR[i]=0;
    }
}
void preStart()
{
    escapePressed=false;
    isOpenForTheFirst=true;
    mute=false;
    hitIndex;
    counter=0;
    BLUE=0,YELLOW=0,RED=0,GREEN=0; //FIRST BULLET COLOR COUNTER (USEFULL FOR INITIALIZE)
    newX,newY;
    //***death=0;                       //COUNTS TRAVERSED STEPS TOWARD THE SKULL
    currentNumberOfBullets=10;     //REMAINED BULLETS
    Mouse_X=0;                     //CURRENT X POSITION OF THE MOUSE
    Mouse_Y=0;                     //CURRENT Y POSITION OF THE MOUSE
    toShootColor=0;                //COLOR OF "TO_SHOOT" BULLET
    TAN=1;                      //TAN OF THE ORIENTION OF  "TOSHOOT" BULLET
    TETHA=45;                    // DEGREE OF TAN
    RADIAN;
    currentScore=0;                  //CURRENT SCORE
    won=false;					   //WINNING STATE
    sameColored=0;                 //NUMBER OF THE SAMECOLORED BULLETS(WILL BE INITIALIZED IN RESEMBLANCECHECK)
    begginingWith=0;               //will Specify Which element is at the beggining?
    frogSays="Nice !";          //WHAT THE FROG SAYS!!!
    int temp;
	//***death=0;
	won=false;
	for(int j=0;j<10;j++)
    {
        TS.X[j]=numToResX(114);
        TS.Y[j]=numToResY(908)-j*numToResY(92);
        //color initializing :
        TS.COLOR[j]=j%4+1;//getRandomColor();
    }

	frogColor();
}
void frogColor()
{
    toShootColor=getRandomColor();
}
int getRandomColor()
{
    reGet:
    int temp=rand()%100+1;
    if(temp%4==0)
        return 1;
    else if(temp%5==0)
        return 2;
    else if(temp%6==0)
        return 3;
    else if(temp%7==0)
        return 4;
    else
        goto reGet;
}
void shiftBullet(int a,string b)
{
    if(b=="UP")
    {

        TS.X[a+1]=TS.X[a];
        TS.Y[a+1]=TS.Y[a]-numToResY(2); //***was 92
        TS.COLOR[a+1]=TS.COLOR[a];
        //usefull for the first element (start element)
        TS.X[a]=0;
        TS.Y[a]=0;
        TS.COLOR[a]=0;
    }
    else if(b=="RIGHT")
    {
        TS.X[a+1]=TS.X[a]+numToResX(2); //***was 114
        TS.Y[a+1]=TS.Y[a];
        TS.COLOR[a+1]=TS.COLOR[a];
        //usefull for the first element (start element)
        TS.X[a]=0;
        TS.Y[a]=0;
        TS.COLOR[a]=0;
    }
    else if(b=="BOTTOM")
    {
        TS.X[a+1]=TS.X[a];
        TS.Y[a+1]=TS.Y[a]+numToResY(2); //***was 92
        TS.COLOR[a+1]=TS.COLOR[a];
        //usefull for the first element (start element)
        TS.X[a]=0;
        TS.Y[a]=0;
        TS.COLOR[a]=0;
    }

}
void scoreUpdate (int sameColored)
{
    currentScore+=sameColored*toShootColor*10;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void shootingSimulation()
{

    int i=1;
    bool notHit=true;
    RADIAN=PI/180*TETHA;
        do
        {
        toShootBullet.move((newX<0 ? -45*cos(RADIAN) : +45*cos(RADIAN-PI)  ),45*sin(RADIAN+PI));
        drawPlease();
        window.draw(toShootBullet);
        window.display();
        for(int j=begginingWith;j<begginingWith+currentNumberOfBullets;j++)
        {

           if(getDistance(toShootBullet.getPosition(),CIRCLES[j].getPosition())   <=75)
           {
               hitIndex=j;
               placement(j);
               notHit=false;
               break;
           }
        }
        }while(toShootBullet.getPosition().x<=numToResX(1910) && toShootBullet.getPosition().x>=numToResX(0) &&  toShootBullet.getPosition().y>=numToResY(0) && notHit);
    which();

}
void placement(int hitIndex)
{

    int hitXTemp=TS.X[hitIndex];//***CIRCLES[hitIndex].getPosition().x;
    int hitYTemp=TS.Y[hitIndex];//***CIRCLES[hitIndex].getPosition().y;
    for(int i=begginingWith+currentNumberOfBullets-1;i>=hitIndex;i--)
   	{
   		if(TS.X[i]==numToResX(114)  && TS.Y[i]>=numToResY(80) && TS.Y[i]<=numToResY(1080) )
        {
            if(TS.Y[i]>=172)
            {
                //***shiftBullet(i,"UP");  //just was this line!!!
                TS.X[i+1]=TS.X[i];
                TS.Y[i+1]=TS.Y[i]-numToResY(92);
                TS.COLOR[i+1]=TS.COLOR[i];
                //useful for the first element (start element)
                TS.X[i]=0;
                TS.Y[i]=0;
                TS.COLOR[i]=0;
                cout<<"UPPED!\n";
            }
            else
            {

                TS.Y[i+1]=TS.Y[i]-(TS.Y[i]-80);
                TS.X[i+1]=TS.X[i]+(92-TS.Y[i]+80);
                TS.COLOR[i+1]=TS.COLOR[i];
                //useful for the first element (start element)
                TS.X[i]=0;
                TS.Y[i]=0;
                TS.COLOR[i]=0;
                cout<<"UPPED!\n";
            }
        }
        else if(TS.Y[i]==numToResY(80) && TS.X[i]>=numToResX(114) && TS.X[i]<numToResX(1710))
        {

            if(TS.X[i]<1618)
            {
                //***shiftBullet(i,"RIGHT");//***just was this line
                TS.X[i+1]=TS.X[i]+numToResX(92); //***was 114
                TS.Y[i+1]=TS.Y[i];
                TS.COLOR[i+1]=TS.COLOR[i];
                //usefull for the first element (start element)
                TS.X[i]=0;
                TS.Y[i]=0;
                TS.COLOR[i]=0;
                cout<<"RIGHTED!\n";
            }
            else
            {

                //***shiftBullet(i,"RIGHT");//***just was this line
                TS.X[i+1]=TS.X[i]+(1710-TS.X[i]); //***was 114
                TS.Y[i+1]=TS.Y[i]+(92-1710+TS.X[i]);
                TS.COLOR[i+1]=TS.COLOR[i];



                //usefull for the first element (start element)
                TS.X[i]=0;
                TS.Y[i]=0;
                TS.COLOR[i]=0;
                cout<<"RIGHTED!\n";
            }


        }
        else if(TS.X[i]==numToResX(1710) && TS.Y[i]>numToResY(80) && TS.Y[i] <= numToResY(1080))
        {
            //***shiftBullet(i,"BOTTOM");  //***just was this line
            TS.X[i+1]=TS.X[i];
            TS.Y[i+1]=TS.Y[i]+numToResY(92); //***was 92
            TS.COLOR[i+1]=TS.COLOR[i];
            //usefull for the first element (start element)
            TS.X[i]=0;
            TS.Y[i]=0;
            TS.COLOR[i]=0;
            cout<<"BOTTOMED!\n";
        }
    }
    cout<<"________________________________________\n";
    TS.COLOR[hitIndex]=toShootColor ;
    TS.X[hitIndex]=hitXTemp;
    TS.Y[hitIndex]=hitYTemp;
    //***death++;
    currentNumberOfBullets++;
}
void linkTrail()
{
    int m=findTheFirst();
    int last_index_before_the_first_shift=begginingWith+currentNumberOfBullets-1;
    //place to back :
    for(int j=1;j<=sameColored;j++)
    {
        for(int i=m;i<=(last_index_before_the_first_shift);i++)
        {
            //up
            if(TS.X[i]==numToResX(1710)  && TS.Y[i]>numToResY(80) && TS.Y[i]<=numToResY(1080) )
            {
                if(TS.Y[i]<=172)
                {
                    TS.Y[i-1]=TS.Y[i]-(TS.Y[i]-80);
                    TS.X[i-1]=TS.X[i]-(92-TS.Y[i]+80);
                    TS.COLOR[i-1]=TS.COLOR[i];
                    //usefull for the first element (start element)
                    TS.X[i]=0;
                    TS.Y[i]=0;
                    TS.COLOR[i]=0;
                }
                else
                {
                    TS.X[i-1]=TS.X[i];
                    TS.Y[i-1]=TS.Y[i]-numToResY(92);
                    TS.COLOR[i-1]=TS.COLOR[i];
                    //usefull for the first element (start element)
                    TS.X[i]=0;
                    TS.Y[i]=0;
                    TS.COLOR[i]=0;
                }

            }
            //bottom
            if(TS.X[i]==numToResX(114) && TS.Y[i]>=numToResY(80) && TS.Y[i] <= numToResY(1080))
            {
                TS.X[i-1]=TS.X[i];
                TS.Y[i-1]=TS.Y[i]+numToResY(92);
                TS.COLOR[i-1]=TS.COLOR[i];
                //usefull for the first element (start element)
                TS.X[i]=0;
                TS.Y[i]=0;
                TS.COLOR[i]=0;
            }
            //left
            else if(TS.Y[i]==numToResY(80) && TS.X[i]>=numToResX(114) && TS.X[i]<numToResX(1920))
            {
                if(TS.X[i]>206)//*****was194
                {
                    TS.X[i-1]=TS.X[i]-numToResX(92);//***was 114
                    TS.Y[i-1]=TS.Y[i];
                    TS.COLOR[i-1]=TS.COLOR[i];
                    //usefull for the first element (start element)
                    TS.X[i]=0;
                    TS.Y[i]=0;
                    TS.COLOR[i]=0;
                }
                else
                {
                    TS.X[i-1]=TS.X[i]-(TS.X[i]-114);
                    TS.Y[i-1]=TS.Y[i]+(92-TS.X[i]+114);
                    TS.COLOR[i-1]=TS.COLOR[i];

                    //usefull for the first element (start element)
                    TS.X[i]=0;
                    TS.Y[i]=0;
                    TS.COLOR[i]=0;
                }
            }
        }


        m--;
        last_index_before_the_first_shift--;

    }
//***    death-=sameColored;
    currentNumberOfBullets-=sameColored;
    which();
}
bool  isFinished ()
{
    //cout<<"last y : "<<TS.Y[begginingWith+currentNumberOfBullets-1]<<endl;
    if((currentNumberOfBullets==0 )|| (TS.X[begginingWith+currentNumberOfBullets-1]==1710 && TS.Y[begginingWith+currentNumberOfBullets-1]>=867))
    {
        if(currentNumberOfBullets==0)
            won=true;
        else
            won=false;
        return true;
    }
    return false;
}
void  gameOver()
{
    while (window.isOpen())
    {

            Mouse_X=sf::Mouse::getPosition().x;
            Mouse_Y=sf::Mouse::getPosition().y;
            while (window.pollEvent(event))
            {
                switch(event.type)
                {
                    case sf::Event::MouseMoved :
                    {
                        if(Mouse_X>=625 && Mouse_X <=735 && Mouse_Y>=770 && Mouse_Y<=820)
                            exitText.setColor(sf::Color::Red);
                        else
                            exitText.setColor(sf::Color::White);
                        if(Mouse_X>=985 && Mouse_X <=1205 && Mouse_Y>=770 && Mouse_Y<=820)
                            restartText.setColor(sf::Color::Green);
                        else
                            restartText.setColor(sf::Color::White);
                    }
                    break;
                    case sf::Event::MouseButtonPressed:
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            if(Mouse_X>=625 && Mouse_X <=735 && Mouse_Y>=770 && Mouse_Y<=820)
                                exitZuma();
                            else if(Mouse_X>=985 && Mouse_X <=1205 && Mouse_Y>=770 && Mouse_Y<=820)
                            {
                                setFree();
                                preStart();
                                playZuma();
                            }
                        }
                    break;
                    case sf::Event::KeyPressed:
                        switch(event.key.code)
                        {
                            case sf::Keyboard::Escape:
                                window.close();
                                exit(0);
                                break;
                        }
                    break;
                }
            }
        window.clear();
        gameOverDraw();
        window.display();
    }
}
void gameOverDraw()
{
       gameoverbackSprite.setTexture(gameoverbackTexture);
       gameoverbackSprite.setPosition(numToResX(0),numToResY(0));
       gameoverbackSprite.setScale(numToResX(1),numToResY(1));
       exitText.setFont(ARIAL_FONT);
       exitText.setCharacterSize(70);
       exitText.setString("Exit");
       exitText.setPosition(numToResX(620),numToResY(750));
       restartText.setFont(ARIAL_FONT);
       restartText.setCharacterSize(70);
       restartText.setString("Restart");
       restartText.setPosition(numToResX(980),numToResY(750));
       gameOverText.setFont(ARIAL_FONT);
       gameOverText.setCharacterSize(75);
       gameOverText.setString("GameOver");
       gameOverText.setPosition(numToResX(735),numToResY(97));
       gameOverText.setColor(sf::Color::Yellow);
       tScoreText.setFont(ARIAL_FONT);
       tScoreText.setCharacterSize(38);
       tScoreText.setString("Total Score : ");
       tScoreText.setPosition(numToResX(795),numToResY(527));
       tScoreText.setColor(sf::Color::White);
       scoreText.setFont(ARIAL_FONT);
       scoreText.setCharacterSize(38);
       scoreText.setString(toString(currentScore));
       scoreText.setPosition(numToResX(1010),numToResY(527));
       scoreText.setColor(sf::Color::White);

       window.draw(gameoverbackSprite);
       window.draw(exitText);
       window.draw(restartText);
       window.draw(gameOverText);
       window.draw(tScoreText);
       window.draw(scoreText);
       if(won)
       {
            wonText.setFont(ARIAL_FONT);
            wonText.setCharacterSize(45);
            wonText.setString("You Win ! ");
            wonText.setPosition(numToResX(835),numToResY(395));
            wonText.setColor(sf::Color::Green);
            window.draw(wonText);
            window.draw(scoreText);
       }
       else
       {
            wonText.setFont(ARIAL_FONT);
            wonText.setCharacterSize(45);
            wonText.setString("You lose ! ");
            wonText.setPosition(numToResX(835),numToResY(395));
            wonText.setColor(sf::Color::Red);
            window.draw(wonText);
       }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double setShootOriention(int x,int y)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    newX=  x- numToResX(929);
    newY=numToResY(964)-y;
    if(newX!=0)
        return (float)(newY)/newX;
    return 1000;
}
void exitZuma()
{
    window.close();
    exit(0);
}
void screenLoad()
{
        sf::RectangleShape col1(sf::Vector2f(numToResX(930),numToResY(5)));
        sf::RectangleShape col2(sf::Vector2f(numToResX(830),numToResY(5)));

        col1.rotate(90);
        col1.setPosition(numToResX(105),numToResY(70));
        col2.rotate(90);
        col2.setPosition(numToResX(215),numToResY(170));
        sf::RectangleShape col3(sf::Vector2f(numToResX(830),numToResY(5)));
        col3.rotate(90);
        col3.setPosition(numToResX(1705),numToResY(170));
        sf::RectangleShape col4(sf::Vector2f(numToResX(930),numToResY(5)));
        col4.rotate(90);
        col4.setPosition(numToResX(1815),numToResY(70));
        sf::RectangleShape row1(sf::Vector2f(numToResX(1710),numToResY(5)));
        row1.rotate(0);
        row1.setPosition(numToResX(105),numToResY(70));
        sf::RectangleShape row2(sf::Vector2f(numToResX(1490),numToResY(5)));
        row2.rotate(0);
        row2.setPosition(numToResX(210),numToResY(170));
        sf::RectangleShape row3(sf::Vector2f(numToResX(115),numToResY(5)));
        row3.rotate(0);
        row3.setPosition(numToResX(100),numToResY(1000));
        sf::RectangleShape row4(sf::Vector2f(numToResX(1495),numToResY(2)));
        row4.rotate(0);
        row4.setPosition(numToResX(215),numToResY(1003));
        sf::RectangleShape row5(sf::Vector2f(numToResX(115),numToResY(5)));
        row5.rotate(0);
        row5.setPosition(numToResX(1700),numToResY(1000));


        backgroundSprite.setPosition(numToResX(0),numToResY(0));

        window.draw(backgroundSprite);

        for(int i=begginingWith+currentNumberOfBullets-1;i>=begginingWith;i--)
        {
            if(TS.COLOR[i]!=0)
            {
                CIRCLES[i].setRadius(numToResX(43));
                CIRCLES[i].setFillColor(toColor(TS.COLOR[i]));
                CIRCLES[i].setPosition(numToResX(TS.X[i]),numToResY(TS.Y[i]));
                window.draw(CIRCLES[i]);
            }
        }
        frogSprite.setPosition(numToResX(807),numToResY(805));
        //arrowSprite.setPosition(numToResX(810),numToResY(1000));
        arrowSprite.setPosition(numToResX(910),numToResY(950));
        arrowSprite.setScale(numToResX(0.9),numToResY(0.9));
        arrowSprite.setOrigin(numToResX(370),numToResY(145));
        arrowSprite.setRotation(TETHA);
        skullSprite.setPosition(numToResX(1700),numToResY(867));
        skullSprite.setScale(numToResX(0.18),numToResY(0.17));
        startText.setFont(ARIAL_FONT);
        startText.setString("Live");
        startText.setPosition(numToResX(124),numToResY(1020));
        finishText.setFont(ARIAL_FONT);
        finishText.setString("Death");
        finishText.setPosition(numToResX(1716),numToResY(1020));
        scoreWordText.setFont(ARIAL_FONT);
        scoreWordText.setString("SCORE : ");
        scoreWordText.setPosition(numToResX(1588),numToResY(20));
        scoreText.setFont(ARIAL_FONT);
        scoreText.setString(toString(currentScore));
        scoreText.setPosition(numToResX(1725),numToResY(20));
        scoreText.setColor(sf::Color::White);
        playerWordText.setFont(ARIAL_FONT);
        //playerWordText.setCharacterSize(57);
        playerWordText.setString("Player : ");
        playerWordText.setPosition(numToResX(112),numToResY(22));
        playerWordText.setColor(sf::Color::White);
        playerText.setFont(BEAUTY_FONT);
        playerText.setCharacterSize(numToResX(57));
        playerText.setString("Alexander Anderson");
        playerText.setPosition(numToResX(236),numToResY(0));
        playerText.setColor(sf::Color::White);
        frogText.setFont(ARIAL_FONT);
        frogText.setString(frogSays);
        frogText.setPosition(numToResX(885),numToResY(1020));
        toShootBullet.setRadius(numToResX(43));
        toShootBullet.setFillColor(toColor(toShootColor));
        toShootBullet.setPosition(numToResX(884),numToResY(920));

        window.draw(col1);
        window.draw(col1);
        window.draw(col2);
        window.draw(col3);
        window.draw(col4);
        window.draw(row1);
        window.draw(row2);
        window.draw(row3);
        window.draw(row4);
        window.draw(row5);
        window.draw(frogSprite);
        window.draw(skullSprite);
        window.draw(arrowSprite);
        window.draw(startText);
        window.draw(finishText);
        window.draw(scoreWordText);
        window.draw(scoreText);
        window.draw(playerWordText);
        window.draw(playerText);
        window.draw(frogText);

        window.draw(toShootBullet);

}

sf::Color toColor(int number)
{
    switch(number)
    {
        case 1: return sf::Color::Blue;  break;
        case 2: return sf::Color::Yellow;break;
        case 3: return sf::Color::Red;   break;
        case 4: return sf::Color::Green; break;
    }
    //no worries!!! the following line won't be run because our random number is always between 1 and 4
    return sf::Color::White;
}
double numToResX(double x)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    return (x*desktop.width/1920);
}
double numToResY(double y)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    return (y*desktop.height/1080);
}
string toString(int num)
{
    ostringstream oss;
    oss<< num;
    return oss.str();
}
void drawPlease()
{
        sf::RectangleShape col1(sf::Vector2f(numToResX(930),numToResY(5)));
        sf::RectangleShape col2(sf::Vector2f(numToResX(830),numToResY(5)));
        sf::RectangleShape col3(sf::Vector2f(numToResX(830),numToResY(5)));
        sf::RectangleShape col4(sf::Vector2f(numToResX(930),numToResY(5)));
        sf::RectangleShape row1(sf::Vector2f(numToResX(1710),numToResY(5)));
        sf::RectangleShape row2(sf::Vector2f(numToResX(1490),numToResY(5)));
        sf::RectangleShape row3(sf::Vector2f(numToResX(115),numToResY(5)));
        sf::RectangleShape row4(sf::Vector2f(numToResX(1495),numToResY(2)));
        sf::RectangleShape row5(sf::Vector2f(numToResX(115),numToResY(5)));
        col1.rotate(90);
        col1.setPosition(numToResX(105),numToResY(70));
        col2.rotate(90);
        col2.setPosition(numToResX(215),numToResY(170));

        col3.rotate(90);
        col3.setPosition(numToResX(1705),numToResY(170));

        col4.rotate(90);
        col4.setPosition(numToResX(1815),numToResY(70));

        row1.rotate(0);
        row1.setPosition(numToResX(105),numToResY(70));

        row2.rotate(0);
        row2.setPosition(numToResX(210),numToResY(170));

        row3.rotate(0);
        row3.setPosition(numToResX(100),numToResY(1000));

        row4.rotate(0);
        row4.setPosition(numToResX(215),numToResY(1003));

        row5.rotate(0);
        row5.setPosition(numToResX(1700),numToResY(1000));

        window.draw(backgroundSprite);
        window.draw(col1);
        window.draw(col2);
        window.draw(col3);
        window.draw(col4);
        window.draw(row1);
        window.draw(row2);
        window.draw(row3);
        window.draw(row4);
        window.draw(row5);
        window.draw(frogSprite);
        window.draw(skullSprite);
        window.draw(arrowSprite);
        window.draw(startText);
        window.draw(finishText);
        window.draw(scoreWordText);
        window.draw(scoreText);
        window.draw(playerWordText);
        window.draw(playerText);
        window.draw(frogText);
        for(int i=begginingWith+currentNumberOfBullets-1;i>=begginingWith;i--)
        {
            if(TS.COLOR[i]!=0)
            {
                CIRCLES[i].setRadius(numToResX(43));
                CIRCLES[i].setFillColor(toColor(TS.COLOR[i]));
                CIRCLES[i].setPosition(numToResX(TS.X[i]),numToResY(TS.Y[i]));
                window.draw(CIRCLES[i]);
            }
        }

}
double getDistance(Vector2f d1,Vector2f d2)
{
    Vector2f dif=d1-d2;
    return sqrt(dif.x*dif.x+dif.y*dif.y);
}
int findTheFirst()
{
    for(int i=hitIndex;i<begginingWith+currentNumberOfBullets;i++)
    {
        if(TS.COLOR[i]!=toShootColor)
            return i;
    }
}
bool  resemblanceCheck()
{
    sameColored=0;
    for(int i=begginingWith;i<begginingWith+currentNumberOfBullets;i++)
    {
        sameColored=0;
        for(int j=i;TS.COLOR[j]==TS.COLOR[i];j++,sameColored++);
        if(sameColored>=3)
            return true;
    }
    return false;

}
void loadGame()
{

}
//FINISHED

