#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <map>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <SFML/Graphics.hpp>

typedef std::map<sf::Keyboard::Key, CEGUI::Key::Scan> KeyMap;
typedef std::map<sf::Mouse::Button, CEGUI::MouseButton> MouseButtonMap;

class GUIManager
{
public:
    GUIManager(sf::RenderWindow* window);

    bool handleEvent(const sf::Event& e);
    void update(float dt);
    void draw();

private:
    void initialiseMaps();
    CEGUI::Key::Scan toCEGUIKey(sf::Keyboard::Key key);
    CEGUI::MouseButton toCEGUIMouseButton(sf::Mouse::Button button);

    sf::RenderWindow* m_window;

    CEGUI::OpenGLRenderer& m_renderer;

    KeyMap m_keyMap;
    MouseButtonMap m_mouseButtonMap;
};

#endif //GUIMANAGER_HPP
