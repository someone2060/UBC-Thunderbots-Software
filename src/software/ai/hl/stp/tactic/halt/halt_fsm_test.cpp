#include "software/ai/hl/stp/tactic/halt/halt_fsm.h"

#include <gtest/gtest.h>

#include "software/test_util/test_util.h"

TEST(StopFSMTest, test_transitions)
{
    std::shared_ptr<World> world = ::TestUtil::createBlankTestingWorld();
    Robot robot(0,
                RobotState(Point(1, -3), Vector(2.1, 3.1), Angle::half(),
                           AngularVelocity::zero()),
                Timestamp::fromSeconds(123));

    FSM<HaltFSM> fsm{HaltFSM()};
    EXPECT_TRUE(fsm.is(boost::sml::state<HaltFSM::StopState>));
    fsm.process_event(HaltFSM::Update(
        {}, TacticUpdate(robot, world, [](std::shared_ptr<Primitive>) {})));
    // robot is still moving
    EXPECT_TRUE(fsm.is(boost::sml::state<HaltFSM::StopState>));
    robot = Robot(0,
                  RobotState(Point(1, -3), Vector(1.1, 2.1), Angle::half(),
                             AngularVelocity::zero()),
                  Timestamp::fromSeconds(123));
    fsm.process_event(HaltFSM::Update(
        {}, TacticUpdate(robot, world, [](std::shared_ptr<Primitive>) {})));
    // robot is still moving
    EXPECT_TRUE(fsm.is(boost::sml::state<HaltFSM::StopState>));
    robot = TestUtil::createRobotAtPos(Point(1, -3));
    fsm.process_event(HaltFSM::Update(
        {}, TacticUpdate(robot, world, [](std::shared_ptr<Primitive>) {})));
    // robot stopped
    EXPECT_TRUE(fsm.is(boost::sml::X));
}
