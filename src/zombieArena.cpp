#include "Platform/Platform.hpp"
#include <SFML/Graphics.hpp>
#include "zombieArena.hpp"
#include "Player.hpp"
#include "textureHolder.hpp"

using namespace sf;

int main() {

    TextureHolder holder;

    // The game will always be in one of four states
    enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING};

    // Start with the GAME_OVER state
    State state = State::GAME_OVER;

    // Get the screen resolution and create an SFML window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);

    // Create an SFML View for the main action
    View mainView(sf::FloatRect(0,0,resolution.x,resolution.y));
    // Clock for timing everything
    Clock clock;
    // How long has the PLAYING state been active?
    Time gameTimeTotal;
    // Where is the mouse in relation to world coordinates?
    Vector2f mouseWorldPosition;
    // Where is the mouse in relation to screen coordinates?
    Vector2i mouseScreenPosition;

    // Create an instance of the Player class
    Player player;

    // The boundaries of the arena
    IntRect arena;

    // Create the background
    VertexArray background;
    // Load the texture for our background vertex array
    Texture textureBackground = TextureHolder::GetTexture("graphics/background_sheet.png") ;

    // Prepare for a horde of zombies
    int numZombies=0; // Number at start of wave
    // int numZombiesAlive=0; // Number to be killed
    Zombie* zombies = nullptr;

    // The main game loop
    while (window.isOpen()) {

        /*
        **************************************
        Handle input
        **************************************
        */

        // Handle events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyPressed) {
                // Pause game while playing
                if (event.key.code == Keyboard::Return && state == State::PLAYING) {
                    state = State::PAUSED;
                }
                // Restart while paused
                else if (event.key.code == Keyboard::Return && state == State::PAUSED) {
                    state = State::PLAYING;
                    // Reset the clock so there isn't a frame jump
                    clock.restart();
                }
                // State a new game while in GAME_OVER state
                else if (event.key.code == Keyboard::Return && state == State::GAME_OVER) {
                    state = State::LEVELING_UP;
                }

                if (state == State::PLAYING) {
                    // populated later - if a key other then return is oressed during gameplay
                }
            } // End if (event.type == Event::KeyPressed)
        } // End event polling

        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        // Handle controls while playing
        if (state == State::PLAYING) {
            // Handle the pressing and releasing of the WASD keys
            if (Keyboard::isKeyPressed(Keyboard::W)) {
                player.moveUp();
            }
            else {
                player.stopUp();
            }
            if (Keyboard::isKeyPressed(Keyboard::S)) {
                player.moveDown();
            }
            else {
                player.stopDown();
            }
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                player.moveLeft();
            }
            else {
                player.stopLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                player.moveRight();
            }
            else {
                player.stopRight();
            }
        } // End WASD while playing

        // Handle the leveling up state
        if (state == State::LEVELING_UP) {
            if (event.key.code == Keyboard::Num1) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num2) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num3) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num4) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num5) {
                state = State::PLAYING;
            }
            if (event.key.code == Keyboard::Num6) {
                state = State::PLAYING;
            }

            if (state == State::PLAYING) {
                // Prepare the level - we will update this later
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                // Pass the vertex array by reference to the createBackground function
                int tileSize = createBackground(background, arena);

                // Spawn the player in the middle of the arena
                player.spawn(arena, resolution, tileSize);

                // Create a horde of zombies
                numZombies = 10;

                // Delete the previously allocated memory ( if it exists )
                delete[] zombies; // Note use of delete[] - should use [] when deleting arrays from heap
                zombies = createHorde(numZombies, arena);
                // numZombiesAlive = numZombies;

                // Reset the clock so there isn't a frame jump
                clock.restart();
            }

        } // End levelling up

        /*
        *******************************
        UPDATE THE FRAME
        *******************************
        */

        if (state == State::PLAYING) {
            // Update the delta time
            Time dt = clock.restart();
            // Update the total game time
            gameTimeTotal += dt;
            // Make a decimal fraction of 1 from the delta time
            float dtAsSeconds = dt.asSeconds();

            // Find the mouse pointer
            mouseScreenPosition = Mouse::getPosition(window);
            // Convert mouse position to world coordinates of mainView
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            // Update the player
            player.update(dtAsSeconds, Mouse::getPosition());

            // Make a note of the players new position
            Vector2f playerPosition(player.getCenter());

            // Make the view centre around the player
            mainView.setCenter(player.getCenter());

            // Loop through each Zombie and update then if alive
            for (int i = 0; i < numZombies; i++) {
                if (zombies[i].isAlive()) {
                    zombies[i].update(dt.asSeconds(), playerPosition);
                }
            }

        } // End updating the scene

        /*
        *******************************
        Draw the scene
        *******************************
        */

        if (state == State::PLAYING) {
            window.clear();

            // Set the mainView to be displayed in the window
            // And draw everything related to it
            window.setView(mainView);

            // Draw the background
            window.draw(background, &textureBackground);

            // Draw the zombies
            for (int i = 0; i < numZombies; i++) {
                window.draw(zombies[i].getSprite());
            }

            // Draw the player
            window.draw(player.getSprite());
        }

        if (state == State::LEVELING_UP) {

        }

        if (state == State::PAUSED) {


        }
        if (state == State::GAME_OVER) {

        }

        window.display();


    }

    // Delete the previously allocated memory ( if it exists )
    delete[] zombies;

    return 0;
}
