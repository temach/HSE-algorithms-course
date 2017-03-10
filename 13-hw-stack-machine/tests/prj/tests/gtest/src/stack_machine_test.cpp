////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Unit tests for xi::StackMachine class
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      23.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// Gtest-based unit test.
/// The naming conventions imply the name of a unit-test module is the same as 
/// the name of the corresponding tested module with _test suffix
///
/// Note the issue about including point modules here (ask the trainer about).
/// 
////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include <climits>   // INT_MAX

#include "stack_machine.h"



/// Fixture class for testing stack machine
class StackMachineTest : public testing::Test {


protected:
    
    /// Invoked before each test
    virtual void SetUp()
    {
        
        
        // TODO: register all necessay operations here
        _sm.registerOperation('&', &_andop);
        _sm.registerOperation('^', &_powop);
        _sm.registerOperation('+', &_plusop);
        _sm.registerOperation('*', &_mulop);
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() { }

protected:
    xi::StackMachine _sm;           // stack machine itself

    // TODO: add here all operation to be registered for a specific instance of the stack machine,
    // it depends on the individual assignment
    xi::PlusOp _plusop;
    xi::AndOp _andop;
    xi::PowerOp _powop;
    xi::MulOp _mulop;



}; // class TestMachineTest



TEST(StackMachine, simplest)
{
    using namespace xi;

    xi::StackMachine sm;
}


// tests with the fixture class
TEST_F(StackMachineTest, plusOp1)
{
    int res = _sm.calculate("7 8 10 + +");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 25);
    EXPECT_EQ(r1, 25);
}


TEST_F(StackMachineTest, plusOp2)
{
    int res = _sm.calculate("8 10 + 7 +");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 25);
    EXPECT_EQ(r1, 25);
}


TEST_F(StackMachineTest, undefOper1)
{
    // for undefined operation (let it be >) must raise an exception
    EXPECT_THROW(_sm.calculate("10 8 >"), std::logic_error);
}


// TODO: a skeleton for testing operation '*' (multiplication)
// will produce std::logic_error("No operation defined" for undefined operation
TEST_F(StackMachineTest, multiOp1)
{
    int res = _sm.calculate("2 3 *");      
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 6);
    EXPECT_EQ(r1, 6);
}


// TODO: a skeleton for testing operation '&' 
// will produce std::logic_error("No operation defined" for undefined operation
TEST_F(StackMachineTest, andOp1)
{

    int res = _sm.calculate("1 3 &");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 1 & 3);
    EXPECT_EQ(r1, 1 & 3);                  
}


// TODO: a skeleton for testing operation '^' 
// will produce std::logic_error("No operation defined" for undefined operation
TEST_F(StackMachineTest, powOp1)
{

    int res = _sm.calculate("    2  3 ^   ");
    int r1 = _sm.getStack().top();
    EXPECT_EQ(res, 8);
    EXPECT_EQ(r1, 8);
}


