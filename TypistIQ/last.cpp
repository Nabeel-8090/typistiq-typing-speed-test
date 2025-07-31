#include "last.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

// Constructor initializes WPM and accuracy values, loads fonts, and positions elements
ResultsScreen::ResultsScreen(int wpm, float accuracy)
    : wordsPerMinute(wpm), accuracy(accuracy)
{
    if (!mainFont.loadFromFile("font.ttf") || !titleFont.loadFromFile("global_bikers.ttf"))
    {
        cerr << "Error loading fonts" << endl;
    }
    positionElements();
}

// Set positions, styles, and content for all text elements
void ResultsScreen::positionElements()
{
    const float windowWidth = 800.f;
    const float windowHeight = 600.f;
    const float padding = 30.f;

    // Title
    titleText.setFont(titleFont);
    titleText.setString("RESULTS");
    titleText.setCharacterSize(60);
    titleText.setFillColor(accentColor);
    titleText.setPosition((windowWidth - titleText.getLocalBounds().width) / 2, padding);

    // WPM display
    wpmText.setFont(mainFont);
    wpmText.setString("Words Per Minute: " + to_string(wordsPerMinute));
    wpmText.setCharacterSize(28);
    wpmText.setFillColor(textColor);
    wpmText.setPosition((windowWidth - wpmText.getLocalBounds().width) / 2, padding + 190);

    // Accuracy display
    accuracyText.setFont(mainFont);
    accuracyText.setString("Accuracy: " + to_string(static_cast<int>(accuracy)) + "%");
    accuracyText.setCharacterSize(28);
    accuracyText.setFillColor(textColor);
    accuracyText.setPosition((windowWidth - accuracyText.getLocalBounds().width) / 2, padding + 240);

    // Feedback message based on WPM
    string feedback;
    if (wordsPerMinute < 20)
    {
        feedback = "Keep practicing! Beginner typists average 20-30 WPM.";
    }
    else if (wordsPerMinute < 40)
    {
        feedback = "Good job! Average typists range between 35-45 WPM.";
    }
    else if (wordsPerMinute < 60)
    {
        feedback = "Great work! You're typing faster than average.";
    }
    else
    {
        feedback = "Excellent! You're in the top tier of typists!";
    }

    feedbackText.setFont(mainFont);
    feedbackText.setString(feedback);
    feedbackText.setCharacterSize(24);
    feedbackText.setFillColor(accentColor);
    feedbackText.setPosition(
        (windowWidth - feedbackText.getLocalBounds().width) / 2, padding + 290);

    // Instruction for user to return to main menu
    instructionText.setFont(mainFont);
    instructionText.setString("Press ENTER key to return to the main menu");
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(textColor);
    instructionText.setPosition((windowWidth - instructionText.getLocalBounds().width) / 2, windowHeight - 60);
}

// Main loop for results screen
int ResultsScreen::run(RenderWindow &window)
{
    bool screenActive = true;
    while (window.isOpen() && screenActive)
    {
        handleEvents(window, screenActive);
        draw(window);
    }
    return 0; // Go back to front page
}

// Handle events like window close or ENTER key press
void ResultsScreen::handleEvents(RenderWindow &window, bool &screenActive)
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            window.close();
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
        {
            screenActive = false;
        }
    }
}

// Draw all UI elements on the window
void ResultsScreen::draw(RenderWindow &window)
{
    window.clear(backgroundColor);

    window.draw(titleText);
    window.draw(wpmText);
    window.draw(accuracyText);
    window.draw(feedbackText);
    window.draw(instructionText);

    window.display();
}
