#include "speedtest.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QtMath>

SpeedTest::SpeedTest(QObject *parent)
    : QObject(parent)
    , mRed_activated(false)
    , mBlue_activated(false)
    , mOrange_activated(false)
    , mYellow_activated(false)
    , mGameEnded(true)
    , next (-1)
    , mCount (0)
    , lastPressed (-1)

{          

    // reactionTimes = new QVector<int>;


    flashes = new QQueue<Flash>;

    // read record points

    setRecord(readRecord());

    // initiate timers

    intervalTimer = new QTimer(this);
    connect(intervalTimer, SIGNAL(timeout()), this, SLOT(tick()));
    intervalTimer->setTimerType(Qt::PreciseTimer);

    elapsedTimer = new QElapsedTimer();

    for (int i = 0 ; i < 4 ; i++) {
        wrongButtonTimers[i] = new QTimer(this);
    }
    connect(wrongButtonTimers[0], &QTimer::timeout, this, [this]{setRed_activated(!mRed_activated);});
    connect(wrongButtonTimers[1], &QTimer::timeout, this, [this]{setBlue_activated(!mBlue_activated);});
    connect(wrongButtonTimers[2], &QTimer::timeout, this, [this]{setOrange_activated(!mOrange_activated);});
    connect(wrongButtonTimers[3], &QTimer::timeout, this, [this]{setYellow_activated(!mYellow_activated);});


    animationTimer = new QTimer(this);
    startAnimation();

    // seed for random numbers

    randomGenerator = QRandomGenerator::global();

}

bool SpeedTest::gameEnded() {
    return mGameEnded;
}

//double SpeedTest::variance(QVector<int> numbers)
//{
//    double mean;
//    int total = 0;
//    for (int i = 0; i < numbers.size(); i++) {
//        total += numbers.at(i);
//    }
//    mean = total / numbers.size();
//    double sum = 0;
//    for (int i = 0; i < numbers.size(); i++) {
//        double abs = qFabs(numbers.at(i) - mean);
//        double pw2 = qPow(abs, 2);
//        sum += pw2;
//    }
//    return sum/numbers.size();
//}

int SpeedTest::count() {
    return mCount;
}

int SpeedTest::interval()
{
    if (mCount > 0)
        return 1200 - 200 * qLn(mCount);
    else
        return 2000;
}

int SpeedTest::record()
{
    return mRecord;
}

bool SpeedTest::red_activated() {
    return mRed_activated;
}

bool SpeedTest::blue_activated() {
    return mBlue_activated;
}

bool SpeedTest::orange_activated() {
    return mOrange_activated;
}

bool SpeedTest::yellow_activated() {
    return mYellow_activated;
}

void SpeedTest::setCount(int newcount) {
    mCount = newcount;
    emit countChanged();
}

bool SpeedTest::setRecord(int newRecord)
{
    mRecord = newRecord;
    emit recordChanged();
    return true;
}

/*

  Sets gameEnded status. Stops timer if game ended and writes new record to file.

*/

void SpeedTest::setGameEnded(bool ended) {
    mGameEnded = ended;    
    if (ended) {
        intervalTimer->stop();

//        if (!reactionTimes->isEmpty()) {

//            qDebug() << *reactionTimes;
//            qDebug() << "Variance: " << variance(*reactionTimes);

//        }
//        reactionTimes->clear();

        if (mCount > mRecord)
            writeRecord(mCount);
    }
    emit gameEndedChanged();
}

void SpeedTest::setRed_activated(bool newState)
{
    if (mRed_activated != newState) {
        mRed_activated = newState;
        emit red_activatedChanged();
    }
}

void SpeedTest::setBlue_activated(bool newState)
{
    if (mBlue_activated != newState) {
        mBlue_activated = newState;
        emit blue_activatedChanged();
    }
}

void SpeedTest::setOrange_activated(bool newState)
{
    if (mOrange_activated != newState) {
        mOrange_activated = newState;
        emit orange_activatedChanged();
    }
}

void SpeedTest::setYellow_activated(bool newState)
{
    if (mYellow_activated != newState) {
        mYellow_activated = newState;
        emit yellow_activatedChanged();
    }
}

void SpeedTest::buttonPressed(int index) {

    if (!mGameEnded) {

        // ignore when user presses same button multiple times

        if (lastPressed == index) {
            return;
        }

        // end game when user presses button when queue is empty

        if (flashes->isEmpty()) {
            setGameEnded(true);
            activateAll();
            return;
        }

        // end game when user presses wrong button

        int target = flashes->head().position;
        if (target != index) {
            setGameEnded(true);
            idleAll();
            switch (target) {
            case 0:
                setRed_activated(true);
                break;
            case 1:
                setBlue_activated(true);
                break;
            case 2:
                setOrange_activated(true);
                break;
            case 3:
                setYellow_activated(true);
            }

            const int INTERVAL = 1000;
            wrongButtonTimers[index]->start(INTERVAL);
            return;
        }

        // user presses right button

        // end game when reaction time is inhumane

        int reactionTime = elapsedTimer->elapsed() - flashes->head().timestamp;

        if (reactionTime < 100) {
            setGameEnded(true);
            activateAll();
            return;
        }

//        reactionTimes->append(reactionTime);
        flashes->removeFirst();
        setCount(++mCount);
        lastPressed = index;      
    }

}

void SpeedTest::setColors (int next) {

    idleAll();

    switch (next) {
    case 0:
        setRed_activated(true);
        break;
    case 1:
        setBlue_activated(true);
        break;
    case 2:
        setOrange_activated(true);
        break;
    case 3:
        setYellow_activated(true);
        break;

    }
}

void SpeedTest::activateAll () {
    setRed_activated(true);
    setBlue_activated(true);
    setOrange_activated(true);
    setYellow_activated(true);
}

void SpeedTest::idleAll() {
    setRed_activated(false);
    setBlue_activated(false);
    setOrange_activated(false);
    setYellow_activated(false);
}

void SpeedTest::startAnimation()
{
    const int INTERVAL = 500;
    int count = 0;
    connect(animationTimer, &QTimer::timeout, this, [this, count] () mutable {
        switch (count % 12) {
        case 0:
            setRed_activated(true);
            break;
        case 1:
            setBlue_activated(true);
            break;
        case 2:
            setOrange_activated(true);
            break;
        case 3:
            setYellow_activated(true);
            break;
        case 6:
            setYellow_activated(false);
            break;
        case 7:
            setOrange_activated(false);
            break;
        case 8:
            setBlue_activated(false);
            break;
        case 9:
            setRed_activated(false);
            break;
        default:
            mRed_activated ? idleAll() : activateAll();
            break;
        }
        count++;
    });
    animationTimer->start(INTERVAL);
}


/*

  Timer activates this function

*/

void SpeedTest::tick() {
    if (!mGameEnded) {        
        intervalTimer->setInterval(interval());
        Flash flash;
        flash.position = next;
        flash.timestamp = elapsedTimer->elapsed();
        flashes->append(flash);

        // end game if user has not responded to 10 flashes

        if (flashes->size() > 9) {
             setGameEnded(true);
             activateAll();
             return;
        }

        setColors(next);

        // cheat test

//        int randomInterval = randomGenerator->bounded(100, 300);
//        QTimer::singleShot(randomInterval, this, [this]{buttonPressed(flashes->head().position);});


        next = (next + (randomGenerator->bounded(0, 2)) + 1) % 4;
    }
}

int SpeedTest::readRecord()
{
    QFile file("record.txt");
    if (!file.exists()) {
        setRecord(0);
        return 0;
    }
    if (!file.open(QIODevice::ReadOnly))
    {
        // qDebug() << file.errorString();
        return 0;
    }
    QTextStream stream(&file);
    QString line = stream.readLine();
    file.close();
    return line.toInt();
}

bool SpeedTest::writeRecord(int newRecord)
{
    QFile file("record.txt");
    if (!file.open(QIODevice::WriteOnly))
    {
        // qDebug() << file.errorString();
        return false;
    }
    QTextStream stream(&file);
    stream << QString::number(newRecord);
    file.close();
    return true;
}

void SpeedTest::startGame() {

    if (animationTimer->isActive())
        animationTimer->stop();
    for (QTimer* timer : wrongButtonTimers) {
        if (timer->isActive())
            timer->stop();
    }
    setGameEnded(false);
    idleAll();
    lastPressed = -1;
    flashes->clear();
    if (mCount > mRecord)
        setRecord(mCount);
    setCount(0);
    intervalTimer->start(interval());
    elapsedTimer->start();
    next = randomGenerator->bounded(0, 3);
    tick();

}



