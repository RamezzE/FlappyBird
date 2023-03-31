#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp> 

typedef std::string ObjectType;

class QuadTree {

public:
    class Point {
    public:
        int x;
        int y;
        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }
    };

    class Rectangle {
    public:
        int x1, y1, x2, y2;

        Rectangle() {
            setData(0, 0, 0, 0);
        }
        Rectangle(int x1, int y1, int x2, int y2) {
            setData(x1, y1, x2, y2);
        }

        void setData(int x1, int y1, int x2, int y2) {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;

            if (x1 > x2) {
                int temp = this->x1;
                this->x1 = this->x2;
                this->x2 = temp;
            }
            if (y1 > y2) {
                int temp = this->y1;
                this->y1 = y2;
                this->y2 = temp;
            }
        }

        bool contains(Point point) {

            return (point.x >= x1 && point.x <= x2 && point.y >= y1 && point.y <= y2);

        }

        bool intersects(Rectangle range) {

            return !(x1 > range.x2 || x2 < range.x1 || y1 > range.y1 || y2 < range.y1);

        }
        bool intersects(sf::Sprite object) {
            int X1, X2, Y1, Y2;
            X1 = object.getGlobalBounds().left;
            X2 = object.getGlobalBounds().width + X1;
            Y1 = object.getGlobalBounds().top;
            Y2 = object.getGlobalBounds().height + Y1;

            return  !(x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1);
        }
    };

    QuadTree();

    QuadTree(Rectangle boundary, int capacity);

    void setData(Rectangle boundary, int capacity);

    void subdivide();

    void insert(sf::Sprite object);

    void query(Rectangle range, std::vector<sf::Sprite>& objectsFound);

    void remove(sf::Sprite object);

    bool search(sf::Sprite object);

    bool equals(sf::Sprite sprite1, sf::Sprite sprite2);
private:

    Rectangle boundary; int capacity;
    bool divided;

    std::vector<sf::Sprite> objects; //store points in the tree

    QuadTree* NE; QuadTree* NW; QuadTree* SE; QuadTree* SW;
};