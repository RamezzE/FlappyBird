#include "Quadtree.h"
QuadTree::QuadTree() {}

QuadTree::QuadTree(Rectangle boundary, int capacity = 4) {
    setData(boundary, capacity);
}

void QuadTree::setData(Rectangle boundary, int capacity)
{
    this->boundary = boundary;
    this->capacity = capacity;
    divided = false;
}

void QuadTree::subdivide() {

    int x1 = this->boundary.x1;
    int y1 = this->boundary.y1;
    int x2 = this->boundary.x2;
    int y2 = this->boundary.y2;

    //setting sides for each rectangle appropriately
    Rectangle ne((x1 + x2) / 2, ((y1 + y2) / 2), x2, y2);
    Rectangle nw(x1, ((y1 + y2) / 2), (x1 + x2) / 2, y2);
    Rectangle se((x1 + x2) / 2, y1, x2, (y1 + y2) / 2);
    Rectangle sw(x1, y1, (x1 + x2) / 2, ((y1 + y2) / 2));

    NE = new QuadTree(ne, capacity); //north east
    NW = new QuadTree(nw, capacity); //north west
    SE = new QuadTree(se, capacity); //south east
    SW = new QuadTree(sw, capacity); //south west

    this->divided = true;
}


void QuadTree::insert(sf::Sprite object) {

    if (search(object)) return;

    if (!boundary.intersects(object)) return; // if object coordinates are out of range of boundary

    if (objects.size() < capacity) { // if there is space inside vector 
        objects.push_back(object);
    }
    else { //if it is over the capacity, it divides itself into subtrees and checks inserts into one of them
        if (!divided) {
            this->subdivide();
        }
        NE->insert(object);
        NW->insert(object);
        SE->insert(object);
        SW->insert(object);
    }
}

inline bool QuadTree::equals(sf::Sprite sprite1, sf::Sprite sprite2)
{
    if (sprite1.getGlobalBounds().left != sprite2.getGlobalBounds().left) return false;
    if (sprite1.getGlobalBounds().width != sprite2.getGlobalBounds().width) return false;
    if (sprite1.getGlobalBounds().top != sprite2.getGlobalBounds().top) return false;
    if (sprite1.getGlobalBounds().height != sprite2.getGlobalBounds().height) return false;
    return true;
}

void QuadTree::query(Rectangle range, vector<sf::Sprite>& objectsFound) {

    if (!boundary.intersects(range)) { //range is not within the QuadTree boundary so returns
        return;
    }
    else {
        for (sf::Sprite r : objects) {
            if (range.intersects(r)) { //adds object to vector if point exists within the range
                bool duplicate = false;
                for (int i = 0; i < objectsFound.size(); i++) {
                    if (equals(r, objectsFound[i])) {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate) {
                    objectsFound.push_back(r);
                }
            }

        }
        if (divided) {   //gets all objects in the sub trees that exist
            NE->query(range, objectsFound);
            NW->query(range, objectsFound);
            SE->query(range, objectsFound);
            SW->query(range, objectsFound);
        }
    }
}

void QuadTree::remove(sf::Sprite object) {
    for (int i = 0; i < objects.size(); i++) {
        if (equals(object, objects[i])) {
            objects.erase(objects.begin() + i);
        }
    }
    if (divided) {
        NE->remove(object);
        NW->remove(object);
        SE->remove(object);
        SW->remove(object);
    }
}

bool QuadTree::search(sf::Sprite object) {
    for (int i = 0; i < objects.size(); i++) {
        if (equals(object, objects[i])) {
            return true;
        }
    }
    if (divided) {
        if (NE->search(object)) return true;
        if (NW->search(object)) return true;
        if (SE->search(object)) return true;
        if (SW->search(object)) return true;
    }
    return false;
}

