#ifndef FRONT_HPP
#define FRONT_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

// Class that handles the front page of the TYPEVERSE application
class FrontPage {
public:
    FrontPage(); // Constructor

    int run(RenderWindow& window); // Runs the front page loop
    string getPlayerName() const { 
        return playerInput; // Returns user input
    }

private:
    // Helper methods
    void loadResources(); // Load fonts and assets
    void positionElements(); // Set positions of UI elements
    void handleEvents(RenderWindow &window, bool &isTyping, string &playerInput, bool &gameStarted); // Handle input
    void draw(RenderWindow &window, const string &playerInput); // Render everything

    // Fonts used for different elements
    Font mainFont;
    Font titleFont;
    Font taglineFont;
    Font buttonFont;

    // UI text elements
    Text titleText;
    Text taglineText;
    Text inputLabel;
    Text inputText;
    Text startButtonText;

    // Input box and button shapes
    RectangleShape inputBox;
    RectangleShape startButton;

    // Theme colors
    Color backgroundColor = Color(30, 30, 30);
    Color accentColor = Color(255, 204, 0);
    Color textColor = Color::White;
    Color buttonColor = Color(50, 50, 200);
    Color buttonHoverColor = Color(100, 100, 255);

    // State variables
    string playerInput;
    bool gameStarted;
};

#endif
