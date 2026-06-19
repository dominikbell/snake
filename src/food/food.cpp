#include "food.hpp"

void Food::spawn(const Snake& snake) {
  m_location.x = m_gen_width(m_engine);
  m_location.y = m_gen_height(m_engine);

  while (colliding(snake)) {
    m_location.x = m_gen_width(m_engine);
    m_location.y = m_gen_height(m_engine);
  }

  m_has_been_eaten = false;
}
