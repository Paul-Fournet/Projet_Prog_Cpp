#include "../Headers/main.hpp"
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;
using namespace sf;

Traffic_light::Traffic_light(const sf::Color& color, int type, const Vector2f& position) : color_(color), type_(type),position_(position) {
	shape.setRadius(10.f);
	shape.setFillColor(Color::Black);
	shape.setOrigin(shape.getRadius() / 2, shape.getRadius() / 2);
	shape.setPosition(position_);
}

Color Traffic_light::get_color() {
	return color_;
}
void Traffic_light::set_color(Color color) {
	std::lock_guard<std::mutex> lock(mtx);
	color_ = color;
	shape.setFillColor(color);

}


int Traffic_light::get_type() {
	return type_;
}
void Traffic_light::set_type(int type) {
	type_ = type;
}


Vector2f Traffic_light::get_position() {
	return position_;
}
void Traffic_light::set_position(Vector2f& position) {
	position_ = position;
	shape.setPosition(position);
}

CircleShape Traffic_light::return_traffic_light() const {	
	return shape;
}

void run_traffic_light(Traffic_light& tlHG, Traffic_light& tlHD, Traffic_light& tlVH, Traffic_light& tlVB, int time_on, int time_transition) {

	Clock clock;
	Time time_elapsed = clock.getElapsedTime();

	Time time_ON = seconds(time_on);
	Time time_TRANSITION = seconds(time_transition);
	
	clock.restart();
	while (true) {
		while (clock.getElapsedTime() < time_ON) {
			time_elapsed = clock.getElapsedTime();
			tlHG.set_color(Color::Green);
			tlHD.set_color(Color::Green);

			tlVH.set_color(Color::Red);
			tlVB.set_color(Color::Red);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		clock.restart();

		while (clock.getElapsedTime() < time_TRANSITION) {
			time_elapsed = clock.getElapsedTime();
			tlHG.set_color(Color::Yellow);
			tlHD.set_color(Color::Yellow);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		clock.restart();

		while (clock.getElapsedTime() < time_ON) {
			time_elapsed = clock.getElapsedTime();
			tlHG.set_color(Color::Red);
			tlHD.set_color(Color::Red);

			tlVH.set_color(Color::Green);
			tlVB.set_color(Color::Green);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		clock.restart();

		while (clock.getElapsedTime() < time_TRANSITION) {
			time_elapsed = clock.getElapsedTime();
			tlVH.set_color(Color::Yellow);
			tlVB.set_color(Color::Yellow);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	


}