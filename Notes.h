#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;
/**
 * This file requires SFML2
 * The Drawable, Transformable, Sound, SoundBuffer, Vector etc. classes are included in the SFML2
 */

/*
 * The Note class holds audio data and contains methods to play back the audio data
 * as well as get data relating to the musical quality and rythmic duration
 * these values are not in standard notation
 */
class Note
{
public:
    //loads note of the specified duration and quality(tone)
    void load(int duration,int quality);
    
    //Plays the note
    void Play();
    
    //returns the duration of the note
    int getDuration();
    
    //returns the quality of the note
    int getQuality();
protected:
    //Buffer to hold file
    SoundBuffer file;
    
    //Plays sound from buffer
    Sound note;
    
    //Duration of the note eg. 1 for 8th 2 for 4th 3 for dotted 8th 4 for dotted quarter
    //Valid values are any integer from 1 to 4
    int duration;
    
    //Quality of the note 
    //Acceptable values are integers from 1 - 12
    //Based on major scale, not chromatic
    int quality;
};

/*
 * The tile class represents a 100x100 square with a specified color
 * Further documentation on the implementation of a class that extends from
 * sf::Drawable can be found on sfml-dev.org in the tutorials and documentation
 */
class Tile : public Drawable, public Transformable
{
public:
    //sets the x and y position of the top left corner, as well as the color
    bool load(float x,float y,int color);
    
    //returns the x member of coordinates variable
    float getX();
    
    //returns the y member of coordinates variable
    float getY();
protected:
    //Contains the tile sheet
    Texture t_tile;
    
    //Vertices of the square
    VertexArray t_vertices;
    
    //Coordinates of the upper left corner
    Vector2f coordinates;
    
    //needed to inherit from sf::Drawable
    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &t_tile;
        target.draw(t_vertices, states);
    }
};

/*
 * Inherits from Note and Tile classes
 * Connects a note to a tile of a specified color
 */
class NoteTile : public Note, public Tile
{
public:
    //loads the tile and note
    //The color of the tile is dependent on the quality parameter
    void load(float x,float y,int duration,int quality);
    
    //plays the note
    void Play();
    
    //Returns the value of the SleepTime field
    float getSleepTime();
    
    //Returns the x coordinate of the top-left corner of the tile
    float getX();
    
    //Returns the y coordinate of the top-left corner of the tile
    float getY();
    
    //returns the top-left corner of the tile as an sf::Vector2f
    Vector2f getP();
    
    //Returns the quality of the note
    //See note class for more detail
    int getQuality();
    
    //Returns the duration of the note
    //See note class for more detail
    int getDuration();
    
    //Legacy code
    //Doesn't do anything
    void Draw();
protected:
    //The amount of time in seconds of the note's duration
    //Based on 150 beats per minute constant
    float SleepTime;
};

/*
 * Entity class is a 100x100 square that moves around the tile grid
 */
class Entity
{
public:
    //Sets all values
    //Changing anything in this class will likely break the program
    Entity();
    
    //Moves the entity left
    void goLeft();
    
    //Moves the entity right
    void goRight();
    
    //Moves the entity up
    void goUp();
    
    //Moves the entity down
    void goDown();
    
    //Jumps the entity to a specified sf::Vector2f coordinate
    void jump(Vector2f);
    
    //Algorithm to automate entity movement
    //Moslty random, but certain fixed positions will cause the entity to jump
    //to a preset position
    void automate();
    
    //Returns the x coordinate
    float getX();
    
    //Returns the y coordinate
    float getY();
    
    //Returns the position as sf::Vector2f
    Vector2f getP();
    
    //Sprite for visual representation of entity
    Sprite s_entity;
protected:
    //Holds the image
    Texture t_entity;
    
    //Constant used for goUp()
    Vector2f up;
    
    //Constant used for goDown()
    Vector2f down;
    
    //Constant used for goLeft()
    Vector2f left;
    
    //Constant used for goRight()
    Vector2f right;
    
    //Constant fixed jump positions
    Vector2f jump1;
    Vector2f jump2;
    Vector2f jump3;
    Vector2f jump4;
    Vector2f jump5;
    Vector2f jump6;
    Vector2f jump7;
    Vector2f jump8;
};

void Note::load(int duration, int quality)
{
    this->duration = duration;
    this->quality = quality;

    string quality_names[] = {"i.wav","ii.wav","iii.wav","iv.wav","v.wav","vi.wav","vii.wav","i8va.wav","ii8va.wav","iii8va.wav","iv8va.wav","v8va.wav"};
    string duration_names[] = {"Eighth_","Quarter_","Dotted_Eighth_","Dotted_Quarter_"};
    string folder_names[] = {"Note_Files\\i\\","Note_Files\\ii\\","Note_Files\\iii\\","Note_Files\\iv\\","Note_Files\\v\\","Note_Files\\vi\\","Note_Files\\vii\\","Note_Files\\i8va\\","Note_Files\\ii8va\\","Note_Files\\iii8va\\","Note_Files\\iv8va\\","Note_Files\\v8va\\",};
    if (!file.loadFromFile(folder_names[quality-1]+duration_names[duration-1]+quality_names[quality-1]))
        cout << "could not load file";
    note.setBuffer(file);
}
void Note::Play()
{
    note.play();
}
int Note::getDuration()
{
    return duration;
}
int Note::getQuality()
{
    return quality;
}

bool Tile::load(float x, float y, int color)
{
    if (!t_tile.loadFromFile("tile_set.png"))
        return false;
    t_vertices.setPrimitiveType(Quads);
    int corners = 4;
    float tx = 0;
    float ty = 0;
    t_vertices.resize(corners);
    t_vertices[0].position = Vector2f(x,y);
    t_vertices[1].position = Vector2f(x+100,y);
    t_vertices[2].position = Vector2f(x+100,y+100);
    t_vertices[3].position = Vector2f(x,y+100);
    for (int a = 0; a < color; ++a)
    {
        if (a % 4 == 0)
        {
            tx = 0;
            ty += 100;
        }
        else
            tx += 100;
    }
    t_vertices[0].texCoords = Vector2f(tx,ty);
    t_vertices[1].texCoords = Vector2f(tx+100,ty);
    t_vertices[2].texCoords = Vector2f(tx+100,ty+100);
    t_vertices[3].texCoords = Vector2f(tx,ty+100);

    coordinates = t_vertices[0].position;
    return true;
}
float Tile::getX()
{
    return coordinates.x;
}
float Tile::getY()
{
    return coordinates.y;
}

void NoteTile::load(float x, float y,int duration, int quality)
{
    Note::load(duration,quality);
    Tile::load(x,y,quality);
    switch (duration)
    {
    case 1:
        SleepTime = (60.f/150.f)/2.f;
        break;
    case 2:
        SleepTime = 60.f/150.f;
        break;
    case 3:
        SleepTime = (60.f/150.f)/2.f + ((60.f/150.f)/2.f)/2.f;
        break;
    case 4:
        SleepTime = 60.f/150.f + (60.f/150.f)/2.f;
        break;
    default:
        cout << "invalid duration";
        break;
    }
}
void NoteTile::Play()
{
    note.play();
    sleep(seconds(SleepTime));

}
float NoteTile::getSleepTime()
{
    return SleepTime;
}
float NoteTile::getX()
{
    return Tile::getX();
}
float NoteTile::getY()
{
    return Tile::getY();
}
int NoteTile::getDuration()
{
    return Note::getDuration();
}
int NoteTile::getQuality()
{
    return Note::getQuality();
}
Vector2f NoteTile::getP()
{
    return Tile::coordinates;
}

Entity::Entity()
{
    if (!t_entity.loadFromFile("Character.png"))
        cout << "could not load entity texture";
    s_entity.setTexture(t_entity);
    s_entity.setTextureRect(IntRect(0,0,100,100));
    s_entity.setPosition(0,0);
    up.x = 0;
    up.y = -100;

    down.x = 0;
    down.y = 100;

    left.x = -100;
    left.y = 0;

    right.x = 100;
    right.y = 0;

    jump1.x = 300;
    jump1.y = 200;

    jump2.x = 300;
    jump2.y = 300;

    jump3.x = 300;
    jump3.y = 100;

    jump4.x = 200;
    jump4.y = 100;

    jump5.x = 200;
    jump5.y = 300;

    jump6.x = 200;
    jump6.y = 200;

    jump7.x = 300;
    jump7.y = 400;

    jump8.x = 200;
    jump8.y = 400;
}
void Entity::goLeft()
{
    s_entity.move(left);
}
void Entity::goRight()
{
    s_entity.move(right);
}
void Entity::goUp()
{
    s_entity.move(up);
}
void Entity::goDown()
{
    s_entity.move(down);
}
void Entity::jump(Vector2f location)
{
    s_entity.setPosition(location);
}
float Entity::getX()
{
    return s_entity.getPosition().x;
}
float Entity::getY()
{
    return s_entity.getPosition().y;
}
Vector2f Entity::getP()
{
    return s_entity.getPosition();
}
void Entity::automate()
{
    int x = (int) getX()/100;
    int y = (int) getY()/100;
    int random;
    if ((x==1 && y ==1)||(x==1 && y==4)||(x==4 && y==1)||(x==4 && y==4))
    {
        random = rand() % 2;
        switch (x)
        {
        case 1:
            switch (y)
            {
            case 1:
                switch (random)
                {
                case 0:
                    goDown();
                    break;
                case 1:
                    goRight();
                    break;
                default:
                    break;
                }
                break;
            case 4:
                switch (random)
                {
                case 0:
                    goUp();
                    break;
                case 1:
                    goRight();
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            break;
        case 4:
            switch (y)
            {
            case 1:
                switch (random)
                {
                case 0:
                    goDown();
                    break;
                case 1:
                    goLeft();
                    break;
                default:
                    break;
                }
                break;
            case 4:
                switch (random)
                {
                case 0:
                    goUp();
                    break;
                case 1:
                    goLeft();
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    else if (x == 0 || y == 0 || x == 5 || y == 5)
    {
        switch(x)
        {
        case 0:
            switch (y)
            {
            case 2:
                jump(jump1);
                break;
            case 3:
                jump(jump2);
                break;
            default:
                break;
            }
            break;
        case 2:
            switch (y)
            {
            case 0:
                jump(jump8);
                break;
            case 5:
                jump(jump3);
                break;
            default:
                break;
            }
            break;
        case 3:
            switch (y)
            {
            case 0:
                jump(jump7);
                break;
            case 5:
                jump(jump4);
                break;
            default:
                break;
            }
            break;
        case 5:
            switch (y)
            {
            case 2:
                jump(jump5);
                break;
            case 3:
                jump(jump6);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    else
    {
        random = rand() % 4;
        switch (random)
        {
        case 0:
            goUp();
            break;
        case 1:
            goDown();
            break;
        case 2:
            goLeft();
            break;
        case 3:
            goRight();
            break;
        default:
            break;
        }
    }
}
#endif // NOTES_H_INCLUDED
