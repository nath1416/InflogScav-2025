#include "input.h"

void Input::beginFrame()
{
    m_mouseDeltaX = 0;
    m_mouseDeltaY = 0;
    m_scroll = 0;

    for (auto& kv : m_keysPressed)
        kv.second = false;
}

void Input::keyCallback(int key, int action)
{
    if (action == GLFW_PRESS)
    {
        m_keysHeld[key] = true;
        m_keysPressed[key] = true;  
    }
    else if (action == GLFW_RELEASE)
    {
        m_keysHeld[key] = false;
    }
}

void Input::mouseMoveCallback(double x, double y)
{
    if (m_firstMouse)
    {
        m_lastMouseX = x;
        m_lastMouseY = y;
        m_firstMouse = false;
    }

    m_mouseDeltaX = (int)(x - m_lastMouseX);
    m_mouseDeltaY = (int)(y - m_lastMouseY);

    m_lastMouseX = x;
    m_lastMouseY = y;
}

void Input::scrollCallback(double y)
{
    m_scroll = (y > 0) ? 1 : (y < 0 ? -1 : 0);
}

bool Input::getKeyHold(Key k)
{
    return m_keysHeld[k];
}

bool Input::getKeyPress(Key k)
{
    return m_keysPressed[k];
}

void Input::getMouseMotion(int& x, int& y)
{
    x = m_mouseDeltaX;
    y = m_mouseDeltaY;
}

int Input::getMouseScrollDirection()
{
    return m_scroll;
}
