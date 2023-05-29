#ifndef SPEEDTEST_H
#define SPEEDTEST_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QQueue>
#include <QRandomGenerator>
#include "flash.cpp"

class SpeedTest : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool red_activated READ red_activated NOTIFY red_activatedChanged)
    Q_PROPERTY(bool blue_activated READ blue_activated NOTIFY blue_activatedChanged)
    Q_PROPERTY(bool orange_activated READ orange_activated NOTIFY orange_activatedChanged)
    Q_PROPERTY(bool yellow_activated READ yellow_activated NOTIFY yellow_activatedChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int interval READ interval NOTIFY countChanged)
    Q_PROPERTY(int record READ record NOTIFY recordChanged)
    Q_PROPERTY(bool gameEnded READ gameEnded NOTIFY gameEndedChanged)

public:
    explicit SpeedTest(QObject *parent = nullptr);
    Q_INVOKABLE void startGame();    
    Q_INVOKABLE void buttonPressed(int);
    bool red_activated();
    bool blue_activated();
    bool orange_activated();
    bool yellow_activated();
    int count();
    int interval();
    int record();
    bool gameEnded();
    // double variance(QVector<int>);



signals:
    void red_activatedChanged();
    void blue_activatedChanged();
    void orange_activatedChanged();
    void yellow_activatedChanged();
    void countChanged();
    void recordChanged();
    void gameEndedChanged();


public slots:
    void setRed_activated(bool);
    void setBlue_activated(bool);
    void setOrange_activated(bool);
    void setYellow_activated(bool);
    void setGameEnded(bool);
    void setCount(int);
    bool setRecord(int);
    void tick();    

private:    
    QTimer *intervalTimer;
    QTimer *animationTimer;
    QTimer *wrongButtonTimers[4];
    QElapsedTimer *elapsedTimer;
    QRandomGenerator *randomGenerator;
    bool mRed_activated;
    bool mBlue_activated;
    bool mOrange_activated;
    bool mYellow_activated;
    bool mGameEnded;
    QQueue<Flash> *flashes;
    int next;
    int mCount;
    int mRecord;
    int readRecord();
    bool writeRecord(int);
    void setColors(int);
    void activateAll();
    void idleAll();
    int lastPressed;
    // QVector<int> *reactionTimes;
    void startAnimation();

};

#endif // SPEEDTEST_H
