#include <SFML\Graphics.hpp>
#include "klocek.h"

using namespace sf;
class Ball : public Drawable
{
public:
	Ball(float t_x, float t_y);
	int update(klocek k, float odgryl, float obgryp,float granica);
	float left();//zwaraca lew¹ krawêdz obiektu
	float right();//zwaraca lew¹ krawêdz obiektu
	float bottom();//zwaraca lew¹ krawêdz obiektu
	float top();//zwaraca lew¹ krawêdz obiektu
	float klocekhit();
	
	void move();
	bool czypktd;
	bool czyll;
	CircleShape sheap;
private:
	
	const float ballRadius = 10.0f;
	const float basevelo = 2.0f;
	float ballvelocityx = 2.0f;
	float ballvelocityy = -2.0f;
	void draw(RenderTarget& target, RenderStates states)const override;

};
