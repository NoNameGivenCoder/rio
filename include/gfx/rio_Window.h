#ifndef RIO_GFX_WINDOW_H
#define RIO_GFX_WINDOW_H

#include <gpu/rio_Texture.h>

#if RIO_IS_CAFE
#include <gfx/cafe/rio_NativeWindowCafe.h>
#elif RIO_IS_WIN
#include <gfx/win/rio_NativeWindowWin.h>
#endif

namespace rio {

class Window
{
    // TODO: Customizable Color Buffer and Depth-Stencil Buffer formats

public:
    // Create window singleton instance
    // Parameters:
    // - width: The desired width
    // - height: The desired height
    static bool createSingleton(u32 width = 1280, u32 height = 720);

    // Destroy window singleton instance
    static void destroySingleton();

    // Get window singleton instance
    static Window* instance() { return sInstance; }

public:
    // Get window current width
    u32 getWidth() const { return mWidth; }

    // Get window current height
    u32 getHeight() const { return mHeight; }

    // Get the native window instance
    const NativeWindow& getNativeWindow() const
    {
        return mNativeWindow;
    }

    // Make the context of this window the current context
    void makeContextCurrent() const;

    // Set the swap interval (how many refreshes to wait before flipping the scan buffers)
    // Parameters:
    // - swap_interval: The swap interval is this value divided by the refresh rate (59.94 Hz on Cafe)
    //                  e.g. On Cafe, a value of 2 will give a swap interval of 2 / 59.94 = ~33 ms
    //                  A value of 0 means swapping should happen as quickly as possible (For GLFW)
    void setSwapInterval(u32 swap_interval);

    // Check if window is still running
    bool isRunning() const;

    // Swap the front and back buffers
    // This function will perform a GPU flush and block until swapping is done
    // For Cafe, TV output is automatically duplicated to the DRC
    void swapBuffers() const;

    // Clear the window's color buffer
    void clearColor(f32 r, f32 g, f32 b, f32 a = 1.0f);

    // Clear the window's depth buffer
    void clearDepth();
    void clearDepth(f32 depth);

    // Clear the window's stencil buffer
    void clearStencil();
    void clearStencil(u8 stencil);

    // Clear the window's depth-stencil buffer
    void clearDepthStencil();
    void clearDepthStencil(f32 depth, u8 stencil = 0);

#if RIO_IS_WIN

    // Get the window's inner handle (deprecated)
    static GLFWwindow* getWindowInner()
    {
        if (sInstance == nullptr)
            return nullptr;

        return sInstance->mNativeWindow.handle;
    }

#endif // RIO_IS_WIN

    static NativeTexture2DHandle getWindowColorBuffer()
    {
        if (sInstance == nullptr)
            return RIO_NATIVE_TEXTURE_2D_HANDLE_NULL;

#if RIO_IS_CAFE
        return &sInstance->mNativeWindow.color_buffer_texture;
#elif RIO_IS_WIN
        return sInstance->mNativeWindow.color_buffer_handle;
#endif
    }

private:
    Window(u32 width, u32 height)
    {
        RIO_ASSERT(width > 0);
        RIO_ASSERT(height > 0);

        mWidth  = width;
        mHeight = height;
    }

    Window(const Window&);
    Window& operator=(const Window&);

    // Initialize the window
    bool initialize_();
    // Terminate the window
    void terminate_();

#if RIO_IS_CAFE

    // Acquire and release foreground
    bool foregroundAcquire_();
    void foregroundRelease_();

#elif RIO_IS_WIN

    // Set viewport and scissor to framebuffer size
    inline void setVpToFb_() const;
    // Restore current viewport and scissor
    inline void restoreVp_() const;

#endif

private:
    // Window singleton instance
    static Window* sInstance;

    u32             mWidth;         // Current width
    u32             mHeight;        // Current height
    NativeWindow    mNativeWindow;  // Native window instance
};

}

#endif // RIO_GFX_WINDOW_H
