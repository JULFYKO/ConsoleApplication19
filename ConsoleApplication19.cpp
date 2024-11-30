#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Shooter {
protected:
    string ammoType;
    int ammoCount;

public:
    void loadAmmo(const string& type, int count) {
        ammoType = type;
        ammoCount = count;
    }

    virtual ~Shooter() = default;

    virtual void fire() {
        if (ammoCount > 0) {
            ammoCount--;
            cout << "Shot: " << ammoType << endl;
        }
        else {
            cout << "Out of ammo!" << endl;
        }
    }
};

class Archer : public Shooter {
public:
    void fire() override {
        if (ammoCount > 0) {
            ammoCount--;
            cout << "Archer fires an arrow: " << ammoType << endl;
        }
        else {
            cout << "Archer has no arrows left!" << endl;
        }
    }
};

class Ranger : public Shooter {
public:
    void fire() override {
        if (ammoCount > 0) {
            ammoCount--;
            cout << "Ranger fires an arrow: " << ammoType << endl;
        }
        else {
            cout << "Ranger has no arrows left!" << endl;
        }
    }
};

class AmmoProvider {
public:
    virtual void setAmmo(const string& type, int count) = 0;
    virtual ~AmmoProvider() = default;
};

class ArcherTower : public Archer, public AmmoProvider {
protected:
    Ranger ranger;

public:
    void setAmmo(const string& type, int count) override {
        Archer::loadAmmo(type, count);
        ranger.loadAmmo(type, count);
    }

    void archerFire() {
        Archer::fire();
    }

    void rangerFire() {
        ranger.fire();
    }
};

class Catapult : public Shooter {
public:
    void fire() override {
        if (ammoCount > 0) {
            ammoCount--;
            cout << "Catapult launches a rock: " << ammoType << endl;
        }
        else {
            cout << "Catapult is out of rocks!" << endl;
        }
    }
};

class Fortress final : public ArcherTower {
private:
    int wallHealth;
    int gateHealth;
    int soldierCount;
    Catapult catapult;

public:
    Fortress(int wall, int soldiers)
        : wallHealth(wall),
        gateHealth(100),
        soldierCount(soldiers) {
        setAmmo("Arrow", 4);
        catapult.loadAmmo("Rock", 3);
    }

    void damageGate(int damage) {
        gateHealth = std::max(0, gateHealth - damage);
        cout << "Gate health: " << gateHealth << "%" << endl;
    }

    void repairWall(int repair) {
        wallHealth += repair;
        cout << "Wall health increased to: " << wallHealth << endl;
    }

    void archerAttack() {
        archerFire();
    }

    void rangerAttack() {
        rangerFire();
    }

    void catapultAttack() {
        catapult.fire();
    }

    int getWallHealth() const { return wallHealth; }
    int getGateHealth() const { return gateHealth; }
    int getSoldierCount() const { return soldierCount; }
};

int main() {
    Fortress fortress(500, 50);

    cout << "Archer attack:" << endl;
    fortress.archerAttack();
    fortress.archerAttack();
    fortress.archerAttack();

    cout << "\nRanger attack:" << endl;
    fortress.rangerAttack();
    fortress.rangerAttack();

    cout << "\nCatapult attack:" << endl;
    fortress.catapultAttack();
    fortress.catapultAttack();
    fortress.catapultAttack();

    fortress.damageGate(20);
    fortress.repairWall(50);

    cout << "\nFortress Status:" << endl;
    cout << "Wall Health: " << fortress.getWallHealth() << endl;
    cout << "Gate Health: " << fortress.getGateHealth() << "%" << endl;
    cout << "Soldier Count: " << fortress.getSoldierCount() << endl;

    return 0;
}
