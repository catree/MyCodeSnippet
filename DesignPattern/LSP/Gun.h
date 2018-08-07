#ifndef GUN_H
#define GUN_H

#include <iostream>

namespace bluefish {

class AbstractGun
{
public:
    virtual void Shoot() = 0;
};

class HandGun : public AbstractGun
{
public:
    virtual void Shoot()
    {
        std::cout << "Hand Gun Shooting...\n";
    }
};

class Rifle : public AbstractGun
{
public:
    virtual void Shoot()
    {
        std::cout << "Rifle Shooting...\n"; 
    }
};

class MachineGun : public AbstractGun
{
public:
    virtual void Shoot()
    {
        std::cout << "Machine Gun Shooting...\n";
    }
};

} // blufish



#endif