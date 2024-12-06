//// condition_variable::wait (with predicate)
//#include <iostream> // std::cout
//#include <thread>   // std::thread, std::this_thread::yield
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
//
//using namespace std::chrono_literals;
//
//static const sf::Color Orange(255, 165, 0);
//
//const auto time_transit = 3s;
//const auto time_waiting = 8s;
//
//enum class Traffic_color
//{
//    green = 0,
//    orange = 1,
//    red = 2
//};
//
//Traffic_color operator++(Traffic_color& traffic_color)
//{
//    switch (traffic_color)
//    {
//    case Traffic_color::red:
//        traffic_color = Traffic_color::green;
//        break;
//
//    case Traffic_color::green:
//        std::this_thread::sleep_for(time_transit);
//        traffic_color = Traffic_color::orange;
//        std::this_thread::sleep_for(time_transit);
//        traffic_color = Traffic_color::red;
//    }
//    return traffic_color;
//}
//
//class Traffic_light
//{
//private:
//    Traffic_color traffic_color_;
//
//public:
//    explicit Traffic_light(const Traffic_color& traffic_color) : traffic_color_{ traffic_color } {}
//    void operator++()
//    {
//        ++traffic_color_;
//    }
//    void set_traffic_color(const Traffic_color& traffic_color)
//    {
//        traffic_color_ = traffic_color;
//    }
//    const Traffic_color& get_traffic_color() const
//    {
//        return traffic_color_;
//    }
//};
//
//const sf::Color& get_SFML_color(const Traffic_light& traffic_light)
//{
//    switch (traffic_light.get_traffic_color())
//    {
//    case Traffic_color::green:
//        return sf::Color::Green;
//    case Traffic_color::red:
//        return sf::Color::Red;
//    }
//    return Orange;
//}
//
//std::ostream& operator<<(std::ostream& os, const Traffic_light& traffic_light)
//{
//    std::string ptr;
//    switch (traffic_light.get_traffic_color())
//    {
//    case Traffic_color::red:
//        ptr = "Red";
//        break;
//    case Traffic_color::green:
//        ptr = "Green";
//        break;
//    case Traffic_color::orange:
//        ptr = "Orange";
//    }
//    os << ptr;
//    return os;
//}
//
//void run_traffic_light(Traffic_light& traffic_light_master, Traffic_light& traffic_light_slave, std::stop_token stop_token)
//{
//    traffic_light_master.set_traffic_color(Traffic_color::green);
//    traffic_light_slave.set_traffic_color(Traffic_color::red);
//    while (!stop_token.stop_requested())
//    {
//        std::this_thread::sleep_for(time_waiting);
//        if (traffic_light_master.get_traffic_color() == Traffic_color::green)
//        {
//            ++traffic_light_master;
//            ++traffic_light_slave;
//        }
//        else
//        {
//            ++traffic_light_slave;
//            ++traffic_light_master;
//        }
//    }
//}
//
//void print_traffic_light(Traffic_light& traffic_light_master, Traffic_light& traffic_light_slave, std::stop_token stop_token)
//{
//    while (!stop_token.stop_requested())
//    {
//        std::this_thread::sleep_for(1s);
//        std::cout << "Taffic light master : " << traffic_light_master << " Taffic light slave : " << traffic_light_slave << std::endl;
//    }
//}
//
//int main()
//{
//    std::stop_source stopping;
//    Traffic_light traffic_light_master{ Traffic_color::red };
//    Traffic_light traffic_light_slave{ Traffic_color::red };
//    std::jthread thread_traffic_light_master(run_traffic_light,
//        std::ref(traffic_light_master), std::ref(traffic_light_slave), stopping.get_token());
//
//    std::jthread write_traffic_light(print_traffic_light,
//        std::ref(traffic_light_master), std::ref(traffic_light_slave), stopping.get_token());
//
//    sf::RenderWindow window(sf::VideoMode(800, 800), "My window");
//
//    float l1 = 350, l2 = 430, size = 800, radius = 10;
//    sf::Vertex line1[] = { sf::Vertex(sf::Vector2f(0, l1)), sf::Vertex(sf::Vector2f(size, l1)) };
//    sf::Vertex line2[] = { sf::Vertex(sf::Vector2f(0, l2)), sf::Vertex(sf::Vector2f(size, l2)) };
//    sf::Vertex line3[] = { sf::Vertex(sf::Vector2f(l1, 0)), sf::Vertex(sf::Vector2f(l1, size)) };
//    sf::Vertex line4[] = { sf::Vertex(sf::Vector2f(l2, 0)), sf::Vertex(sf::Vector2f(l2, size)) };
//
//    sf::CircleShape circle1(radius);
//    circle1.setFillColor(sf::Color::Blue);
//    circle1.setOrigin(circle1.getRadius() / 2, circle1.getRadius() / 2);
//    circle1.setPosition(l2 + radius / 2, l2 + radius / 2);
//    sf::CircleShape circle2(radius);
//    circle2.setFillColor(sf::Color::Green);
//    circle2.setOrigin(circle2.getRadius() / 2, circle2.getRadius() / 2);
//    circle2.setPosition(l2 + radius / 2, l1 - radius);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//            {
//                stopping.request_stop();
//                window.close();
//                return 0;
//            }
//        }
//        window.clear(sf::Color::Black);
//
//        window.draw(line1, 2, sf::Lines);
//        window.draw(line2, 2, sf::Lines);
//        window.draw(line3, 2, sf::Lines);
//        window.draw(line4, 2, sf::Lines);
//        circle1.setFillColor(get_SFML_color(traffic_light_slave));
//        circle2.setFillColor(get_SFML_color(traffic_light_master));
//        window.draw(circle1);
//        window.draw(circle2);
//
//        window.display();
//    }
//
//    return 0;
//}

#include "../Headers/main.hpp"
#include "../Headers/classes.hpp"
#include <filesystem>

using namespace std;
using namespace sf;

int main() {

    Clock clock_;

    //Définition des textures des éléments du jeu

    Texture texture_carrefour;
    texture_carrefour.loadFromFile("../../../../Assets/Carrefour/image_carrefour_2.png");
    
    Texture texture_voiture;
    texture_voiture.loadFromFile("../../../../Assets/Vehicules/vecteezy_car-top-view-clipart-design-illustration_9380944.png");

    


    Sprite sprite_carrefour;
    sprite_carrefour.setTexture(texture_carrefour);

    
    //Définition de la fenêtre
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simulation");
    window.setVerticalSyncEnabled(true);
    
    //Positionnnement de l'image du carrefour
    sprite_carrefour.setScale(
        static_cast<float>(window.getSize().x) / texture_carrefour.getSize().x,
        static_cast<float>(window.getSize().y) / texture_carrefour.getSize().y
    );
    

    //Feux de circulation (représentés par des disques)
    //H : horizontal
    //V : vertical
    //G : gauche
    //D : droite
    //B : bas
    //H : haut

    Vector2f pos_feu_HG(235,660);
    Vector2f pos_feu_HD(660, 303);
    Vector2f pos_feu_VH(265, 275);
    Vector2f pos_feu_VB(625, 680);

    Traffic_light feu_HG(Color::Black, 0, pos_feu_HG);
    Traffic_light feu_HD(Color::Black, 0, pos_feu_HD);
    Traffic_light feu_VH(Color::Black, 1, pos_feu_VH);
    Traffic_light feu_VB(Color::Black, 1, pos_feu_VB);

    vector<Traffic_light*> vect_feux;
    vect_feux.push_back(&feu_HG);
    vect_feux.push_back(&feu_VH);



    //Car car1(4,texture_voiture,std::ref(window),std::ref(vect_ca));
    
    //Vector contenant les voitures affichées à l'écran
    //vector<Car&> vect_cars;

    //vect_cars.push_back(std::ref(car1));

    
    //Zones d'arrêt de la voiture
    RectangleShape rect_voie1(Vector2f(10, 90));
    rect_voie1.setFillColor(Color(255,0,0,100));
    rect_voie1.setPosition(198,493);
    rect_voie1.setScale(1, 1);    

    RectangleShape rect_voie2 = rect_voie1;
    rect_voie2.rotate(90);
    rect_voie2.setPosition(441, 234);

    RectangleShape rect_voie3 = rect_voie1;
    rect_voie3.setPosition(681, 387);

    RectangleShape rect_voie4 = rect_voie2;
    rect_voie4.setPosition(546, 716);

    vector<RectangleShape*> vect_rectangles;
    vect_rectangles.push_back(&rect_voie1);
    vect_rectangles.push_back(&rect_voie2);
    vect_rectangles.push_back(&rect_voie3);
    vect_rectangles.push_back(&rect_voie4);


    //Threads :

    //Vecteur contenant les threads
    vector<std::thread> vect_threads;
    
    vect_threads.emplace_back(run_traffic_light, std::ref(feu_HG), std::ref(feu_HD), std::ref(feu_VH), std::ref(feu_VB), TIME_ON, TIME_TRANSITION, std::ref(window));
    

    //Vecteur de voitures utilisé en local
    vector<Car*> vect_cars;
    
    
    //thread thread_voiture(car_start, std::ref(car1), DELAY, std::ref(window), std::ref(vect_feux), std::ref(vect_rectangles));
    //vect_threads.emplace_back(car_start, vect_cars.at(0), DELAY, std::ref(window), std::ref(vect_feux), std::ref(vect_rectangles));
    //vect_threads.emplace_back(car_start, vect_cars.at(1), DELAY, std::ref(window), std::ref(vect_feux), std::ref(vect_rectangles));
    //vect_threads.emplace_back(car_start, vect_cars.at(2), DELAY, std::ref(window), std::ref(vect_feux), std::ref(vect_rectangles));

    int voie = 1;

    //Tant que la fenêtre est ouverte
    while (window.isOpen()) {
        
        Event event;

        //Un évènement s'est-il produit ?
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::C) {

                    
                }
            }
        }
        if (clock_.getElapsedTime().asSeconds() >= 1) {
            clock_.restart();

            int voie = rand() % 3 + 1;

            while (!is_lane_free(std::ref(vect_cars), voie)) {
                voie = rand() % 3 + 1;
            }

            auto newcar = new Car(voie, texture_voiture, std::ref(window),std::ref(vect_cars));

            cout << "Car added, total cars :" << vect_cars.size() << endl;

            vect_threads.emplace_back(car_start, newcar, DELAY, std::ref(window), std::ref(vect_feux), std::ref(vect_rectangles));

        }
        

        window.clear(Color::Black);

        //Affichage du carrefour
        window.draw(sprite_carrefour);

        //Affichage des feux
        window.draw(feu_HG.return_traffic_light());
        window.draw(feu_HD.return_traffic_light());
        window.draw(feu_VH.return_traffic_light());
        window.draw(feu_VB.return_traffic_light());

        window.draw(rect_voie1);
        window.draw(rect_voie2);
        window.draw(rect_voie3);
        window.draw(rect_voie4);

        //Affichage de/des voitures
        for (auto& car : vect_cars) {
            window.draw(car->return_sprite());
        }
        //window.draw(car1.return_sprite());

        window.display();
    }
    
    //thread_feux.join();
    //thread_voiture.join();

    //thread_feux.join();
    
    for (auto& thread_ : vect_threads) {
        if (thread_.joinable()) {
            thread_.join();
        }
    }
    


    return 0;
}