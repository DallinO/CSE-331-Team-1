#include "logic.h"
#include "uiInteract.h"
#include "enums.h"
#include "storage.h"

using namespace std;

double random(double min, double max)
{
	assert(min <= max);
	double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
	assert(min <= num && num <= max);
	return num;
}

double randomFloat(double min, double max)
{
    assert(min <= max);
    double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
    assert(min <= num && num <= max);
    return num;
}

void Logic::interact(const UserInput& ui)
{
    // reset the game
    Storage* storage = getStorage();
    TimeStorage* time = storage->getTime();
    Score* score = storage->getScore();
    HitRatio* hitRatio = storage->getHitRatio();
    GunStorage* gun = storage->getGun();
    list<BulletStorage>* bullets = storage->getBullets();
    if (timeLogic.isGameOver(time) && ui.isSpace())
    {
        timeLogic.reset(time);
        score->reset();
        hitRatio->reset();
        return;
    }

    // gather input from the interface
    gunLogic.interact(gun, ui.isUp() + ui.isRight(), ui.isDown() + ui.isLeft());
    BulletStorage* p = nullptr;

    // a pellet can be shot at any time
    if (ui.isSpace())
        p = new BulletStorage(Pellet, gun->getAngle());
    // missiles can be shot at level 2 and higher
    else if (ui.isM() && time->getLevelNumber() > 1)
        p = new BulletStorage(Missle, gun->getAngle());
    // bombs can be shot at level 3 and higher
    else if (ui.isB() && time->getLevelNumber() > 2)
        p = new BulletStorage(Bomb, gun->getAngle());

    // add something if something has been added
    if (nullptr != p)
    {
        bullets->push_back(*p);
        score->adjust(0 - p->getPoints());
    }

    // send movement information to all the bullets. Only the missile cares.
    for (auto& bullet : *bullets)
        missleLogic.input(&bullet, ui.isUp() + ui.isRight(), ui.isDown() + ui.isLeft(), ui.isB());
}

void Logic::animate()
{
    Storage* storage = getStorage();
    TimeStorage* time = storage->getTime();
    Score* score = storage->getScore();
    HitRatio* hitRatio = storage->getHitRatio();
    list<BulletStorage>* bullets = storage->getBullets();
    list<BirdStorage>* birds = storage->getBirds();
    list<StorageEffect>* effects = storage->getEffects();
    time++;

    // if status, then do not move the game
    if (getTimeLogic().isStatus(time))
    {
        // get rid of the bullets and the birds without changing the score
        birds->clear();
        bullets->clear();
        effects->clear();
        return;
    }

    spawn(storage, time, birds);
    advance(storage, birds, bullets, effects);
    hitDetection(hitRatio, birds, bullets, effects);
    cleanUp(score, birds, bullets, effects);

}

void Logic::spawn(Storage* storage, TimeStorage* time, list<BirdStorage>* birds)
{
    double size;
    switch (time->getLevelNumber())
    {
        // in level 1 spawn big birds occasionally
    case 1:
        size = 30.0;
        // spawns when there is nothing on the screen
        if (birds->size() == 0 && random(0, 15) == 1)
            birds->push_back(BirdStorage(Standard, size, 7.0, 10, randomFloat(storage->getDimensions().getY() * 0.25, storage->getDimensions().getY() * 0.75)));

        // spawn every 4 seconds
        if (random(0, 4 * 30) == 1)
            birds->push_back(BirdStorage(Standard, size, 7.0, 10, randomFloat(storage->getDimensions().getY() * 0.25, storage->getDimensions().getY() * 0.75)));
        break;

        // two kinds of birds in level 2
    case 2:
        size = 25.0;
        // spawns when there is nothing on the screen
        if (birds->size() == 0 && random(0, 15) == 1)
            birds->push_back(BirdStorage(Standard, size, 7.0, 12, randomFloat(storage->getDimensions().getY() * 0.25, storage->getDimensions().getY() * 0.75)));

        // spawn every 4 seconds
        if (random(0, 4 * 30) == 1)
            birds->push_back(BirdStorage(Standard, size, 5.0, 12, randomFloat(storage->getDimensions().getY() * 0.25, storage->getDimensions().getY() * 0.75)));
        // spawn every 3 seconds
        if (random(0, 3 * 30) == 1)
            birds->push_back(BirdStorage(Sinker, size, 4.5, 20, randomFloat(storage->getDimensions().getY() * 0.50, storage->getDimensions().getY() * 0.95)));
        break;

        // three kinds of birds in level 3
    case 3:
        size = 20.0;
        // spawns when there is nothing on the screen
        if (birds->size() == 0 && random(0, 15) == 1)
            birds->push_back(BirdStorage(Standard, size, 5.0, 15, randomFloat(storage->getDimensions().getY() * 0.25, storage->getDimensions().getY() * 0.75)));

        // spawn every 4 seconds
        if (random(0, 4 * 30) == 1)
            birds->push_back(BirdStorage(Standard, size, 5.0, 15, randomFloat(storage->getDimensions().getY() * 0.25, storage->getDimensions().getY() * 0.75)));
        // spawn every 4 seconds
        if (random(0, 4 * 30) == 1)
            birds->push_back(BirdStorage(Sinker, size, 4.5, 22, randomFloat(storage->getDimensions().getY() * 0.50, storage->getDimensions().getY() * 0.95)));
        // spawn every 4 seconds
        if (random(0, 4 * 30) == 1)
            birds->push_back(BirdStorage(Floater, size, 5.0, 15, randomFloat(storage->getDimensions().getY() * 0.01, storage->getDimensions().getY() * 0.50)));
        break;

        // three kinds of birds in level 4
    case 4:
        size = 15.0;
        // spawns when there is nothing on the screen
        if (birds->size() == 0 && random(0, 15) == 1)
            birds->push_back(BirdStorage(Standard, size, 4.0, 18, randomFloat(storage->getDimensions().getY() * 0.25, storage->getDimensions().getY() * 0.75)));

        // spawn every 4 seconds
        if (random(0, 4 * 30) == 1)
            birds->push_back(BirdStorage(Standard, size, 4.0, 18, randomFloat(storage->getDimensions().getY() * 0.25, storage->getDimensions().getY() * 0.75)));
        // spawn every 4 seconds
        if (random(0, 4 * 30) == 1)
            birds->push_back(BirdStorage(Sinker, size, 3.5, 25, randomFloat(storage->getDimensions().getY() * 0.50, storage->getDimensions().getY() * 0.95)));
        // spawn every 4 seconds
        if (random(0, 4 * 30) == 1)
            birds->push_back(BirdStorage(Floater, size, 4.0, 25, randomFloat(storage->getDimensions().getY() * 0.01, storage->getDimensions().getY() * 0.50)));
        // spawn every 4 seconds
        if (random(0, 4 * 30) == 1)
            birds->push_back(BirdStorage(Crazy, size, 4.5, 30, randomFloat(storage->getDimensions().getY() * 0.25, storage->getDimensions().getY() * 0.75)));
        break;

    default:
        break;
    }
}

void Logic::advance(Storage* storage, list<BirdStorage>* birds, list<BulletStorage>* bullets, list<StorageEffect>* effects)
{
    for (auto& bird : *birds)
    {
        switch (bird.getType())
        {
            case Standard:
                standardlogic.advance(&bird);
                break;
            case Sinker:
                sinkerLogic.advance(&bird);
                break;
            case Floater:
                floaterLogic.advance(&bird);
                break;
            case Crazy:
                crazyLogic.advance(&bird);
                break;
        }
        storage->getHitRatio()->adjust(bird.isDead() ? -1 : 0);
    }
    for (auto& bullet : *bullets)
    {
        switch (bullet.getType())
        {
        case Bomb:
            bombLogic.move(&bullet, effects);
            break;
        case Shrapnel:
            shrapnelLogic.move(&bullet, effects);
            break;
        case Missle:
            missleLogic.move(&bullet, effects);
            break;
        }
    }
    for (auto& effect : *effects)
    {
        switch (effect.getType())
        {
            case Fragment:
                fragmentLogic.fly(&effect);
                break;
            case Streek:
                streekLogic.fly(&effect);
                break;
            case Exaust:
                exhaustLogic.fly(&effect);
        }
    }
}

void Logic::hitDetection(HitRatio* hitRatio, list<BirdStorage>* birds, list<BulletStorage>* bullets, list<StorageEffect>* effects)
{
    for (auto &element : *birds)
        for (auto &bullet : *bullets)
            if (!element.isDead() && !bullet.isDead() &&
                element.getRadius() + bullet.getRadius() >
                minimumDistance(element.getPoint(), element.getVelocity(),
                    bullet.getPoint(), bullet.getVelocity()))
            {
                for (int i = 0; i < 25; i++)
                    effects->push_back(StorageEffect(Fragment, bullet.getPoint(), bullet.getVelocity()));
                element.kill();
                bullet.kill();
                hitRatio->adjust(1);
            }
}

void Logic::cleanUp(Score* score, list<BirdStorage>* birds, list<BulletStorage>* bullets, list<StorageEffect>* effects)
{
    for (auto it = birds->begin(); it != birds->end();)
        if ((it)->isDead())
        {
            score->adjust((it)->getPoints());
            it = birds->erase(it);
        }
        else
            ++it;

    for (auto it = bullets->begin(); it != bullets->end(); )
    {
        if ((it)->isDead())
        {
            if ((*it).getType() == Bomb)
            {
                bombLogic.death(&(*it), bullets);
            }
            
            it = bullets->erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = effects->begin(); it != effects->end();)
        if (effectLogic.isDead(&(*it)))
            it = effects->erase(it);
        else
            ++it;
}