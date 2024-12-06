#include "../Headers/main.hpp"
#include "../Headers/classes.hpp"
#include <iostream>


Car::Car(int voie,Texture& texture,RenderWindow& window,std::vector<Car*>& vect_cars) : voie_(voie), vect_cars_(vect_cars){
	
	type_ = 0;
	n_speed_ = CAR_SPEED;
	started_ = true;
	
	Sprite sprite_voiture(texture);
	sprite_voiture.setScale((float)0.015, (float)0.015);
	//sprite_voiture.setPosition();			A MODIFIER

	if (voie == 1) {
		sprite_voiture.setPosition(window.getSize().x * VOIE_C1_X,window.getSize().y * VOIE_C1_Y);
		sprite_voiture.rotate(90);
	}
	if (voie == 2) {
		sprite_voiture.setPosition(window.getSize().x * VOIE_C2_X,window.getSize().y* VOIE_C2_Y);
		sprite_voiture.rotate(180);
	}
	if (voie == 3) {
		sprite_voiture.setPosition(window.getSize().x * VOIE_C3_X, window.getSize().y * VOIE_C3_Y);
		sprite_voiture.rotate(270);
	}
	if (voie == 4) {
		sprite_voiture.setPosition(window.getSize().x * VOIE_C4_X,window.getSize().y * VOIE_C4_Y);
	}

	sprite_voiture.setOrigin(sprite_voiture.getLocalBounds().width / 2, sprite_voiture.getLocalBounds().height / 2);

	sprite_ = sprite_voiture;

	vect_cars.push_back(this);

}

Car::~Car() {
	auto mycar_it = find(vect_cars_.begin(), vect_cars_.end(), this);
	if (mycar_it != vect_cars_.end()) {
		vect_cars_.erase(mycar_it);
	}	
}

int Car::get_type() {
	return type_;
}

int Car::get_voie() {
	return voie_;
}

float Car::get_n_speed() {
	return n_speed_;
}

Sprite& Car::return_sprite() {

	Sprite& ref_sprite = sprite_;

	return ref_sprite;
}

void Car::forward(int delay, float speed,Clock& clock) {

	if (clock.getElapsedTime().asMilliseconds() > delay) {
		clock.restart();

		if (voie_ == 1) {
			sprite_.move(n_speed_, 0);
		}
		if (voie_ == 2) {
			sprite_.move(0, n_speed_);
		}
		if (voie_ == 3) {
			sprite_.move(-n_speed_, 0);
		}
		if (voie_ == 4) {
			sprite_.move(0, -n_speed_);
		}
	}
}



bool isVehicleInRectangle(const sf::Sprite& vehicle_sprite, const sf::RectangleShape& rect) {
	return rect.getGlobalBounds().contains(vehicle_sprite.getPosition());
}


bool can_pass(Car* car, Traffic_light& feu,RectangleShape& rect) {

	bool cond = false;
	bool feu_vert = false;
	bool in_rect = false;
	bool intesects = false;
	float dist_x = DIST_MIN_CAR;
	float dist_y = DIST_MIN_CAR;


	for (auto& other_car : car->vect_cars_) {

		if ((other_car->return_sprite().getGlobalBounds() != car->return_sprite().getGlobalBounds())) {
			
			dist_x = abs(car->return_sprite().getPosition().x - other_car->return_sprite().getPosition().x);
			dist_y = abs(car->return_sprite().getPosition().y - other_car->return_sprite().getPosition().y);

			if (dist_x < DIST_MIN_CAR && dist_y < DIST_MIN_CAR) {
				if (feu.get_color() != Color::Green) {
					return false;
				}
			}

			/*if (other_car->return_sprite().getGlobalBounds().intersects(car->return_sprite().getGlobalBounds())) {
				if (feu.get_color() == Color::Green) {
					cond = true;
				}
				else {
					return false;
				}
			}*/

			if ((!isVehicleInRectangle(car->return_sprite(), rect) || (feu.get_color() == Color::Green))) {
				cond = true;
			}

			
			



		}
	}

	if ((!isVehicleInRectangle(car->return_sprite(), rect) || (feu.get_color() == Color::Green))) {
		cond = true;
	}
	

	return cond;	

}



void car_start(Car* car,int delay,RenderWindow& window, std::vector<Traffic_light*>& vect_feux, std::vector<sf::RectangleShape*>& vect_rectangles) {
	
	Clock clock;
	
	window.setActive(false);

	bool to_die = false;
	int speed = car->get_n_speed();
	
	while (window.isOpen() && car->started_) {

		Traffic_light* feu = NULL;
		RectangleShape* rectangle = NULL;
		int voie = 0;

		voie = car->get_voie();



		//On associe à la voiture les feux qu'ils doivent respecter
		if (voie == 1) {
			feu = vect_feux.at(0);
			rectangle = vect_rectangles.at(0);
		}
		if (voie == 2) {
			feu = vect_feux.at(1);
			rectangle = vect_rectangles.at(1);
		}
		if (voie == 3) {
			feu = vect_feux.at(0);
			rectangle = vect_rectangles.at(2);
		}
		if (voie == 4) {
			feu = vect_feux.at(1);
			rectangle = vect_rectangles.at(3);
		}

		if (feu == NULL || rectangle == NULL) {
			return;
		}

		if (can_pass(car, *feu, *rectangle)) {
			//Accélérer jusqu'à la vitesse de croisière

			car->forward(delay, speed, std::ref(clock));
		}
		else{
			//Dccélérer jusqu'à l'arrêt complet

			
		}


		if (car->return_sprite().getGlobalBounds().top +car->return_sprite().getGlobalBounds().height< 0 || car->return_sprite().getGlobalBounds().left + car->return_sprite().getGlobalBounds().width< 0 || car->return_sprite().getGlobalBounds().top > window.getSize().y || car->return_sprite().getGlobalBounds().left > window.getSize().x) {
			clock.restart();
			car->started_ = false;
			cout << "Car unloaded" << endl;
			car->~Car();
			
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	
}



void add_car(int voie, vector<Car*>& vect_cars, vector<thread>& vect_threads,Texture texture_voiture,vector<Traffic_light*> vect_feux, vector<RectangleShape*> vect_rectangles, RenderWindow& window) {
	
	auto newcar = new Car(voie, texture_voiture, std::ref(window),std::ref(vect_cars));
	vect_cars.push_back(newcar);
	cout << "Car added, total cars :" << vect_cars.size() << endl;

	vect_threads.emplace_back(car_start, newcar, DELAY, std::ref(window), std::ref(vect_feux), std::ref(vect_rectangles));
}



bool is_lane_free(std::vector<Car*>& vect_cars, int voie) {

	int nbcar_voie = 0;

	for (auto& car : vect_cars) {
		if (car->get_voie() == voie) {
			nbcar_voie++;
		}
	}

	if (((voie == 2 || voie == 4) && nbcar_voie >= 4) || ((voie == 1 || voie == 3) && nbcar_voie >= 3)) {
		return false;
	}
	else {
		return true;
	}
}