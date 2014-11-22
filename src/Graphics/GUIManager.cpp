#include "Graphics/GUIManager.hpp"

#include <iostream>

GUIManager::GUIManager(sf::RenderWindow* window)
    : m_window(window)
    , m_renderer(CEGUI::OpenGLRenderer::bootstrapSystem())
{
    CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());

    rp->setResourceGroupDirectory("schemes", "data/cegui/schemes");
    rp->setResourceGroupDirectory("imagesets", "data/cegui/imagesets");
    rp->setResourceGroupDirectory("fonts", "data/cegui/fonts");
    rp->setResourceGroupDirectory("layouts", "data/cegui/layouts");
    rp->setResourceGroupDirectory("looknfeels", "data/cegui/looknfeel");
    rp->setResourceGroupDirectory("lua_scripts", "data/cegui/lua_scripts");

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

    CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
    CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("AlfiskoSkin/MouseArrow");

    initialiseMaps();
}

bool GUIManager::handleEvent(const sf::Event& e)
{
    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

    switch (e.type)
    {
        case sf::Event::TextEntered:
        {
            context.injectChar(e.text.unicode);
            break;
        }

        case sf::Event::KeyPressed:
        {
            context.injectKeyDown(toCEGUIKey(e.key.code));
            break;
        }

        case sf::Event::KeyReleased:
        {
            context.injectKeyUp(toCEGUIKey(e.key.code));
            break;
        }

        case sf::Event::MouseMoved:
        {
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*m_window));
            context.injectMousePosition(mousePos.x, mousePos.y);
            break;
        }

        case sf::Event::MouseButtonPressed:
        {
            context.injectMouseButtonDown(toCEGUIMouseButton(e.mouseButton.button));
            break;
        }

        case sf::Event::MouseButtonReleased:
        {
            context.injectMouseButtonUp(toCEGUIMouseButton(e.mouseButton.button));
            break;
        }

        case sf::Event::MouseWheelMoved:
        {
            context.injectMouseWheelChange(e.mouseWheel.delta);
            break;
        }

        case sf::Event::Resized:
        {
            CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(e.size.width, e.size.height));
            break;
        }

        default:
        {
            break;
        }
    }

    return false;
}

void GUIManager::update(float dt)
{
    CEGUI::System::getSingleton().injectTimePulse(dt);
}

void GUIManager::draw()
{
    CEGUI::System::getSingleton().renderAllGUIContexts();
}

void GUIManager::initialiseMaps()
{
	m_keyMap[sf::Keyboard::Escape]          = CEGUI::Key::Escape       ;
	m_keyMap[sf::Keyboard::Num1]            = CEGUI::Key::One          ;
	m_keyMap[sf::Keyboard::Num2]            = CEGUI::Key::Two          ;
	m_keyMap[sf::Keyboard::Num3]            = CEGUI::Key::Three        ;
	m_keyMap[sf::Keyboard::Num4]            = CEGUI::Key::Four         ;
	m_keyMap[sf::Keyboard::Num5]            = CEGUI::Key::Five         ;
	m_keyMap[sf::Keyboard::Num6]            = CEGUI::Key::Six          ;
	m_keyMap[sf::Keyboard::Num7]            = CEGUI::Key::Seven        ;
	m_keyMap[sf::Keyboard::Num8]            = CEGUI::Key::Eight        ;
	m_keyMap[sf::Keyboard::Num9]            = CEGUI::Key::Nine         ;
	m_keyMap[sf::Keyboard::Num0]            = CEGUI::Key::Zero         ;
	m_keyMap[sf::Keyboard::Dash]            = CEGUI::Key::Minus        ;
	m_keyMap[sf::Keyboard::Equal]           = CEGUI::Key::Equals       ;
	m_keyMap[sf::Keyboard::BackSpace]       = CEGUI::Key::Backspace    ;
	m_keyMap[sf::Keyboard::Tab]             = CEGUI::Key::Tab          ;
	m_keyMap[sf::Keyboard::Q]               = CEGUI::Key::Q            ;
	m_keyMap[sf::Keyboard::W]               = CEGUI::Key::W            ;
	m_keyMap[sf::Keyboard::E]               = CEGUI::Key::E            ;
	m_keyMap[sf::Keyboard::R]               = CEGUI::Key::R            ;
	m_keyMap[sf::Keyboard::T]               = CEGUI::Key::T            ;
	m_keyMap[sf::Keyboard::Y]               = CEGUI::Key::Y            ;
	m_keyMap[sf::Keyboard::U]               = CEGUI::Key::U            ;
	m_keyMap[sf::Keyboard::I]               = CEGUI::Key::I            ;
	m_keyMap[sf::Keyboard::O]               = CEGUI::Key::O            ;
	m_keyMap[sf::Keyboard::P]               = CEGUI::Key::P            ;
	m_keyMap[sf::Keyboard::LBracket]        = CEGUI::Key::LeftBracket  ;
	m_keyMap[sf::Keyboard::RBracket]        = CEGUI::Key::RightBracket ;
	m_keyMap[sf::Keyboard::Return]          = CEGUI::Key::Return       ;
	m_keyMap[sf::Keyboard::LControl]        = CEGUI::Key::LeftControl  ;
	m_keyMap[sf::Keyboard::A]               = CEGUI::Key::A            ;
	m_keyMap[sf::Keyboard::S]               = CEGUI::Key::S            ;
	m_keyMap[sf::Keyboard::D]               = CEGUI::Key::D            ;
	m_keyMap[sf::Keyboard::F]               = CEGUI::Key::F            ;
	m_keyMap[sf::Keyboard::G]               = CEGUI::Key::G            ;
	m_keyMap[sf::Keyboard::H]               = CEGUI::Key::H            ;
	m_keyMap[sf::Keyboard::J]               = CEGUI::Key::J            ;
	m_keyMap[sf::Keyboard::K]               = CEGUI::Key::K            ;
	m_keyMap[sf::Keyboard::L]               = CEGUI::Key::L            ;
	m_keyMap[sf::Keyboard::SemiColon]       = CEGUI::Key::Semicolon    ;
	m_keyMap[sf::Keyboard::LShift]          = CEGUI::Key::LeftShift    ;
	m_keyMap[sf::Keyboard::BackSlash]       = CEGUI::Key::Backslash    ;
	m_keyMap[sf::Keyboard::Z]               = CEGUI::Key::Z            ;
	m_keyMap[sf::Keyboard::X]               = CEGUI::Key::X            ;
	m_keyMap[sf::Keyboard::C]               = CEGUI::Key::C            ;
	m_keyMap[sf::Keyboard::V]               = CEGUI::Key::V            ;
	m_keyMap[sf::Keyboard::B]               = CEGUI::Key::B            ;
	m_keyMap[sf::Keyboard::N]               = CEGUI::Key::N            ;
	m_keyMap[sf::Keyboard::M]               = CEGUI::Key::M            ;
	m_keyMap[sf::Keyboard::Comma]           = CEGUI::Key::Comma        ;
	m_keyMap[sf::Keyboard::Period]          = CEGUI::Key::Period       ;
	m_keyMap[sf::Keyboard::Slash]           = CEGUI::Key::Slash        ;
	m_keyMap[sf::Keyboard::RShift]          = CEGUI::Key::RightShift   ;
	m_keyMap[sf::Keyboard::Multiply]        = CEGUI::Key::Multiply     ;
	m_keyMap[sf::Keyboard::LAlt]            = CEGUI::Key::LeftAlt      ;
	m_keyMap[sf::Keyboard::Space]           = CEGUI::Key::Space        ;
	m_keyMap[sf::Keyboard::F1]              = CEGUI::Key::F1           ;
	m_keyMap[sf::Keyboard::F2]              = CEGUI::Key::F2           ;
	m_keyMap[sf::Keyboard::F3]              = CEGUI::Key::F3           ;
	m_keyMap[sf::Keyboard::F4]              = CEGUI::Key::F4           ;
	m_keyMap[sf::Keyboard::F5]              = CEGUI::Key::F5           ;
	m_keyMap[sf::Keyboard::F6]              = CEGUI::Key::F6           ;
	m_keyMap[sf::Keyboard::F7]              = CEGUI::Key::F7           ;
	m_keyMap[sf::Keyboard::F8]              = CEGUI::Key::F8           ;
	m_keyMap[sf::Keyboard::F9]              = CEGUI::Key::F9           ;
	m_keyMap[sf::Keyboard::F10]             = CEGUI::Key::F10          ;
	m_keyMap[sf::Keyboard::Numpad7]         = CEGUI::Key::Numpad7      ;
	m_keyMap[sf::Keyboard::Numpad8]         = CEGUI::Key::Numpad8      ;
	m_keyMap[sf::Keyboard::Numpad9]         = CEGUI::Key::Numpad9      ;
	m_keyMap[sf::Keyboard::Subtract]        = CEGUI::Key::Subtract     ;
	m_keyMap[sf::Keyboard::Numpad4]         = CEGUI::Key::Numpad4      ;
	m_keyMap[sf::Keyboard::Numpad5]         = CEGUI::Key::Numpad5      ;
	m_keyMap[sf::Keyboard::Numpad6]         = CEGUI::Key::Numpad6      ;
	m_keyMap[sf::Keyboard::Add]             = CEGUI::Key::Add          ;
	m_keyMap[sf::Keyboard::Numpad1]         = CEGUI::Key::Numpad1      ;
	m_keyMap[sf::Keyboard::Numpad2]         = CEGUI::Key::Numpad2      ;
	m_keyMap[sf::Keyboard::Numpad3]         = CEGUI::Key::Numpad3      ;
	m_keyMap[sf::Keyboard::Numpad0]         = CEGUI::Key::Numpad0      ;
	m_keyMap[sf::Keyboard::F11]             = CEGUI::Key::F11          ;
	m_keyMap[sf::Keyboard::F12]             = CEGUI::Key::F12          ;
	m_keyMap[sf::Keyboard::F13]             = CEGUI::Key::F13          ;
	m_keyMap[sf::Keyboard::F14]             = CEGUI::Key::F14          ;
	m_keyMap[sf::Keyboard::F15]             = CEGUI::Key::F15          ;
	m_keyMap[sf::Keyboard::RControl]        = CEGUI::Key::RightControl ;
	m_keyMap[sf::Keyboard::Divide]          = CEGUI::Key::Divide       ;
	m_keyMap[sf::Keyboard::RAlt]            = CEGUI::Key::RightAlt     ;
	m_keyMap[sf::Keyboard::Pause]           = CEGUI::Key::Pause        ;
	m_keyMap[sf::Keyboard::Home]            = CEGUI::Key::Home         ;
	m_keyMap[sf::Keyboard::Up]              = CEGUI::Key::ArrowUp      ;
	m_keyMap[sf::Keyboard::PageUp]          = CEGUI::Key::PageUp       ;
	m_keyMap[sf::Keyboard::Left]            = CEGUI::Key::ArrowLeft    ;
	m_keyMap[sf::Keyboard::Right]           = CEGUI::Key::ArrowRight   ;
	m_keyMap[sf::Keyboard::End]             = CEGUI::Key::End          ;
	m_keyMap[sf::Keyboard::Down]            = CEGUI::Key::ArrowDown    ;
	m_keyMap[sf::Keyboard::PageDown]        = CEGUI::Key::PageDown     ;
	m_keyMap[sf::Keyboard::Insert]          = CEGUI::Key::Insert       ;
	m_keyMap[sf::Keyboard::Delete]          = CEGUI::Key::Delete       ;

	m_mouseButtonMap[sf::Mouse::Left]		= CEGUI::LeftButton        ;
	m_mouseButtonMap[sf::Mouse::Middle]		= CEGUI::MiddleButton      ;
	m_mouseButtonMap[sf::Mouse::Right]		= CEGUI::RightButton       ;
	m_mouseButtonMap[sf::Mouse::XButton1]	= CEGUI::X1Button          ;
	m_mouseButtonMap[sf::Mouse::XButton2]	= CEGUI::X2Button          ;
}

CEGUI::Key::Scan GUIManager::toCEGUIKey(sf::Keyboard::Key key)
{
    return m_keyMap[key];
}

CEGUI::MouseButton GUIManager::toCEGUIMouseButton(sf::Mouse::Button button)
{
    return m_mouseButtonMap[button];
}
