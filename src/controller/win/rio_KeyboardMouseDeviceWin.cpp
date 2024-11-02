#include <misc/rio_Types.h>

#if RIO_IS_WIN

#include <controller/win/rio_KeyboardMouseDeviceWin.h>
#include <gfx/rio_Window.h>

#include <misc/gl/rio_GL.h>
#ifdef _WIN32
#include <misc/win/rio_Windows.h>
#endif

namespace rio {

KeyboardMouseDevice::KeyboardMouseDevice(ControllerMgr* mgr)
    : ControlDevice(mgr)
    , mIsLastReadSuccess(false)
{
    mId = ControllerDefine::DEVICE_KEYBOARD_MOUSE;
}

KeyboardMouseDevice::~KeyboardMouseDevice()
{
}

void KeyboardMouseDevice::calc()
{
#ifdef _WIN32
    mIsLastReadSuccess = GetKeyboardState(mKeyState);
#else
    mIsLastReadSuccess = true;
#endif
#ifndef RIO_NO_GLFW_CALLS
    f64 pos_x, pos_y;
    glfwGetCursorPos(Window::getWindowInner(), &pos_x, &pos_y);
#else
    f64 pos_x = 0;
    f64 pos_y = 0;
#endif // RIO_NO_GLFW_CALLS
    mCursorPos.set(static_cast<f32>(pos_x), static_cast<f32>(pos_y));
}

}

#endif // RIO_IS_WIN
