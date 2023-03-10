#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

#include "VRAM.h"

short VRAM[128][128];
int COLORS[16] = {0xFFFFFFFF, 0xFFFF00FF, 0xFF00FFFF, 0xFF0000FF, 0xC0C0C0FF, 0x808080FF, 0x808000FF, 0x800080FF, 0x800000FF, 0x00FFFFFF, 0x00FF00FF, 0x008080FF, 0x008000FF, 0x0000FFFF, 0x000080FF, 0x000000FF};

void ClearVRAM() {
    for (short x = 0; x < 128; x++) {
        for (short y = 0; y < 128; y++) {
            VRAM[x][y] = 0;
        }
    }
}
void SaveVRAM() {
    sf::Image image;
    image.create(128, 128);
    for (short x = 0; x < 128; x++) {
        for (short y = 0; y < 128; y++) {
            image.setPixel(x, y, sf::Color(COLORS[VRAM[x][y]]));
        }
    }
    image.saveToFile("VRAM.png");
}
void SetPixel(short x, short y, short color) {
    if (x < 128 && y < 128 && x >= 0 && y >= 0) {
        if (color <= 16 && color >= 0) {
            VRAM[x][y] = color;
        } else {
            std::cout << "Error: Color out of bounds" << std::endl;
        }
    } else {
        std::cout << "Error: Pixel out of bounds" << std::endl;
    }
}
short GetPixel(short x, short y) {
    if (x < 128 && y < 128 && x >= 0 && y >= 0) {
        return VRAM[x][y];
    } else {
        std::cout << "Error: Pixel out of bounds" << std::endl;
    }
    return 0;
}
void SetPixels(short posX, short posY, short width, short height, short color) {
    for (short y = 0; y < width; y++) {
        for (short x = 0; x < height; x++) {
            if (posX + x < 128 && posY + y < 128 && x >= 0 && y >= 0) {
                if (color <= 16 && color >= 0) {
                    VRAM[posX + x][posY + y] = color;
                } else {
                    std::cout << "Error: Color out of bounds" << std::endl;
                }
            } else {
                std::cout << "Error: Pixel out of bounds" << std::endl;
            }
        }
    }
}
void SetSprite(short posX, short posY, short** sprite) {
    for (short y = 0; y < 16; y++) {
        for (short x = 0; x < 16; x++) {
            if (posX + x < 128 && posY + y < 128 && x >= 0 && y >= 0) {
                if (sprite[y][x] >= 16) {
                    VRAM[posY + y][posX + x] = sprite[y][x];
                } else {
                    std::cout << "Error: Color out of bounds" << std::endl;
                }
            } else {
                std::cout << "Error: Pixel out of bounds" << std::endl;
            }
        }
    }
}
void WriteText(std::string text, short posX, short posY, int scale, int color) {
    int height = 24;
    int width = 24;
    std::string characters = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    sf::Image image;
    if (!image.loadFromFile("font.png")) {
        std::cout << "Error: Could not load image" << std::endl;
    }

    for (short i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            posX += width;
        } else {
            for (short y = 0; y < height; y++) {
                for (short x = 0; x < width; x++) {
                    if (text[i] >= 0 && text[i] <= 95) {
                        SetPixel((posX + x) / scale, (posY + y) / scale, image.getPixel((characters.find(text[i])) * width + x, y).r / 16);
                    }
                }
            }
            posX += width;
        }
    }
}
void DrawColorPallete() {
    int addX = 25;

    WriteText("00", 0, 0, 2, 0);
    SetPixels(addX + 0, 0, 11, 11, 0);
    SetPixels(addX + 10, 0, 11, 11, 4);
    WriteText("04", (addX * 2) + (12 * 4), 0, 2, 0);

    WriteText("09", 0, 25, 2, 0);
    SetPixels(addX + 0, 12, 11, 11, 9);
    SetPixels(addX + 10, 12, 11, 11, 11);
    WriteText("11", (addX * 2) + (12 * 4), 25, 2, 0);

    WriteText("01", 0, 50, 2, 0);
    SetPixels(addX + 0, 24, 11, 11, 1);
    SetPixels(addX + 10, 24, 11, 11, 6);
    WriteText("06", (addX * 2) + (12 * 4), 50, 2, 0);

    WriteText("10", 0, 75, 2, 0);
    SetPixels(addX + 0, 37, 11, 11, 10);
    SetPixels(addX + 10, 37, 11, 11, 12);
    WriteText("12", (addX * 2) + (12 * 4), 75, 2, 0);

    WriteText("02", 0, 100, 2, 0);
    SetPixels(addX + 0, 50, 11, 11, 2);
    SetPixels(addX + 10, 50, 11, 11, 7);
    WriteText("07", (addX * 2) + (12 * 4), 100, 2, 0);

    WriteText("03", 0, 125, 2, 0);
    SetPixels(addX + 0, 62, 11, 11, 3);
    SetPixels(addX + 10, 62, 11, 11, 8);
    WriteText("08", (addX * 2) + (12 * 4), 125, 2, 0);

    WriteText("13", 0, 150, 2, 0);
    SetPixels(addX + 0, 75, 11, 11, 13);
    SetPixels(addX + 10, 75, 11, 11, 14);
    WriteText("14", (addX * 2) + (12 * 4), 150, 2, 0);

    WriteText("15", 0, 175, 2, 0);
    SetPixels(addX + 0, 87, 11, 11, 15);
    SetPixels(addX + 10, 87, 11, 11, 5);
    WriteText("05", (addX * 2) + (12 * 4), 175, 2, 0);
}   
void DrawLine(short x1, short y1, short x2, short y2, short color) {
    if (x1 < 0 || x1 > 127 || x2 < 0 || x2 > 127 || y1 < 0 || y1 > 127 || y2 < 0 || y2 > 127) {
        std::cout << "Error: Line out of bounds" << std::endl;
        return;
    }
    if (color < 0 || color > 15) {
        std::cout << "Error: Color out of bounds" << std::endl;
        return;
    }

    short dx = x2 - x1;
    short dy = y2 - y1;
    short steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xinc = dx / (float)steps;
    float yinc = dy / (float)steps;
    float x = x1;
    float y = y1;
    for (short i = 0; i <= steps; i++) {
        SetPixel(round(x), round(y), color);
        x += xinc;
        y += yinc;
    }
}