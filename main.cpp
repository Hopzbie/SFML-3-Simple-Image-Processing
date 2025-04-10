// library
#include <SFML/Graphics.hpp>

// main program
int main()
{
    // create window
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Title");

    // load image
    sf::Image image("Images/Girl.png");
    unsigned int image_w = image.getSize().x;
    unsigned int image_h = image.getSize().y;

    // image processing
    for (unsigned int i = 0;  i < image_w;  i++)
    {
        for (unsigned int j = 0;  j < image_h;  j++)
        {
            // get color of pixel
            sf::Color color = image.getPixel({i, j});

            // grayscale value
            uint8_t value = 0.3f*color.r + 0.6f*color.g + 0.1f*color.b;

            // thresholding
            if      (value <  64)  color = sf::Color::Black;
            else if (value < 128)  color = sf::Color(  0, 170, 255);
            else if (value < 200)  color = sf::Color(128, 212, 255);
            else                   color = sf::Color::White;

            // set color of pixel
            image.setPixel({i, j}, color);
        }
    }

    // save image to file
    // bool success = image.saveToFile("Images/Girl 2.png");

    // create texture from image
    sf::Texture texture(image);
    texture.setSmooth(true);

    // create sprite from texture
    sf::Sprite sprite(texture);
    float scale = static_cast<float>(window.getSize().x) / image_w;
    sprite.setScale({scale, scale});

    // window loop
    while (window.isOpen())
    {
        // handle events
        while (auto event = window.pollEvent())
        {
            // on close button release
            if (event->is<sf::Event::Closed>())
            {
                // close window
                window.close();
            }

            // when window is resized
            else if (event->is<sf::Event::Resized>())
            {
                // update view
                window.setView(sf::View(sf::FloatRect({0.f, 0.f}, sf::Vector2f(window.getSize()))));
            }
        }

        // fill background color
        window.clear(sf::Color(64, 64, 64));

        // draw sprite
        window.draw(sprite);
        
        // display
        window.display();
    }

    // program end successfully
    return 0;
}