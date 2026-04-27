#include "BHHUD.h"
#include "BHGameState.h"
#include <SFML/Graphics.hpp>

namespace BulletHell {

    void BHHUD::Start()
    {
        static sf::Font sharedFont;
        static bool     loaded = false;
        if (!loaded)
        {
            const char* paths[] = {
                "C:/Windows/Fonts/arial.ttf",
                "C:/Windows/Fonts/segoeui.ttf",
                "C:/Windows/Fonts/tahoma.ttf",
                nullptr
            };
            for (int i = 0; paths[i]; ++i)
                if (sharedFont.openFromFile(paths[i])) { loaded = true; break; }
        }
        if (loaded) { fontPtr = &sharedFont; fontLoaded = true; }
    }

    void BHHUD::DrawText(sf::RenderWindow* w, const std::string& txt,
        float x, float y, unsigned sz, sf::Color col)
    {
        if (!fontLoaded) return;
        sf::Text shadow(*fontPtr, txt, sz);
        shadow.setFillColor(sf::Color(0, 0, 0, 160));
        shadow.setPosition({ x + 2.f, y + 2.f });
        w->draw(shadow);
        sf::Text t(*fontPtr, txt, sz);
        t.setFillColor(col);
        t.setPosition({ x, y });
        w->draw(t);
    }

    void BHHUD::Render(sf::RenderWindow* window)
    {
        if (!fontLoaded) return;
        auto& gs = BHGameState::Get();

        sf::RectangleShape bar(sf::Vector2f(1000.f, 38.f));
        bar.setFillColor(sf::Color(0, 0, 0, 150));
        window->draw(bar);

        DrawText(window, "Score: " + std::to_string(gs.score), 10.f, 6.f, 22, sf::Color::White);
        DrawText(window, "Vague: " + std::to_string(gs.wave) + "/3", 400.f, 6.f, 22, sf::Color(255, 215, 0));

        for (int i = 0; i < gs.lives; i++)
        {
            sf::CircleShape heart(10.f);
            heart.setFillColor(sf::Color(220, 50, 50));
            heart.setPosition({ 850.f + i * 30.f, 8.f });
            window->draw(heart);
        }

        if (gs.gameOver)
        {
            sf::RectangleShape overlay(sf::Vector2f(1000.f, 600.f));
            overlay.setFillColor(sf::Color(0, 0, 0, 160));
            window->draw(overlay);
            DrawText(window, "GAME OVER", 330.f, 230.f, 64, sf::Color::Red);
            DrawText(window, "Score final: " + std::to_string(gs.score), 360.f, 320.f, 28, sf::Color::White);
            DrawText(window, "Relancez pour rejouer", 310.f, 370.f, 22, sf::Color(200, 200, 200));
        }

        if (gs.victory)
        {
            sf::RectangleShape overlay(sf::Vector2f(1000.f, 600.f));
            overlay.setFillColor(sf::Color(0, 0, 0, 140));
            window->draw(overlay);
            DrawText(window, "VICTOIRE !", 320.f, 230.f, 64, sf::Color::Yellow);
            DrawText(window, "Score final: " + std::to_string(gs.score), 360.f, 320.f, 28, sf::Color::White);
        }
    }
}