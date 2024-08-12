#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <unordered_map>
#include <string>
#include "chessEngine.h"

using namespace std;
using namespace sf;



//Sprite f[32]; //figures
int intSize = 56;
Vector2f offset(28, 28);

int board[8][8] =
{ -1,-2,-3,-4,-5,-3,-2,-1,
 -6,-6,-6,-6,-6,-6,-6,-6,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  6, 6, 6, 6, 6, 6, 6, 6,
  1, 2, 3, 4, 5, 3, 2, 1 };


void loadPosition(vector<Sprite>& f, unordered_map<pair<int, int>, int, hash_pair>& um)
{
    int k = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            int n = board[i][j];
            if (!n) continue;
            int x = abs(n) - 1;
            int y = n > 0 ? 1 : 0;
            f[k].setTextureRect(IntRect(intSize * x, intSize * y, intSize, intSize));
            f[k].setPosition(intSize * j, intSize * i);
            um[{ i, j }] = k;
            k++;
        }
}

inline void drawFigures(vector<Sprite>& f, RenderWindow& window) {
    for (int i = 0; i < 32; i++) {
        f[i].move(offset);
        window.draw(f[i]);
        f[i].move(-offset);
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");

    ChessEngine ce;

    vector<Sprite> f(32);
    unordered_map<pair<int, int>, int, hash_pair> um;
    
    //Music soundMove;
    //soundMove.openFromFile("music/move.mp3");

    RenderWindow window(VideoMode(504, 504), "The Chess", Style::Close);
    //RenderWindow secondWindow(VideoMode(240, 320), "Noob");
    
    Image icon;
    icon.loadFromFile("images/smallFakt.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Texture t1, t2;
    t1.loadFromFile("images/figures.png");
    t2.loadFromFile("images/board.png");
    for (int i = 0; i < 32; i++) {
        f[i].setTexture(t1);
    }
    loadPosition(f, um);
    
    Sprite s(t1);
    Sprite sBoard(t2);

    bool isMove = false, isComp = false;
    float dx = 0, dy = 0;
    Vector2i prevPos;
    int n = 0;
    sf::Texture emptyTexture;
    emptyTexture.create(intSize, intSize);

    Colors col = Colors::white;

    int winOrLose = 0; // win == 1, lose == 2

    while (window.isOpen()) {
        Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);
        //cout << "\t" << pos.x << " " << pos.y << "\n";
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed || winOrLose != 0)
                window.close();
            
            // если тыгыдыкнули и держим ЛКМ*
            if (e.type == Event::MouseButtonPressed && e.key.code == Mouse::Left) {
                for (int i = 0; i < 32; i++) {
                    if (f[i].getGlobalBounds().contains(pos.x, pos.y)) {
                        isMove = true;
                        prevPos = pos;

                        n = i;
                        dx = pos.x - f[i].getPosition().x;
                        dy = pos.y - f[i].getPosition().y;
                    }
                }
            }
            // отпускаем ЛКМ
            else if (e.type == Event::MouseButtonReleased && e.key.code == Mouse::Left) {
                //soundMove.play();
                isMove = false;
                
                ce.setNextMove(prevPos.y / intSize, prevPos.x / intSize, pos.y / intSize, pos.x / intSize, col);

                int t21 = pos.y / intSize, t22 = pos.x / intSize;
                int t11 = prevPos.y / intSize, t12 = prevPos.x / intSize;


                if (board[t11][t12] > 0 && board[t21][t22] < 0 || board[t11][t12] < 0 && board[t21][t22] > 0) {
                    f[um[{pos.y / intSize, pos.x / intSize}]].setTexture(emptyTexture);
                    um.erase({ pos.y / intSize, pos.x / intSize });

                    board[pos.y / intSize][pos.x / intSize] = 0;
                }
                swap(board[t11][t12], board[t21][t22]);
                f[n].setPosition(intSize * t22, intSize * t21);
                um[{t21, t22}] = um[{t11, t12}];
                um.erase({ t11, t12 });

                //ce.printAttackBoard(black);
            }
            else if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Space) {
                    //soundMove.play();
                    retNewMove rnm = ce.makeNextMove(Colors::black);
                    if (rnm.bp == boardPieces::empt) {
                        winOrLose = 1;
                    }
                    else {
                        if (board[rnm.from1][rnm.from2] < 0 && board[rnm.to1][rnm.to2] > 0 ||
                            board[rnm.from1][rnm.from2] > 0 && board[rnm.to1][rnm.to2] < 0) {
                            f[um[{rnm.to1, rnm.to2}]].setTexture(emptyTexture);
                            um.erase({ rnm.to1, rnm.to2 });
                            board[rnm.to1][rnm.to2] = 0;
                        }
                        swap(board[rnm.from1][rnm.from2], board[rnm.to1][rnm.to2]);
                        f[um[{rnm.from1, rnm.from2}]].setPosition(intSize * rnm.to2, intSize * rnm.to1);
                        um[{rnm.to1, rnm.to2}] = um[{rnm.from1, rnm.from2}];
                        um.erase({ rnm.from1, rnm.from2 });
                    }
                    //ce.printAttackBoard(Colors::white);
                }

                // сдача (кэщбек)
                else if (e.key.code == Keyboard::BackSpace) {
                    winOrLose = 2;
                }
            }
        }
        if (isMove) {
            f[n].setPosition(pos.x - dx, pos.y - dy);
        }
        window.clear();
        window.draw(sBoard);
        drawFigures(f, window);
        window.display();
        if (winOrLose != 0) {
            RenderWindow secondWindow(VideoMode(360, 480), "Result");
            Texture st;
            
            Font font;
            font.loadFromFile("images/sunflower.otf");
            Text text;
            text.setFont(font);
            text.setCharacterSize(36);
            text.setPosition(135, 20);

            if (winOrLose == 1) {
                st.loadFromFile("images/win.png");
                text.setFillColor(Color::Blue);
                text.setString("Ez game");
            }
            else {
                st.loadFromFile("images/lose.png");
                text.setFillColor(Color::Black);
                text.setString("Potracheno!");
            }
            Sprite fon(st);
            
            Image icon2;
            icon2.loadFromFile("images/mipt.png");
            secondWindow.setIcon(icon2.getSize().x, icon2.getSize().y, icon2.getPixelsPtr());

            while (secondWindow.isOpen()) {
                Event e2;
                while (secondWindow.pollEvent(e2)) {
                    if (e2.type == Event::Closed)
                        secondWindow.close();
                }
                secondWindow.clear();

                secondWindow.draw(fon);
                secondWindow.draw(text);

                secondWindow.display();
            }
        }
    }


    return 0;
}
