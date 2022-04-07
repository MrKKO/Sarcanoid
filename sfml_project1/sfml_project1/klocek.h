#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;
class klocek:public sf::Drawable
{
public:
	klocek(float pozx, float pozy,bool mm,float width,float hight);

	bool tlo;
	bool update(float obgryl,float obgryp,float granica);
	float left();
	float right();
	float bottom();
	float top();
	bool motionmode;
	float klocekvelocity = 0.f;
	float klocekvelocitx = 0.0f;
	float klocekwidth;
	float klocekhight;
	RectangleShape shape;
private: 
	void draw(RenderTarget& target, RenderStates states)const override;
	
	const float basevelo = 4.0f;
	

};

