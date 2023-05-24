#include <iostream>
#include <list>
#include "bird.h"
#include <time.h>
#include "bullet.h"
#include "score.h"

using namespace std;

class Command
{
protected:
    Time time;
    Command* next;

public:
    Command(Time& time) : next(nullptr) { this->time = time; }

    virtual ~Command() {}
    virtual void execute(list<Bird*>& birds, list<Bullet*>& bullets, list<Effect*>& effects, HitRatio& hitRatio, Score& score) = 0;

    void setNext(Command* command)
    {
        next = command;
    }
};

class Clear : public Command
{
public:
    Clear(Time& time) : Command(time) {}

    void execute(list<Bird*>& birds, list<Bullet*>& bullets, list<Effect*>& effects, HitRatio& hitRatio, Score& score) override
    {
        for (auto it = birds.begin(); it != birds.end();)
        {
            if ((*it)->isDead())
            {
                score.adjust((*it)->getPoints());
                it = birds.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto it = bullets.begin(); it != bullets.end(); )
        {
            if ((*it)->isDead())
            {
                (*it)->death(bullets);
                it = bullets.erase(it);
            }
            else
            {
                ++it;
            }
        }

        for (auto it = effects.begin(); it != effects.end();)
        {
            if ((*it)->isDead())
            {
                it = effects.erase(it);
            }
            else
            {
                ++it;
            }
        }
        if (next != nullptr)
        {
            next->execute(birds, bullets, effects, hitRatio, score);
        }
    }
};

int RandomGen(int min, int max)
{
    assert(min < max);
    int num = (rand() % (max - min)) + min;
    assert(min <= num && num <= max);

    return num;
}

class Spawn : public Command
{
public:
    Spawn(Time& time) : Command(time) {}

    void execute(list<Bird*>& birds, list<Bullet*>& bullets, list<Effect*>& effects, HitRatio& hitRatio, Score& score) override
    {
        double size = 0.0;
        int level = time.level();

        if (birds.size() == 0 && RandomGen(0, 15) == 1)
        {
            switch (level)
            {
            case 1:
                size = 30.0;
                birds.push_back(new Standard(size, 7.0));
                break;
            case 2:
                size = 25.0;
                birds.push_back(new Standard(size, 7.0, 12));
                break;
            case 3:
                size = 20.0;
                birds.push_back(new Standard(size, 5.0, 15));
                break;
            case 4:
                size = 15.0;
                birds.push_back(new Standard(size, 4.0, 18));
                break;
            default:
                break;
            }
        }

        switch (level)
        {
        case 1:
            if (RandomGen(0, 4 * 30) == 1)
                birds.push_back(new Standard(size, 7.0));
            break;
        case 2:
            if (RandomGen(0, 4 * 30) == 1)
                birds.push_back(new Standard(size, 5.0, 12));
            if (RandomGen(0, 3 * 30) == 1)
                birds.push_back(new Sinker(size));
            break;
        case 3:
            if (RandomGen(0, 4 * 30) == 1)
                birds.push_back(new Standard(size, 5.0, 15));
            if (RandomGen(0, 4 * 30) == 1)
                birds.push_back(new Sinker(size, 4.0, 22));
            if (RandomGen(0, 4 * 30) == 1)
                birds.push_back(new Floater(size));
            break;
        case 4:
            if (RandomGen(0, 4 * 30) == 1)
                birds.push_back(new Standard(size, 4.0, 18));
            if (RandomGen(0, 4 * 30) == 1)
                birds.push_back(new Sinker(size, 3.5, 25));
            if (RandomGen(0, 4 * 30) == 1)
                birds.push_back(new Floater(size, 4.0, 25));
            if (RandomGen(0, 4 * 30) == 1)
                birds.push_back(new Crazy(size));
            break;
        default:
            break;
        }

        if (next != nullptr)
        {
            next->execute(birds, bullets, effects, hitRatio, score);
        }
    }

};

class MoveBirds : public Command
{
public:
    MoveBirds(Time& time) : Command(time) {}

    void execute(list<Bird*>& birds, list<Bullet*>& bullets, list<Effect*>& effects, HitRatio& hitRatio, Score& score) override
    {
        for (auto element : birds)
        {
            element->advance();
            hitRatio.adjust(element->isDead() ? -1 : 0);
        }

        for (auto bullet : bullets)
        {
            bullet->move(effects);
        }

        for (auto effect : effects)
        {
            effect->fly();
        }

        if (next != nullptr)
        {
            next->execute(birds, bullets, effects, hitRatio, score);
        }
    }
};

class HitDetection : public Command
{
public:
    HitDetection(Time& time) : Command(time) {}

    void execute(list<Bird*>& birds, list<Bullet*>& bullets, list<Effect*>& effects, HitRatio& hitRatio, Score& score) override
    {
        for (auto element : birds)
        {
            for (auto bullet : bullets)
            {
                if (!element->isDead() && !bullet->isDead() &&
                    element->getRadius() + bullet->getRadius() > minimumDistance(element->getPosition(), element->getVelocity(),
                        bullet->getPosition(), bullet->getVelocity()))
                {
                    for (int i = 0; i < 25; i++)
                    {
                        effects.push_back(new Fragment(bullet->getPosition(), bullet->getVelocity()));
                    }
                    element->kill();
                    bullet->kill();
                    hitRatio.adjust(1);
                }
            }
        }

        if (next != nullptr)
        {
            next->execute(birds, bullets, effects, hitRatio, score);
        }
    }
};