#ifndef LAST_HPP
#define LAST_HPP

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

// Displays typing test results
class ResultsScreen {
public:
    ResultsScreen(int wpm, float accuracy);  // Constructor
    int run(RenderWindow& window);           // Run the results screen

private:
    void handleEvents(RenderWindow& window, bool& screenActive);  // Handle input
    void draw(RenderWindow& window);                              // Render elements
    void positionElements();                                      // Set positions

    // Fonts
    Font mainFont;
    Font titleFont;

    // UI Text
    Text titleText;
    Text wpmText;
    Text accuracyText;
    Text feedbackText;
    Text instructionText;

    // Data
    int wordsPerMinute;
    float accuracy;

    // Colors
    Color backgroundColor = Color(30, 30, 30);
    Color textColor = Color::White;
    Color accentColor = Color(255, 204, 0);
};

#endif
