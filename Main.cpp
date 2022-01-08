#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "EventManagers/BaseManager.h"
#include "EventManagers/KeyboardManager.h"
#include "Entities/ContainerEntity.h"
#include "Entities/BallEntity.h"
#include "Entities/CueEntity.h"
#include "Entities/WallEntity.h"
#include "Entities/HoleEntity.h"
#include "UI/UICueForce.h"
#include "UI/UIBallTrajectory.h"

float randomFloat(float max)
{
    return (static_cast <float>(rand()) / static_cast <float> (RAND_MAX)) * max;
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode(800, 500), "Back At The Farm - Pool Prototype", sf::Style::Close, settings);
    window.setFramerateLimit(60);
    
    EventManager eventManager;
    KeyboardManager keyboardManager;

    eventManager.Attach(&keyboardManager);
    ContainerEntity container;

    for (int i = 0; i < sizeof(G_BALLS) / (sizeof(float) * 2); i++)
    {
        BallEntity* pBall = new BallEntity(false, false);
        pBall->m_ball.setFillColor(sf::Color::Red);
        pBall->setPosition(G_BALLS[i]);
        container.addNode(pBall);
    }

    // Walls
    container.addNode(new WallEntity(sf::Vector2f(77, 58), sf::Vector2f(68, 49), 0));
    container.addNode(new WallEntity(sf::Vector2f(374, 57), sf::Vector2f(77, 58), 0));
    container.addNode(new WallEntity(sf::Vector2f(385, 49), sf::Vector2f(374, 57), 0));
    container.addNode(new WallEntity(sf::Vector2f(427, 58), sf::Vector2f(418, 49), 0));
    container.addNode(new WallEntity(sf::Vector2f(722, 58), sf::Vector2f(427, 58), 0));
    container.addNode(new WallEntity(sf::Vector2f(736, 48), sf::Vector2f(722, 58), 0));
    container.addNode(new WallEntity(sf::Vector2f(742, 78), sf::Vector2f(751, 71), 0));
    container.addNode(new WallEntity(sf::Vector2f(743, 379), sf::Vector2f(742, 78), 0));
    container.addNode(new WallEntity(sf::Vector2f(752, 390), sf::Vector2f(743, 379), 0));
    container.addNode(new WallEntity(sf::Vector2f(724, 402), sf::Vector2f(734, 411), 0));
    container.addNode(new WallEntity(sf::Vector2f(433, 403), sf::Vector2f(724, 402), 0));
    container.addNode(new WallEntity(sf::Vector2f(420, 413), sf::Vector2f(433, 403), 0));
    container.addNode(new WallEntity(sf::Vector2f(374, 402), sf::Vector2f(384, 412), 0));
    container.addNode(new WallEntity(sf::Vector2f(80, 402), sf::Vector2f(374, 402), 0));
    container.addNode(new WallEntity(sf::Vector2f(67, 413), sf::Vector2f(80, 402), 0));
    container.addNode(new WallEntity(sf::Vector2f(61, 382), sf::Vector2f(51, 390), 0));
    container.addNode(new WallEntity(sf::Vector2f(62, 81), sf::Vector2f(61, 382), 0));
    container.addNode(new WallEntity(sf::Vector2f(52, 70), sf::Vector2f(62, 81), 0));

    sf::Texture floorTexture;
    sf::Sprite floorSprite;
    floorTexture.loadFromFile("Textures/Floor.png");
    floorTexture.setRepeated(true);
    floorSprite.setTexture(floorTexture);
    floorSprite.setTextureRect({ 0, 0, 800, 500 });

    sf::Texture poolTableTexture;
    sf::Sprite poolTableSprite;
    poolTableTexture.loadFromFile("Textures/pooltable-upscaled.png");
    poolTableSprite.setTexture(poolTableTexture);
    poolTableSprite.setPosition(32, 32);
    poolTableSprite.setScale(0.74, 0.74);

    BallEntity* pPlayer = new BallEntity(true, false);
    pPlayer->m_ball.setFillColor(sf::Color::White);
    pPlayer->setPosition(100, 200);
    container.addNode(pPlayer);

    CueEntity* pCue = new CueEntity();
    pPlayer->AttachCue(pCue);

    UIBallTrajectory* pTrajectory = new UIBallTrajectory();
    pPlayer->AttachTrajectory(pTrajectory);
    container.addNode(pTrajectory);

    UICueForce* pUICueForce = new UICueForce();
    pCue->AttachUIElement(pUICueForce);
    container.addNode(pUICueForce);

    WallEntity* pWall = nullptr;

    container.addNode(new HoleEntity(sf::Vector2f(54, 54)));
    container.addNode(new HoleEntity(sf::Vector2f(402, 46)));
    container.addNode(new HoleEntity(sf::Vector2f(748, 53)));
    container.addNode(new HoleEntity(sf::Vector2f(750, 407)));
    container.addNode(new HoleEntity(sf::Vector2f(401, 415)));
    container.addNode(new HoleEntity(sf::Vector2f(51, 409)));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                eventManager.Process(event);
                break;
            }
        }

        window.clear();
        g_pBallManager->Update();
        window.draw(floorSprite);
        window.draw(poolTableSprite);
        window.draw(container);

        window.display();
    }

    return 0;
}