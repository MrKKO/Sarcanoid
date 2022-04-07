#include "ball.h"

Ball::Ball(float t_x, float t_y) {
	sheap.setPosition(t_x, t_y);
	sheap.setRadius(this->ballRadius);
	sheap.setFillColor(Color::White);
	sheap.setOrigin(this->ballRadius, this->ballRadius);

}
void Ball::draw(RenderTarget& target, RenderStates state)const
{
	target.draw(this->sheap, state);

}
void Ball::move() {
	if (ballvelocityx >  5.f) { ballvelocityx =  5.f;}
	if (ballvelocityx < -5.f) { ballvelocityx = -5.f;}
	if (ballvelocityy >  5.f) { ballvelocityy =  5.f;}
	if (ballvelocityy < -5.f) { ballvelocityy = -5.f;}


	sheap.move(this->ballvelocityx, this->ballvelocityy);
}
int Ball::update(klocek k,float obgryl, float obgryp,float granica) {
	czypktd = false;
	czyll = false;
	if (this->left() <= obgryl+granica) { ballvelocityx = basevelo; }
	else if (this->right() >= obgryp-granica) { ballvelocityx = -basevelo; }
	//kolizje z krawêdziami (lewa,prawa)
	if (this->top() <= 0 + granica) { if (ballvelocityy<0) { czypktd = true; }  ballvelocityy = basevelo; }
	else if (this->bottom() >= 600 - granica) {if (ballvelocityy > 0) { czyll = true; } ballvelocityy = -basevelo;}
	//kolizje z krawêdziami(góra,dó³)

	if ((this->left() >= k.left() && this->left() <= k.right() )||(this->right() >= k.left() && this->right() <= k.right())) {
		if (this->bottom() >= k.top() && this->bottom() < k.top()+2*this->ballRadius)
		{
			ballvelocityy = -basevelo +k.klocekvelocity;
			ballvelocityx += k.klocekvelocitx;
		}
		else if (this->top() <= k.bottom() && this->top() > k.bottom()-2*this->ballRadius)
		{
			ballvelocityy = basevelo + k.klocekvelocity;
			ballvelocityx += k.klocekvelocitx;
		}
	} 
	//kolizja od do³u i góry
	if ((this->top() >= k.top() && this->top() <= k.bottom())|| (this->bottom() >= k.top() && this->bottom() <= k.bottom())) {
		if (this->right() >= k.left() && this->right() < k.left() + 5.f)
		{
			ballvelocityy += k.klocekvelocity;
			ballvelocityx = -basevelo + k.klocekvelocitx;
		}
		else if (this->left() <= k.right() && this->left() > k.right() - 5.f)
		{
			ballvelocityx = basevelo + k.klocekvelocitx;
			ballvelocityy += k.klocekvelocity;
		}
	}
	//kolizja od boków

	if (this->left() < k.right() && this->left() > k.right()-15.f && this->sheap.getPosition().y >= k.top() && this->sheap.getPosition().y <= k.bottom()) {
		sheap.setPosition(this->sheap.getPosition().x + this->ballRadius,this->sheap.getPosition().y);
		ballvelocityx = basevelo;
	}		
	//poprawa pozycji w przypadku wpadniêcia w obiekt(od lewej)
	if (this->right() > k.left() && this->right() < k.left() + 15.f && this->sheap.getPosition().y >= k.top() && this->sheap.getPosition().y <= k.bottom()) {
		sheap.setPosition(this->sheap.getPosition().x - this->ballRadius, this->sheap.getPosition().y);
		ballvelocityx = -basevelo;
	}
	//poprawa pozycji w przypadku wpadniêcia w obiekt(od prawej)
	if (this->top() < k.bottom() && this->top() > k.bottom() + 15.f && this->sheap.getPosition().x >= k.left() && this->sheap.getPosition().x <= k.right()) {
		sheap.setPosition(this->sheap.getPosition().x, this->sheap.getPosition().y + this->ballRadius);
		ballvelocityx = basevelo;
	}
	//poprawa pozycji w przypadku wpadniêcia w obiekt(z do³u)
	if (this->bottom() > k.top() && this->bottom() < k.top() - 15.f && this->sheap.getPosition().x >= k.left() && this->sheap.getPosition().x <= k.right()) {
		sheap.setPosition(this->sheap.getPosition().x, this->sheap.getPosition().y - this->ballRadius);
		ballvelocityx = -basevelo;
	}
	//poprawa pozycji w przypadku wpadniêcia w obiekt(z góry)

	if (this->right()>obgryp+50 || this->left() <obgryl-50 || this->top() < -50 || this->bottom()> 650){
		sheap.setPosition(400,300);
	}
	// reset gdy wypadnie poza obszargry
	
	if (czyll) {
		if (czypktd) { return 3; }else{ return 1; }
	}
	else {
		if (czypktd) { return 2; }else{ return 0; }
	}
}

float Ball::left() {
	return this->sheap.getPosition().x - this->sheap.getRadius();
}
float Ball::right() {
	return this->sheap.getPosition().x + this->sheap.getRadius();
}
float Ball::bottom() {
	return this->sheap.getPosition().y + this->sheap.getRadius();
}
float Ball::top() {
	return this->sheap.getPosition().y - this->sheap.getRadius();
}
