#include <GL/freeglut.h>
#include "Projectile.h"

Projectile::Projectile(const int damage, const Point &source, const Point &direction) : damage(damage), source(source), direction(direction), position(source) {}

void Projectile::draw() {}
