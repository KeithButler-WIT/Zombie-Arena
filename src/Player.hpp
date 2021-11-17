#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>

using namespace sf;

class Player {

    private:
        const float START_SPEED = 200;
        const float START_HEALTH = 100;

        // Where is the player?
        Vector2f m_Position;

        // Player sprite
        Sprite m_Sprite;

        // Player texture
        Texture m_Texture;

        // What if the screen resolution?
        Vector2f m_Resolution;

        // How big is the current arena?
        IntRect m_Arena;

        // How big is each tile of the arean?
        int m_TileSize;

        // Which direcetions is the player currently moving in?
        bool m_UpPressed;
        bool m_DownPressed;
        bool m_LeftPressed;
        bool m_RightPressed;

        // How much health has the player got?
        int m_Health;

        // What is the maximum health the player can have?
        int m_MaxHealth;

        // When was the player last hit?
        Time m_LastHit;

        // Speed in pixels per second
        float m_Speed;

    public:
        Player();

        void spawn(IntRect arena, Vector2f resolution, int tileSize);

        // Called at end of game
        void resetPlayerStats();

        // Handle the player getting hit by a zombie
        bool hit(Time timeHit);

        // How long since player hit?
        Time getLastHitTime();

        // Where is the player?
        FloatRect getPosition();

        // Where is the center of the player?
        Vector2f getCenter();

        // Which angle is the player facing?
        float getRotation();

        // Send a coy of the sprite to main
        Sprite getSprite();

        // How much health has the player currently got?
        int getHealth();

        // Move the player
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

        // Stop the player moving in a specific direction
        void stopLeft();
        void stopRight();
        void stopUp();
        void stopDown();

        // Called every frame
        void update(float elapsedTime, Vector2i mousePosition);

        // Give player a speed boost - used for levelling up
        void upgradeSpeed();

        // Increase max health - used for levelling up
        void upgradeHealth();

        // Increase health - collision with med kit
        void increaseHealthLevel(int amount);

};

#endif // PLAYER_H_
