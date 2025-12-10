#include "pch.h"
#include <gtest/gtest.h>
#include "MarkSys.h"

//тест 1.1: Корректная маркировка одним потоком
TEST(MarkSysTests, SingleThreadMarking)
{
    MarkSys sys(10, 1);
    sys.start();
    sys.waitForPause(1);

    auto arr = sys.getArrayState();
    for (int val : arr)
        EXPECT_EQ(val, 1);

    sys.stopAll();
}

//тест 1.2: Корректная очистка при завершении
TEST(MarkSysTests, SingleThreadCleanup)
{
    MarkSys sys(10, 1);
    sys.start();
    sys.waitForPause(1);

    sys.terminateMarker(1);
    auto arr = sys.getArrayState();
    for (int val : arr)
        EXPECT_EQ(val, 0);

    sys.stopAll();
}

//тест 2.1: Отсутствие гонки за ресурс
TEST(MarkSysTests, NoRaceCondition)
{
    MarkSys sys(20, 10);
    sys.start();
    sys.waitForAllPaused();

    auto arr = sys.getArrayState();
    int countMarked = 0;
    for (int val : arr)
    {
        EXPECT_TRUE(val >= 0 && val <= 10);
        if (val != 0) countMarked++;
    }
    EXPECT_EQ(countMarked, 20);

    sys.stopAll();
}

//тест 2.2: Корректное поочередное завершение
TEST(MarkSysTests, SequentialTermination)
{
    MarkSys sys(30, 5);
    sys.start();
    sys.waitForAllPaused();

    for (int t = 5; t >= 1; --t)
    {
        sys.terminateMarker(t);
        auto arr = sys.getArrayState();

        for (int val : arr)
            EXPECT_NE(val, t);

        sys.continueOthers();
    }

    auto arrFinal = sys.getArrayState();
    for (int val : arrFinal)
        EXPECT_EQ(val, 0);

    sys.stopAll();
}
