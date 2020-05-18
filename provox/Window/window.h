#pragma once

#include <exception>

class WindowException : public std::exception
{
public:
    WindowException() = delete;
    WindowException(const char* msg) : std::exception(msg) {}
};

class Window
{
public:
    static Window* Create(Float x, Float y, Float width, Float height);

    // Initialization
    virtual bool Initialize(Float x, Float y, Float w, Float h) = 0;
    
    // UI Functions
    virtual bool InitializeUI() = 0;
    virtual void StartUIFrame() = 0;
    virtual bool ShutdownUI() = 0;
    
    // Message loop
    virtual bool MessageLoop() = 0;

    // Getters
    virtual AABB2D<Float> GetRect() = 0;

    Float GetX() { return GetRect().GetX(); }
    Float GetY() { return GetRect().GetY(); }
    Float GetWidth() { return GetRect().GetWidth(); }
    Float GetHeight() { return GetRect().GetHeight(); }

    void* GetHandle() { return m_handle; }

protected:
    void* m_handle;
};
