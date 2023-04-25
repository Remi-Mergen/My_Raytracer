/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** main.cpp
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"
#include "Object.hpp"
#include "Rect3.hpp"
#include "Camera.hpp"

// SIZE OF THE WINDOW
unsigned int width = 800;
unsigned int height = 600;
unsigned int screenHalfWidth = width / 2;
unsigned int screenHalfHeight = height / 2;
float worldWidth = 10.0f;                   // Scene width in world coordinates
float worldHeight = 10.0f * height / width; // Scene height in world coordinates, keeping the aspect ratio

bool saveImage = false; // if false render in live

void printHelp()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
    std::cout << "SCENE_FILE: scene configuration" << std::endl;
}

void drawOnImage(RayTracer::Camera camera, std::vector<Object *> scene, sf::Image &image)
{
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            float u = (x + 0.5) / width;
            float v = (y + 0.5) / height;

            Ray ray = camera.ray(u, v);

            Object *closestObject = nullptr;
            float minDistance = std::numeric_limits<float>::max();

            for (const auto &object : scene)
            {
                float t; // distance to the object from the camera
                if (object->intersect(ray, t))
                {
                    if (t < minDistance)
                    {
                        minDistance = t;
                        closestObject = object;
                    }
                }
            }

            if (closestObject != nullptr && minDistance != std::numeric_limits<float>::max())
            {
                image.setPixel(x, y, closestObject->color);
            }
        }
    }
}

void cleanMemory(std::vector<Object *> scene)
{
    // Clean up the allocated memory for the objects in the scene
    for (Object *obj : scene)
    {
        delete obj;
    }
}

sf::Image renderImage(RayTracer::Camera camera, std::vector<Object *> scene)
{
    sf::Image image;

    image.create(width, height, sf::Color::Black);
    drawOnImage(camera, scene, image);

    return image;
}

int main(int argc, char **argv)
{
    if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"))
    {
        printHelp();
        exit(0);
    }
    else if (argc != 2 && false)
    {
        std::cerr << "Invalid number of arguments" << std::endl;
        printHelp();
        exit(84);
    }

    sf::RenderWindow window(sf::VideoMode(width, height), "Raytracer");

    std::vector<Object *> scene;
    scene.push_back(new Sphere(Vec3(-1, 0, -5), 1, sf::Color::Red));
    scene.push_back(new Rect3(Vec3(-3, -1, -5), Vec3(2, 0, 0), Vec3(0, 2, 0), sf::Color::Blue));

    RayTracer::Camera camera(
        Vec3(0, 0, 0),
        Rect3(
            Vec3(-screenHalfWidth, -screenHalfHeight, -1),
            Vec3(2 * screenHalfWidth, 0, 0),
            Vec3(0, 2 * screenHalfHeight, 0), sf::Color::White));

    // Define the camera screen
    float fov = 60.0f;
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    float screenHalfWidth = std::tan(fov * 0.5 * M_PI / 180.0) * aspectRatio;
    float screenHalfHeight = std::tan(fov * 0.5 * M_PI / 180.0);

    camera.screen = Rect3(Vec3(-screenHalfWidth, -screenHalfHeight, -1), Vec3(2 * screenHalfWidth, 0, 0), Vec3(0, 2 * screenHalfHeight, 0), sf::Color::White);

    sf::Image image = renderImage(camera, scene);
    sf::Texture texture;
    texture.loadFromImage(image);
    // image.saveToFile("image.png"); TODO create render mode and live mode
    sf::Sprite sprite(texture);

    bool leftMousePressed = false;
    int selectedObjectIndex = -1;
    sf::Vector2i prevMousePos(-1, -1);

    while (window.isOpen())
    {
        sf::Event event;
        float cameraSpeed = 0.1f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            camera.origin.x += cameraSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            camera.origin.x -= cameraSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            camera.origin.y += cameraSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            camera.origin.y -= cameraSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        {
            camera.origin.z -= cameraSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            camera.origin.z += cameraSpeed;
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    leftMousePressed = true;

                    // Cast a ray from the camera through the clicked pixel
                    leftMousePressed = true;

                    float u = (2.0 * ((event.mouseButton.x + 0.5) / width) - 1.0) * std::tan(fov * 0.5 * M_PI / 180.0) * aspectRatio;
                    float v = (1.0 - 2.0 * ((event.mouseButton.y + 0.5) / height)) * std::tan(fov * 0.5 * M_PI / 180.0);

                    Vec3 rayDirection(u, v, -1);
                    rayDirection = rayDirection.normalize();

                    Ray ray(camera.origin, rayDirection);

                    // Find the closest object under the cursor
                    float minDistance = std::numeric_limits<float>::max();
                    selectedObjectIndex = -1;
                    for (size_t i = 0; i < scene.size(); ++i)
                    {
                        float t;
                        if (scene[i]->intersect(ray, t))
                        {
                            if (t < minDistance)
                            {
                                minDistance = t;
                                selectedObjectIndex = i;
                            }
                        }
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    leftMousePressed = false;
                    prevMousePos = sf::Vector2i(-1, -1);
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::K) || sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            image = renderImage(camera, scene);
            texture.loadFromImage(image);
            sprite.setTexture(texture);
        }

        if (leftMousePressed && selectedObjectIndex >= 0)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (prevMousePos.x != -1 && prevMousePos.y != -1)
            {
                float deltaX = static_cast<float>(mousePos.x - prevMousePos.x);
                float deltaY = static_cast<float>(prevMousePos.y - mousePos.y);

                // Scale the translation based on the desired mapping between screen coordinates and world coordinates
                deltaX = deltaX / width * worldWidth;
                deltaY = deltaY / height * worldHeight;

                Vec3 translation(deltaX, -deltaY, 0);
                scene[selectedObjectIndex]->translate(translation);

                image = renderImage(camera, scene);
                texture.loadFromImage(image);
                sprite.setTexture(texture);
            }

            prevMousePos = mousePos;
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    cleanMemory(scene);
    return 0;
}
