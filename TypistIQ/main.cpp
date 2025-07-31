#include <SFML/Graphics.hpp>
#include "front.hpp"
#include "middle.hpp"
#include "last.hpp"

using namespace sf;

int main()
{

    RenderWindow window(VideoMode(800, 600), "TypistIQ - Typing Speed Test Application");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        // Front Page
        FrontPage frontPage;
        if (frontPage.run(window) != 0)
        {
            return 1; // Exit if front page failed
        }

        // Typing test (Middle Page)
        TypingTest typingTest;
        if (typingTest.run(window) != 0)
        {
            return 1; // Exit if typing test failed
        }

        // Results screen (Last Page)
        ResultsScreen resultsScreen(typingTest.getWPM(), typingTest.getAccuracy());
        if (resultsScreen.run(window) != 0)
        {
            return 1; // Exit if results screen failed
        }
    }

    return 0;
}