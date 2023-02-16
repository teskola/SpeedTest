#include "speedtest.h"
#include <QColor>
#include <QDebug>
#include <stdlib.h>
#include <time.h>
#include <QThread>
#include <cmath>


const int INITIAL_INTERVAL = 2000;
const int NO_VALUE = -1;

const QColor red_activated = QColor(255, 0, 0);
const QColor red_idle = QColor(51, 0, 0);

const QColor blue_activated = QColor(0, 0, 255);
const QColor blue_idle = QColor(0, 0, 51);

const QColor orange_activated = QColor(255,128,0);
const QColor orange_idle = QColor(51, 25, 0);

const QColor yellow_activated = QColor(255, 255, 0);
const QColor yellow_idle = QColor(51, 51, 0);

SpeedTest::SpeedTest(QObject *parent)
    : QObject(parent)
    , mColor_red(red_idle)
    , mColor_blue(blue_idle)
    , mColor_orange(orange_idle)
    , mColor_yellow(yellow_idle)
    , mGameEnded(true)
    , numbers()
    , previous (NO_VALUE)
    , next (NO_VALUE)
    , mCount (0)
    , mInterval (INITIAL_INTERVAL)
    , lastPressed (NO_VALUE)

{

}

int SpeedTest::count() {
    return mCount;
}

int SpeedTest::interval() {
    return mInterval;
}


bool SpeedTest::gameEnded() {
    return mGameEnded;
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

void SpeedTest::setInterval(int newinterval) {
    mInterval = newinterval;
    emit intervalChanged();
}

void SpeedTest::setGameEnded(bool status) {
    mGameEnded = status;
    emit gameEndedChanged();
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
        if (lastPressed == index) {
            return;
        }
        if (numbers.empty()) {
            setGameEnded(true);
            setColor_red(red_activated);
            setColor_blue(blue_activated);
            setColor_orange(orange_activated);
            setColor_yellow(yellow_activated);
            return;
        }
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
        numbers.pop();
        setCount(++mCount);
        int newInterval = 1200-200*log(mCount);
        setInterval(newInterval);
        lastPressed = index;
        qDebug() << mCount;
        qDebug() << mInterval;
    }

}

void SpeedTest::setColors (int previous, int next) {
    switch (previous) {
    case 0:
        setColor_red(red_idle);
        break;
    case 1:
        setColor_blue(blue_idle);
        break;
    case 2:
        setColor_orange(orange_idle);
        break;
    case 3:
        setColor_yellow(yellow_idle);
        break;

    }

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

int SpeedTest::generateRandomNumber (int range) {
    srand(time(NULL));
    return rand() % range;
}

void SpeedTest::tick() {
    if (!mGameEnded) {
        numbers.push(next);
        setColors(previous, next);
        previous = next;
        next = (next + generateRandomNumber(3) + 1) % 4;
    }
    return;
}

void SpeedTest::startGame() {
    setGameEnded(!mGameEnded);

    setColor_red(red_idle);
    setColor_blue(blue_idle);
    setColor_orange(orange_idle);
    setColor_yellow(yellow_idle);
    setCount(0);
    setInterval(INITIAL_INTERVAL);
    lastPressed = NO_VALUE;

    while (!numbers.empty()) {
        numbers.pop();
    }

    if (!mGameEnded) {
        int first = generateRandomNumber(4);
        numbers.push(first);
        setColors(previous, first);
        previous = first;
        next = (first + generateRandomNumber(3) + 1) % 4;
    }

}



