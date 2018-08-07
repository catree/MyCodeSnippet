#ifndef SOLDIER_H
#define SOLDIER_H

#include <iostream>
#include "Gun.h"

namespace bluefish {

class Soldier {
private:
    AbstractGun* _gun;

public:
    void SetGun(AbstractGun* gun)
    {
        this->_gun = gun;
    }

    void KillEnemy()
    {
        std::cout << "Soldiers are shooting enemy...\n";
        _gun->Shoot();
    }
};

}

#endif