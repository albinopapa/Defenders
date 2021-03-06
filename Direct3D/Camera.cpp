
#include "Camera.h"


Camera::Camera(float width, float height)
	:
	pos({ 0.0f,0.0f }),
	center({ width / 2.0f,height / 2.0f }),
	screen_width(width),
	screen_height(height)
{
	viewFrame.left = pos.x;
	viewFrame.top = pos.y;
	viewFrame.right = viewFrame.left + screen_width;
	viewFrame.bottom = viewFrame.top + screen_height;
	Resize(width, height);
	scroll_pos = center;
}
void Camera::Scroll(Vec2f& dir)
{
	
	scroll_pos += dir;
	if (scroll_pos.x < center.x)scroll_pos.x = center.x;
	if (scroll_pos.x > mapFrame.right -center.x)scroll_pos.x = mapFrame.right - center.x;
	if (scroll_pos.y < center.y)scroll_pos.y = center.y;
	if (scroll_pos.y > mapFrame.bottom - center.y)scroll_pos.y = mapFrame.bottom - center.y;

	this->UpdatePosition(scroll_pos);

}


Vec2f Camera::GetPos() { return pos; }
void Camera::ConfineToMap(RectF& map_frame) { mapFrame = map_frame; };
Vec2f Camera:: ConvertToWorldSpace(Vec2f in_pos)
{
	Vec2f pt(in_pos + this->pos);
	if (PointInViewFrame(pt, { 0.0f,0.0f }))
	{
		return pt;
	}
	return Vec2f(-1.0f, -1.0f);
}
bool Camera::PointInViewFrame(Vec2f pt, const Vec2f& offset)
{
	return pt.x > viewFrame.left + -offset.x && pt.x < viewFrame.right + offset.x &&
		pt.y > viewFrame.top + -offset.y && pt.y < viewFrame.bottom + offset.y;
}
void Camera::Resize(float& w, float& h)
{
	screen_width = w;
	screen_height = h;
	center = Vec2f(screen_width / 2, screen_height / 2);
	viewFrame.left = pos.x;
	viewFrame.top = pos.y;
	viewFrame.right = viewFrame.left + screen_width;
	viewFrame.bottom = viewFrame.top + screen_height;

};

void Camera::UpdatePosition(Vec2f& in_pos)
{
	pos = in_pos - center ;
	
	pos.x = __max(pos.x, mapFrame.left);
	pos.y = __max(pos.y, mapFrame.top);
	pos.x = __min(pos.x, mapFrame.right - screen_width);
	pos.y = __min(pos.y, mapFrame.bottom - screen_height);
	pos.y = __max(pos.y, 0.0f);

	viewFrame.left = pos.x;
	viewFrame.top = pos.y;
	viewFrame.right = viewFrame.left + screen_width;
	viewFrame.bottom = viewFrame.top + screen_height;
}
