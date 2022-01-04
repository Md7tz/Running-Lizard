#include "GameObjects/lives.h"

Lives::Lives() {
    n_lives = 3;
}
void Lives::decreaseLives() {
    n_lives--;
}

void Lives::reset() {
    n_lives = 3;
}
int Lives::getLives() {
    return n_lives;
}