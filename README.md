# My_Radar 

## Description
**My_Radar** is a project made in C, with a Makefile for building. It is a 2D visualization panel simulating air traffic.
For this project, I was allowed to use theses functions : 

    ✓ malloc
    ✓ free
    ✓ stat
    ✓ memset
    ✓ rand
    ✓ srand
    ✓ time (only with srand)
    ✓ (f)open
    ✓ (f)read
    ✓ (f)write
    ✓ (f)close
    ✓ getline

And these CSFML lib functions:
    
    ✓ sfRenderWindow_create
    ✓ sfRenderWindow_destroy
    ✓ sfRenderWindow_isOpen
    ✓ sfRenderWindow_close
    ✓ sfRenderWindow_pollEvent
    ✓ sfRenderWindow_setFramerateLimit
    ✓ sfRenderWindow_clear
    ✓ sfRenderWindow_drawSprite
    ✓ sfRenderWindow_draw*Shape
    ✓ sfRenderWindow_drawText
    ✓ sfRenderWindow_display
    ✓ sfMusic_*
    ✓ sfSprite_create
    ✓ sfSprite_destroy
    ✓ sfSprite_setTexture
    ✓ sfSprite_setPosition
    ✓ sfSprite_setRotation
    ✓ sfSprite_move
    ✓ sfSprite_rotate
    ✓ sfTexture_create
    ✓ sfTexture_createFromFile
    ✓ sfTexture_destroy
    ✓ sfTexture_updateFromPixels
    ✓ sfText_*
    ✓ sfView_*
    ✓ sfShape_* (except _getLocalBounds and _getGlobalBounds)
    ✓ sfConvexShape_* (except _getLocalBounds and _getGlobalBounds)
    ✓ sfRectangleShape_* (except _getLocalBounds and _getGlobalBounds)
    ✓ sfCircleShape_* (except _getLocalBounds and _getGlobalBounds)
    ✓ sfTransform_*
    ✓ sfClock_*

## Features

    - Pause (space)
    - disable sprite (s)
    - disable hitbox (l)

## Installatio
To install the project, clone the repository and use the Makefile to build the project :

    > git clone https://github.com/ThePepidev/My_Radar.git
    > cd My_Radar
    > make

## Utilisation

To use this projects you have to execute it with the path of a valid text file. Here is an example :

    ./my_radar [text file path]

And here is an exemple of a valid text file :

    A 1020 830 1070 290 99 3
    A 820 490 1070 290 87 4
    A 1020 830 690 640 91 4
    A 1090 580 820 490 100 5
    A 1160 750 1070 290 78 5
    A 1090 580 1020 830 100 6
    T 820 490 81
    T 1160 750 34
    T 880 330 70

After the 'A' letter, you have to put **the coordonate x and y for the plane spawn**, **the coordonate (x, y) of the plane arrival**, **the speed of the plane** and **the delay of the spawn**.
After the 'T' letter, you have to put **the coordonate x and y for the tower spawn** and **the radius of the tower hitbox circle**.
