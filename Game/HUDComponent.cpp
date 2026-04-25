#include "HUDComponent.h"
#include <string>

namespace TowerDefence {

    void HUDComponent::Start()
    {
        if (fontLoaded) return;

        // Cherche la police dans l'ordre
        const char* paths[] = {
            "assets/arial.ttf",
            "arial.ttf",
            "C:/Windows/Fonts/arial.ttf",
            "C:/Windows/Fonts/segoeui.ttf",
            "C:/Windows/Fonts/tahoma.ttf",
            nullptr
        };

        for (int i = 0; paths[i] != nullptr; ++i)
        {
            if (font.openFromFile(paths[i]))
            {
                fontLoaded = true;
                return;
            }
        }

        // Si aucune police trouvée : on continue sans planter
        // Render() vérifie fontLoaded avant de dessiner
    }

    void HUDComponent::DrawText(sf::RenderWindow* window,
        const std::string& text,
        float x, float y,
        unsigned int size,
        sf::Color color)
    {
        if (!fontLoaded) return;

        sf::Text t(font, sf::String(text), static_cast<unsigned int>(size));
        t.setFillColor(color);
        t.setPosition(sf::Vector2f(x, y));

        // Ombre portée
        sf::Text shadow(font, sf::String(text), static_cast<unsigned int>(size));
        shadow.setFillColor(sf::Color(0, 0, 0, 180));
        shadow.setPosition(sf::Vector2f(x + 2.f, y + 2.f));
        window->draw(shadow);
        window->draw(t);
    }

    void HUDComponent::Render(sf::RenderWindow* window)
    {
        if (!fontLoaded) return;

        GameState& gs = GameState::Get();

        // Bandeau semi-transparent en haut
        sf::RectangleShape banner(sf::Vector2f(1000.f, 40.f));
        banner.setFillColor(sf::Color(0, 0, 0, 160));
        banner.setPosition(sf::Vector2f(0.f, 0.f));
        window->draw(banner);

        // Vie
        std::string hpStr = "HP: " + std::to_string(gs.playerHP);
        DrawText(window, hpStr, 10.f, 8.f, 22,
            gs.playerHP > 5 ? sf::Color(220, 50, 50) : sf::Color::Red);

        // Argent
        std::string moneyStr = "$ " + std::to_string(gs.money);
        DrawText(window, moneyStr, 160.f, 8.f, 22, sf::Color(255, 215, 0));

        // Vague
        std::string waveStr = "Vague " + std::to_string(gs.currentWave)
            + " / " + std::to_string(gs.maxWaves);
        DrawText(window, waveStr, 360.f, 8.f, 22, sf::Color::White);

        // Coût tour
        std::string costStr = "Tour: " + std::to_string(towerCost) + "$";
        sf::Color costColor = gs.money >= towerCost
            ? sf::Color(100, 255, 100)
            : sf::Color(200, 80, 80);
        DrawText(window, costStr, 600.f, 8.f, 22, costColor);

        // Game Over
        if (gs.gameOver)
        {
            sf::RectangleShape overlay(sf::Vector2f(1000.f, 600.f));
            overlay.setFillColor(sf::Color(0, 0, 0, 160));
            window->draw(overlay);
            DrawText(window, "GAME OVER", 330.f, 250.f, 60, sf::Color::Red);
            DrawText(window, "Relancez le programme pour rejouer",
                220.f, 330.f, 22, sf::Color::White);
        }

        // Victoire
        if (gs.victory)
        {
            sf::RectangleShape overlay(sf::Vector2f(1000.f, 600.f));
            overlay.setFillColor(sf::Color(0, 0, 0, 140));
            window->draw(overlay);
            DrawText(window, "VICTOIRE !", 320.f, 250.f, 60, sf::Color::Yellow);
            DrawText(window, "Toutes les vagues repoussees !",
                250.f, 330.f, 22, sf::Color::White);
        }
    }

}