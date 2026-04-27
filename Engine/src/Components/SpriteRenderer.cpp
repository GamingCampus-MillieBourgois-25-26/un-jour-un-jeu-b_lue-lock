#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"

SpriteRenderer::SpriteRenderer(Texture* _texture)
{
    texture = _texture;

    const sf::Vector2u size = texture->GetTexture().getSize();

    rect = sf::IntRect(static_cast<sf::Vector2i>(Maths::Vector2i::Zero),
                       sf::Vector2i(static_cast<int>(size.x), static_cast<int>(size.y)));
}

void SpriteRenderer::Render(sf::RenderWindow* _window)
{
    ARenderedComponent::Render(_window);

    sf::Sprite sprite(texture->GetTexture());

    sprite.setTextureRect(rect);

    auto* col = GetOwner()->GetComponent<SquareCollider>();
    if (col) {
        col->DebugRender(_window);
    }

    sprite.setColor(color);

    sf::Vector2f size = static_cast<sf::Vector2f>(texture->GetTexture().getSize());
    sprite.setOrigin(size * 0.5f);

    sprite.setPosition(static_cast<sf::Vector2f>(GetOwner()->GetPosition()));
    sprite.setRotation(GetOwner()->GetRotation());
    sprite.setScale(static_cast<sf::Vector2f>(GetOwner()->GetScale()));

    _window->draw(sprite);
}
