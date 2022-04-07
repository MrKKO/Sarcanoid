#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ball.h"
#include "klocek.h"
#include <string>

using namespace std;
using namespace sf;



void Enterscreen(string text,RenderWindow& window,string pkt) {
    Event event;
    bool end = true;
    Text pole_gry;
    Text tpkt;
    Font font;
    font.loadFromFile("arial.ttf");
    pole_gry.setFont(font);
    pole_gry.setString(text); 
    FloatRect textRect = pole_gry.getLocalBounds();
    pole_gry.setOrigin(textRect.width / 2, textRect.height / 2);
    pole_gry.setPosition(400, 300);

    tpkt.setString(pkt);
    tpkt.setFont(font);
    textRect = tpkt.getLocalBounds();
    tpkt.setOrigin(textRect.width / 2, textRect.height / 2);
    tpkt.setPosition(400, 350);
    while (end)
    {
        window.clear(Color::Black);
        window.pollEvent(event);
        if (event.type == Event::Closed) {
            window.close();
            break;
        }
        if (event.type == Event::Closed) {

        }
        if (Keyboard::isKeyPressed(Keyboard::Enter)) { end = false; }
        window.draw(pole_gry);
        window.draw(tpkt);
        window.display();
    }
}

int main()
{
    RenderWindow window(VideoMode(800, 600), "Okienko nazwa");
    window.setFramerateLimit(60);

    const float tbasevelo=4.f;
    float tvelocitx= 4.0f;

    Event event;
    Texture t;
    t.loadFromFile("sanah22.png");
    Sprite s(t);
    float obgry[4] = { 0,1000,0,600};
    float granica = 5;
    int zyca = 3;
    int pkt = 0;

    const int iloscball = 2;
    const int ilosckloc = 4;
    

    klocek tab[ilosckloc] = {klocek(400,500,true,80.0f,20.0f),klocek(400,200,false,20.0f,80.0f),klocek(500,200,false,80.0f,20.0f),
        klocek(600,200,false,20.0f,80.0f)};
    Ball tabball[iloscball] = { Ball(200,500) , Ball(30,60)};
    
    


    Text pole_gry;
    Font font;
    font.loadFromFile("arial.ttf");
    
    pole_gry.setFont(font);
    pole_gry.setFillColor(Color::Blue);
    pole_gry.setCharacterSize(24);
    pole_gry.setStyle(Text::Bold);

    Text pole_gry2;
    pole_gry2.setPosition(7,7);
    pole_gry2.setFont(font);
    pole_gry2.setFillColor(Color::Blue);
    pole_gry2.setCharacterSize(24);
    pole_gry2.setStyle(Text::Bold);

    Text pole_gry3;
    pole_gry3.setPosition(750, 0);
    pole_gry3.setFont(font);
    pole_gry3.setFillColor(Color::Green);
    pole_gry3.setCharacterSize(24);
    pole_gry3.setStyle(Text::Bold);


    Enterscreen("Press Enter to Start",window,"");

    pole_gry.setOrigin(0,0);
    pole_gry.setPosition(5,5);

    while (zyca>0) {
        window.clear(Color::Black);
        window.pollEvent(event);
        if (event.type == Event::Closed) {
            window.close();
            break;
        }
        if (event.type == Event::Closed) {

        }
        if (tab[0].update(obgry[0], obgry[1],granica) == false || tvelocitx != 0) {
            if (Keyboard::isKeyPressed(Keyboard::Key::Right) && obgry[1]>800) {
                tvelocitx = -tbasevelo;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Left) && obgry[0] <0) {
                tvelocitx = tbasevelo;
            }
            else {
                tvelocitx = 0;
            }
        }
        for (int i = 0; i < ilosckloc; i++) {
            for (int j = 0; j < iloscball; j++) {
                tabball[j].update(tab[i], obgry[0], obgry[1],granica);
            }
        }
        s.move(tvelocitx, 0);
        obgry[0] += tvelocitx;
        obgry[1] += tvelocitx;

        for (int i = 0; i < iloscball; i++) {
            tabball[i].sheap.move(tvelocitx, 0);
        }
        for (int i = 1; i < ilosckloc; i++) {
            tab[i].shape.move(tvelocitx, 0);
        }
        

        for (int i = 0; i < iloscball; i++) {
            tabball[i].move();
        }

        for (int i = 0; i < iloscball; i++) {
            switch (tabball[i].update(tab[0], obgry[0], obgry[1], granica))
            {
                case 1: zyca--; break;
                case 2: pkt++;  break;
                case 3: pkt++; zyca--; break;
                default:break;
            }
            
        }

        for (int i = 1; i < ilosckloc; i++) {
            for (int j = 0; j < iloscball; j++) {
                tabball[j].update(tab[i], obgry[0], obgry[1], granica);
            }
        }
        
        pole_gry2.setString("Pkt:" + to_string(pkt));
        pole_gry3.setString(to_string(zyca));
        window.draw(s);
        window.draw(pole_gry);
        window.draw(pole_gry2);
        window.draw(pole_gry3);
        for (int i = 0; i < ilosckloc; i++){ window.draw(tab[i]); }
        for (int i = 0; i < iloscball; i++) { window.draw(tabball[i]); }
        window.display(); 
        tvelocitx = 0;
    }
    

    Enterscreen("Game over", window,"punkty: "+to_string(pkt));
    

    return 0;
}


