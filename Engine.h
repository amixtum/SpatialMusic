#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "Notes.h"

using namespace std;
using namespace sf;

const int TILES = 24;
const int SPACES = 6;

/*
 *Contains numberic data for the construction of the window
 *and tiles
 */
struct EngineData
{
    float w_width;
    float w_height;
    float x_coordinates[TILES];
    float y_coordinates[TILES];
    float coordinate_index[SPACES];
    string w_name;
};

/*
 * Contains NoteTile and Tile arrays
 * NOTE: t_array may not be needed anymore
 */
struct TileData
{
    NoteTile tile_array[TILES];
    Tile t_array[TILES];
};

/*
 * Creates the grid of NoteTiles and allows the entity to interact with it
 * Uses SFML to display the images and play the sounds
 */
class Engine
{
public:
    //Sets the basic e_data values
    //calls setTileCoordinates
    Engine(string);
    
    //Runs the main operation of this program
    void Init();
protected:

    
    void setTileCoordinates();
    bool isOnTile(Vector2f,Vector2f);
    EngineData e_data;
    TileData t_data;
};

Engine::Engine(string w_Name)
{
    e_data.w_width = 600;
    e_data.w_height = 600;
    e_data.w_name = w_Name;
    int c = 0;
    for (int g = 0; g < SPACES; ++g)
    {
        e_data.coordinate_index[g] = c;
        c += 100;
    }
    setTileCoordinates();
}

void Engine::setTileCoordinates()
{
    bool rows[6];
    rows[0] = true;
    int i = 0;
    int r = 0;
    while (i < TILES)
    {
        if (rows[r])
        {
            e_data.x_coordinates[i] = e_data.coordinate_index[2];
            e_data.y_coordinates[i] = e_data.coordinate_index[0];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[3];
            e_data.y_coordinates[i] = e_data.coordinate_index[0];
            i++;
            rows[r] = false;
            r++;
            rows[r] = true;
        }
        if (rows[r])
        {
            e_data.x_coordinates[i] = e_data.coordinate_index[1];
            e_data.y_coordinates[i] = e_data.coordinate_index[1];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[2];
            e_data.y_coordinates[i] = e_data.coordinate_index[1];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[3];
            e_data.y_coordinates[i] = e_data.coordinate_index[1];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[4];
            e_data.y_coordinates[i] = e_data.coordinate_index[1];
            i++;
            rows[r] = false;
            r++;
            rows[r] = true;
        }
        if (rows[r])
        {
            e_data.x_coordinates[i] = e_data.coordinate_index[0];
            e_data.y_coordinates[i] = e_data.coordinate_index[2];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[1];
            e_data.y_coordinates[i] = e_data.coordinate_index[2];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[2];
            e_data.y_coordinates[i] = e_data.coordinate_index[2];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[3];
            e_data.y_coordinates[i] = e_data.coordinate_index[2];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[4];
            e_data.y_coordinates[i] = e_data.coordinate_index[2];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[5];
            e_data.y_coordinates[i] = e_data.coordinate_index[2];
            i++;
            rows[r] = false;
            r++;
            rows[r] = true;
        }
        if (rows[r])
        {
            e_data.x_coordinates[i] = e_data.coordinate_index[0];
            e_data.y_coordinates[i] = e_data.coordinate_index[3];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[1];
            e_data.y_coordinates[i] = e_data.coordinate_index[3];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[2];
            e_data.y_coordinates[i] = e_data.coordinate_index[3];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[3];
            e_data.y_coordinates[i] = e_data.coordinate_index[3];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[4];
            e_data.y_coordinates[i] = e_data.coordinate_index[3];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[5];
            e_data.y_coordinates[i] = e_data.coordinate_index[3];
            i++;
            rows[r] = false;
            r++;
            rows[r] = true;
        }
        if (rows[r])
        {
            e_data.x_coordinates[i] = e_data.coordinate_index[1];
            e_data.y_coordinates[i] = e_data.coordinate_index[4];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[2];
            e_data.y_coordinates[i] = e_data.coordinate_index[4];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[3];
            e_data.y_coordinates[i] = e_data.coordinate_index[4];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[4];
            e_data.y_coordinates[i] = e_data.coordinate_index[4];
            i++;
            rows[r] = false;
            r++;
            rows[r] = true;
        }
        if (rows[r])
        {
            e_data.x_coordinates[i] = e_data.coordinate_index[2];
            e_data.y_coordinates[i] = e_data.coordinate_index[5];
            i++;
            e_data.x_coordinates[i] = e_data.coordinate_index[3];
            e_data.y_coordinates[i] = e_data.coordinate_index[5];
            i++;
            rows[r] = false;
        }
    }
    int quality_array[]=   {11,8,
                          4,6,2,9,
                        11,8,7,5,10,12,
                        6,5,9,7,3,12,
                         10,2,1,4,
                            1,3};

    for (int j = 0; j < TILES; ++j)
    {
        t_data.t_array[j].load(e_data.x_coordinates[j],e_data.y_coordinates[j],quality_array[j]);
        t_data.tile_array[j].load(e_data.x_coordinates[j],e_data.y_coordinates[j],(rand()%2)+1,quality_array[j]);
    }
}
bool Engine::isOnTile(Vector2f tile_position, Vector2f entity_position)
{
    if ((tile_position.x != entity_position.x)||(tile_position.y != entity_position.y))
        return false;
    return true;
}
void Engine::Init()
{
    RenderWindow window(VideoMode(e_data.w_width,e_data.w_height),e_data.w_name);
    Entity entity;
    bool start = false;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                entity.goLeft();
                for (int a = 0; a < TILES; ++a)
                {
                    if (isOnTile(t_data.tile_array[a].getP(),entity.getP()))
                        t_data.tile_array[a].Play();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                entity.goRight();
                for (int a = 0; a < TILES; ++a)
                {
                    if (isOnTile(t_data.tile_array[a].getP(),entity.getP()))
                        t_data.tile_array[a].Play();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                entity.goUp();
                for (int a = 0; a < TILES; ++a)
                {
                    if (isOnTile(t_data.tile_array[a].getP(),entity.getP()))
                        t_data.tile_array[a].Play();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                entity.goDown();
                for (int a = 0; a < TILES; ++a)
                {
                    if (isOnTile(t_data.tile_array[a].getP(),entity.getP()))
                        t_data.tile_array[a].Play();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                start = true;
            }
        }
        if (start)
        {
            entity.automate();
            for (int a = 0; a < TILES; ++a)
            {
                if (isOnTile(t_data.tile_array[a].getP(),entity.getP()))
                    t_data.tile_array[a].Play();
            }
        }
        window.clear();
        for (int g = 0; g < TILES; ++g)
        {
            window.draw(t_data.tile_array[g]);
        }
        window.draw(entity.s_entity);
        window.display();
    }
}

#endif // ENGINE_H_INCLUDED
