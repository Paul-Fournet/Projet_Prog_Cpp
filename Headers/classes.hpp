#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>
#include <vector>
using namespace sf;
using namespace std;

//Couleurs des feux
enum class Traffic_color {
    green = 0,
    orange = 1,
    red = 2
};

Traffic_color operator++(Traffic_color& traffic_color);


class Traffic_light {
private:
    Color color_;
    int type_;//0 : horizontal       1 : vertical
    Vector2f position_;
    std::mutex mtx;//Mutex permettant de sécuriser l'accès au feu de circulation
    CircleShape shape;

public:
    Traffic_light(const sf::Color& color, int type, const Vector2f& position);
    Color get_color();
    void set_color(Color color);
    int get_type();
    void set_type(int type);
    Vector2f get_position();
    void set_position(Vector2f& position);
    Traffic_light operator++();
    std::mutex& get_mutex();
    CircleShape return_traffic_light() const;//Arguments à vérifier
};

void run_traffic_light(Traffic_light& tlHG, Traffic_light& tlHD, Traffic_light& tlVH, Traffic_light& tlVB,float time_on,float time_transition,RenderWindow& window);



class RoadUser {
protected:
    int type_ = 0;//0 : voiture, 1 : bus, 2 : piétons, 3 : vélos
    float n_speed_ = 0;
    Sprite sprite_;
public:
    virtual int get_type() = 0;
    virtual float get_n_speed() = 0;
    virtual Sprite& return_sprite() = 0;
    bool started_=true;
};


class Car : public RoadUser {
private:
    int voie_;
    /*
    1 : gauche à droide
    2 : haut en bas
    3 : droite à gauche
    4 : bas en haut
    */

public:
    Car(int voie, Texture& texture, RenderWindow& window);//La voie et la vitesse vont être déterminées automatiquement
    int get_type();
    int get_voie();
    float get_n_speed();
    void forward(int delay, float speed, Clock& clock);
    Sprite& return_sprite();
};

class Pedestrian : RoadUser
{
private:
    //voie....

public:
    Pedestrian();
    int get_type();
    float get_n_speed();
    Sprite& return_sprite();

};


void car_start(Car* car, int delay, RenderWindow& window, std::vector<Traffic_light*>& vect_feux, std::vector<RectangleShape*>& vect_rectangles);

//Fonction qui vérifie si une voiture/un bus est dans un rectangle d'arrêt :
bool isVehicleInRectangle(const sf::Sprite& vehicle_sprite, const sf::RectangleShape& rect);

//Fonction qui vérifie si la voiture peut passer ou non
bool can_pass(const sf::Sprite& vehicle_sprite, Traffic_light& feu, RectangleShape& rect);

void add_car(int voie, vector<Car*>& vect_cars, vector<thread>& vect_threads, Texture texture_voiture, vector<Traffic_light*> vect_feux, vector<RectangleShape*> vect_rectangles, RenderWindow& window);

