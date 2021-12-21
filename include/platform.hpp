#ifndef VIRTUAL_GALAXY_PLATFORM_HPP
#define VIRTUAL_GALAXY_PLATFORM_HPP

#if _WIN32
    // Disable unused libraries
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    // Disable Windows min max (to avoid clash with std min max)
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

    #include <Windows.h>
    #include <shellapi.h>

    #define MAIN_FUNCTION() \
        INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
#else
#define MAIN_FUNCTION() \
        int main()
#endif

/**
 * Application entry point
 */
#define RUN(app) \
        MAIN_FUNCTION() { \
            app a; \
            a.run();   \
            return 0; \
        }

#endif //VIRTUAL_GALAXY_PLATFORM_HPP
