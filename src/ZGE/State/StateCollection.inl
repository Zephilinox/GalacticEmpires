template <class T>
void StateCollection::push(sf::RenderWindow& window)
{
    m_states.push(std::make_shared<T>(T(window, *this)));
}

