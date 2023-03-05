#include "speedtest.h"
#include "colors.cpp"
#include <QColor>
#include <QDebug>
#include <stdlib.h>
#include <time.h>
#include <cmath>


const int INITIAL_INTERVAL = 2000;
const int NO_VALUE = -1;


SpeedTest::SpeedTest(QObject *parent)
    : QObject(parent)
    , mColor_red(red_idle)
    , mColor_blue(blue_idle)
    , mColor_orange(orange_idle)
    , mColor_yellow(yellow_idle)
    , mGameEnded(true)
    , numbers()
    , next (NO_VALUE)
    , mCount (0)
    , lastPressed (NO_VALUE)



{

    // initiate timer

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->setTimerType(Qt::PreciseTimer);

    // seed for random numbers

    srand(time(NULL));

}

int SpeedTest::count() {
    return mCount;
}

QColor SpeedTest::color_red() {
    return mColor_red;
}

QColor SpeedTest::color_blue() {
    return mColor_blue;
}

QColor SpeedTest::color_orange() {
    return mColor_orange;
}

QColor SpeedTest::color_yellow() {
    return mColor_yellow;
}

void SpeedTest::setCount(int newcount) {
    mCount = newcount;
    emit countChanged();
}

/*

  Sets gameEnded status and stops timer if game ended.

*/

void SpeedTest::setGameEnded(bool status) {
    mGameEnded = status;
    if (status) {
        timer->stop();
    }
}

void SpeedTest::setColor_red(QColor newcolor)
{
    if (mColor_red != newcolor) {
        mColor_red = newcolor;
        emit color_redChanged();
    }
}

void SpeedTest::setColor_blue(QColor newcolor)
{
    if (mColor_blue != newcolor) {
        mColor_blue = newcolor;
        emit color_blueChanged();
    }
}

void SpeedTest::setColor_orange(QColor newcolor)
{
    if (mColor_orange != newcolor) {
        mColor_orange = newcolor;
        emit color_orangeChanged();
    }
}

void SpeedTest::setColor_yellow(QColor newcolor)
{
    if (mColor_yellow != newcolor) {
        mColor_yellow = newcolor;
        emit color_yellowChanged();
    }
}

void SpeedTest::buttonPressed(int index) {
    if (!mGameEnded) {

        // ignore when user presses same button multiple times

        if (lastPressed == index) {
            return;
        }

        // end game when user presses button when queue is empty

        if (numbers.empty()) {
            setGameEnded(true);
            activateAll();
            return;
        }

        // end game when user presses wrong button

        int target = numbers.front();
        if (target != index) {
            setGameEnded(true);
            if (target == 0 || index == 0) {
                setColor_red(red_activated);
            } else {
                setColor_red(red_idle);
            }
            if (target == 1 || index == 1) {
                setColor_blue(blue_activated);
            } else {
                setColor_blue(blue_idle);
            }
            if (target == 2 || index == 2) {
                setColor_orange(orange_activated);
            } else {
                setColor_orange(orange_idle);
            }
            if (target == 3 || index == 3) {
                setColor_yellow(yellow_activated);
            } else {
                setColor_yellow(yellow_idle);
            }
            return;
        }

        // user presses right button

        numbers.pop();
        setCount(++mCount);
        timer->setInterval(1200 - 200 * log(mCount));
        lastPressed = index;      
    }

}

void SpeedTest::setColors (int next) {

    idleAll();

    switch (next) {
    case 0:
        setColor_red(red_activated);
        break;
    case 1:
        setColor_blue(blue_activated);
        break;
    case 2:
        setColor_orange(orange_activated);
        break;
    case 3:
        setColor_yellow(yellow_activated);
        break;

    }
}

void SpeedTest::activateAll () {
    setColor_red(red_activated);
    setColor_blue(blue_activated);
    setColor_orange(orange_activated);
    setColor_yellow(yellow_activated);
}

void SpeedTest::idleAll() {
    setColor_red(red_idle);
    setColor_blue(blue_idle);
    setColor_orange(orange_idle);
    setColor_yellow(yellow_idle);
}

void SpeedTest::clearQueue () {
    while (!numbers.empty()) {
        numbers.pop();
    }
}

/*

  Timer activates this function

*/

void SpeedTest::tick() {
    if (!mGameEnded) {
         numbers.push(next);

         // end game if user has not responded to 10 flashes

         if (numbers.size() > 9) {
             setGameEnded(true);
             activateAll();
             return;
         }

         setColors(next);
         next = (next + (rand() % 3) + 1) % 4;
         qDebug() << timer->interval();
     }    
}

void SpeedTest::startGame() {

    setGameEnded(!mGameEnded);    
    idleAll();
    lastPressed = NO_VALUE;    
    clearQueue();

    if (!mGameEnded) {
        setCount(0);
        timer->start(INITIAL_INTERVAL);
        next = rand() % 4;
        tick();
     }
}



