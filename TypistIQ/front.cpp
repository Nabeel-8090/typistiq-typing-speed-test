#include "front.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// Constructor: Initializes resources and positions UI elements
FrontPage::FrontPage() {
    loadResources();
    positionElements();
}

// Loads fonts from files used in the UI
void FrontPage::loadResources() {
    if (!mainFont.loadFromFile("font.ttf") ||
        !titleFont.loadFromFile("global_bikers.ttf") ||
        !taglineFont.loadFromFile("WinkyRough_Bold.ttf")) {
        cerr << "Error loading fonts" << endl;
    }
    buttonFont = mainFont;
}

// Positions all UI elements like title, input, button, etc.
void FrontPage::positionElements() {
    const float windowWidth = 800.f;
    const float windowHeight = 600.f;
    const float padding = 20.f;

    // Title Text Setup
    titleText.setFont(titleFont);
    titleText.setString("TypistIQ");
    titleText.setCharacterSize(72);
    titleText.setFillColor(accentColor);
    titleText.setPosition((windowWidth - titleText.getLocalBounds().width) / 2, padding);

    // Tagline Text Setup
    taglineText.setFont(taglineFont);
    taglineText.setString("\"Type. Survive. Dominate.\"");
    taglineText.setCharacterSize(28);
    taglineText.setFillColor(textColor);
    taglineText.setPosition(
        (windowWidth - taglineText.getLocalBounds().width) / 2,
        titleText.getPosition().y + titleText.getLocalBounds().height + 10
    );

    // Label above name input box
    inputLabel.setFont(mainFont);
    inputLabel.setString("Enter Your Name:");
    inputLabel.setCharacterSize(22);
    inputLabel.setFillColor(textColor);
    inputLabel.setPosition(
        (windowWidth - inputLabel.getLocalBounds().width) / 2,
        taglineText.getPosition().y + taglineText.getLocalBounds().height + 50
    );

    // Input box setup
    inputBox.setSize(Vector2f(350, 40));
    inputBox.setFillColor(Color::White);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(accentColor);
    inputBox.setPosition(
        (windowWidth - inputBox.getSize().x) / 2,
        inputLabel.getPosition().y + inputLabel.getLocalBounds().height + 30
    );

    // Text inside the input box
    inputText.setFont(mainFont);
    inputText.setCharacterSize(20);
    inputText.setFillColor(Color::Black);
    inputText.setPosition(
        inputBox.getPosition().x + 10,
        inputBox.getPosition().y + (inputBox.getSize().y - inputText.getLocalBounds().height) / 2 - 10
    );

    // Start button setup
    startButton.setSize(Vector2f(150, 50));
    startButton.setFillColor(buttonColor);
    startButton.setPosition(
        (windowWidth - startButton.getSize().x) / 2,
        inputBox.getPosition().y + inputBox.getSize().y + 30
    );

    // Text inside the start button
    startButtonText.setFont(buttonFont);
    startButtonText.setString("START");
    startButtonText.setCharacterSize(24);
    startButtonText.setFillColor(textColor);
    startButtonText.setPosition(
        startButton.getPosition().x +
        (startButton.getSize().x - startButtonText.getLocalBounds().width) / 2,
        startButton.getPosition().y +
        (startButton.getSize().y - startButtonText.getLocalBounds().height) / 2 - 5
    );
}

// Main screen loop for front page
int FrontPage::run(RenderWindow& window) {
    string playerInput;
    bool isTyping = false;
    gameStarted = false;

    // Loop until window closes or game starts
    while (window.isOpen() && !gameStarted) {
        handleEvents(window, isTyping, playerInput, gameStarted);
        draw(window, playerInput);
    }

    return 0;  // Move to next game screen
}

// Handles all events: mouse click, typing, closing
void FrontPage::handleEvents(RenderWindow& window, bool& isTyping, string& playerInput, bool& gameStarted) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }

        if (event.type == Event::MouseButtonPressed) {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

            if (inputBox.getGlobalBounds().contains(mousePos)) {
                isTyping = true;
                inputBox.setOutlineColor(Color::Yellow);
            } else {
                isTyping = false;
                inputBox.setOutlineColor(accentColor);
            }

            if (startButton.getGlobalBounds().contains(mousePos) && !playerInput.empty()) {
                cout << "Starting game for: " << playerInput << "\n";
                gameStarted = true;
            }
        }

        if (event.type == Event::TextEntered && isTyping) {
            if (event.text.unicode == '\b') {
                if (!playerInput.empty()) {
                    playerInput.pop_back();
                }
            } else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\t') {
                playerInput += static_cast<char>(event.text.unicode);
            }
            inputText.setString(playerInput);
        }
    }

    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
    if (startButton.getGlobalBounds().contains(mousePos)) {
        startButton.setFillColor(buttonHoverColor);
    } else {
        startButton.setFillColor(buttonColor);
    }
}

// Renders all elements on the screen
void FrontPage::draw(RenderWindow& window, const string& playerInput) {
    window.clear(backgroundColor);

    window.draw(titleText);
    window.draw(taglineText);

    window.draw(inputLabel);
    window.draw(inputBox);
    inputText.setString(playerInput);
    window.draw(inputText);

    if (playerInput.empty()) {
        startButton.setFillColor(Color(100, 100, 100));
    }
    window.draw(startButton);
    window.draw(startButtonText);

    window.display();
}
