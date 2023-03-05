#ifndef SPEEDTEST_H
#define SPEEDTEST_H

#include <QObject>
#include <QColor>
#include <QTimer>
#include <queue>

class SpeedTest : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color_red READ color_red WRITE setColor_red NOTIFY color_redChanged)
    Q_PROPERTY(QColor color_blue READ color_blue WRITE setColor_blue NOTIFY color_blueChanged)
    Q_PROPERTY(QColor color_orange READ color_orange WRITE setColor_orange NOTIFY color_orangeChanged)
    Q_PROPERTY(QColor color_yellow READ color_yellow WRITE setColor_yellow NOTIFY color_yellowChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
    explicit SpeedTest(QObject *parent = nullptr);
    Q_INVOKABLE void startGame();    
    Q_INVOKABLE void buttonPressed(int);
    QColor color_red();
    QColor color_blue();
    QColor color_orange();
    QColor color_yellow();
    int count();



signals:
    void color_redChanged();
    void color_blueChanged();
    void color_orangeChanged();
    void color_yellowChanged();
    void countChanged();


public slots:
    void setColor_red(QColor);
    void setColor_blue(QColor);
    void setColor_orange(QColor);
    void setColor_yellow(QColor);
    void setGameEnded(bool);
    void setCount(int);
    void tick();

private:
    QColor mColor_red;
    QColor mColor_blue;
    QColor mColor_orange;
    QColor mColor_yellow;
    QTimer *timer;
    bool mGameEnded;
    std::queue<int> numbers;
    int next;
    int mCount;
    void clearQueue();
    void setColors(int);
    void activateAll();
    void idleAll();
    int lastPressed;


};

#endif // SPEEDTEST_H
