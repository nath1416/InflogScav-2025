#ifndef WINDOW_H
#define WINDOW_H

#include <unordered_map>
#include <GLFW/glfw3.h>

class Input {
public:
    enum Key {
        ESC = GLFW_KEY_ESCAPE,
        T = GLFW_KEY_T,
        R = GLFW_KEY_R,
        W = GLFW_KEY_W,
        A = GLFW_KEY_A,
        S = GLFW_KEY_S,
        D = GLFW_KEY_D,
        Q = GLFW_KEY_Q,
        E = GLFW_KEY_E,
        SPACE = GLFW_KEY_SPACE
    };

    void beginFrame();                 // Reset per-frame data
    void keyCallback(int key, int action);
    void mouseMoveCallback(double x, double y);
    void scrollCallback(double y);

    bool getKeyHold(Key k);
    bool getKeyPress(Key k);
    void getMouseMotion(int& x, int& y);
    int getMouseScrollDirection();

private:
    std::unordered_map<int, bool> m_keysHeld;
    std::unordered_map<int, bool> m_keysPressed;

    double m_lastMouseX = 0.0, m_lastMouseY = 0.0;
    int m_mouseDeltaX = 0, m_mouseDeltaY = 0;

    int m_scroll = 0;
    bool m_firstMouse = true;
};

#endif
