#include <SFML/Graphics.hpp>
int main()
{
    sf::RectangleShape rect({30.f, 40.f});
    float offsetX, offsetY;
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(60);
    rect.move({100.f,100.f});
    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Right)
                {
                   if( mouseButtonPressed->position.x < rect.getPosition().x){
                       offsetX=1;
                   }
                   else{
                       if( mouseButtonPressed->position.x > rect.getPosition().x){
                           offsetX=-1;
                       }else{
                           if( mouseButtonPressed->position.x == rect.getPosition().x){
                               offsetX=0;
                           }
                       }

                   }
                    if( mouseButtonPressed->position.y < rect.getPosition().y){
                        offsetY=1;
                    }
                    else{
                        if( mouseButtonPressed->position.y > rect.getPosition().y){
                            offsetY=-1;
                        }else{
                            if( mouseButtonPressed->position.y == rect.getPosition().y){
                                offsetY=0;
                            }
                        }

                    }
                }
            }
        }
        rect.move({offsetX,offsetY});
        window.clear();
        window.draw(rect);
        window.display();
    }
}
