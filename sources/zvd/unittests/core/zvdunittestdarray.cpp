/*
-----------------
 Persistent info
-----------------

This file is part of the "Zv3D" project.

MIT License

Copyright (c) 2012-2099 Marat Sungatullin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
nCopies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
nCopies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

......
 Web:
......

 + https:// (for questions and help)

-------------
 Description
-------------
Purpose: blank file for implementations (.cpp files).

----------------------
 For developers notes
----------------------

*/

#include "gtest/gtest.h"
#include "core/base/containers/zvddarray.h"
#include <string>

namespace zvd
{
    namespace utest
    {
        //-----------------------------------------------------------------------------
        // Test Fixtures for different types
        //-----------------------------------------------------------------------------

        // A helper struct to track nConstructions, nDestructions, nCopies, and nMoves.
        struct CDCMCounter
        {
            static int nConstructions;
            static int nDestructions;
            static int nCopies;
            static int nMoves;

            static void Reset() { nConstructions = nDestructions = nCopies = nMoves = 0; }
        };
        int CDCMCounter::nConstructions = 0;
        int CDCMCounter::nDestructions = 0;
        int CDCMCounter::nCopies = 0;
        int CDCMCounter::nMoves = 0;


        // SCENARIO 1: Type with a non-throwing (noexcept) move constructor.
        struct DummyNoexceptMoveOnly : public CDCMCounter
        {
            int value{};
            DummyNoexceptMoveOnly(int v = 0) : value(v) { nConstructions++; }
            ~DummyNoexceptMoveOnly() { nDestructions++; }

            DummyNoexceptMoveOnly(const DummyNoexceptMoveOnly&) = delete; // No copying allowed
            DummyNoexceptMoveOnly& operator=(const DummyNoexceptMoveOnly&) = delete;

            DummyNoexceptMoveOnly(DummyNoexceptMoveOnly&& other) noexcept : value(other.value)
            {
                nMoves++;
                other.value = -1; // Invalidate the source
            }
            DummyNoexceptMoveOnly& operator=(DummyNoexceptMoveOnly&& other) noexcept
            {
                nMoves++;
                value = other.value;
                other.value = -1;
                return *this;
            }
        };

        // SCENARIO 2: Type that can only be copied.
        struct DummyCopyOnly : public CDCMCounter
        {
            int value;
            DummyCopyOnly(int v = 0) : value(v) { nConstructions++; }
            ~DummyCopyOnly() { nDestructions++; }

            DummyCopyOnly(const DummyCopyOnly& other) : value(other.value) { nCopies++; }
            DummyCopyOnly& operator=(const DummyCopyOnly& other) { nCopies++; value = other.value; return *this; }

            DummyCopyOnly(DummyCopyOnly&&) = delete; // No moving allowed
            DummyCopyOnly& operator=(DummyCopyOnly&&) = delete;
        };

        // SCENARIO 3: Type with a throwing copy constructor.
        struct DummyThrowingCopy : public CDCMCounter
        {
            int value;
            static int s_nThrowOnCopyAttempt; // The copy construction number on which to throw (from 1)

            DummyThrowingCopy(int v = 0) : value(v) { nConstructions++; }
            ~DummyThrowingCopy() { nDestructions++; }

            DummyThrowingCopy(const DummyThrowingCopy& other) : value(other.value)
            {
                int nAttempt = nCopies + 1;
                if (nAttempt == s_nThrowOnCopyAttempt)
                {
                    throw std::runtime_error("Copy constructor failed as planned!");
                }
                nCopies++;
            }
            DummyThrowingCopy& operator=(const DummyThrowingCopy& other) { /*...*/ return *this; }
        };
        int DummyThrowingCopy::s_nThrowOnCopyAttempt = -1; // Disabled by default

        
    }// eof utest
} // eof zvd



//-----------------------------------------------------------------------------
// The Tests
//-----------------------------------------------------------------------------

// We use a test fixture to reset counters before each test.
class ZvdcUTestDArrayPushBackTest : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        zvd::utest::CDCMCounter::Reset();
        zvd::utest::DummyThrowingCopy::s_nThrowOnCopyAttempt = -1;
        ZvdcMallocFreeMemoryAllocator::ResetAllocationsCounter();
    }

    void TearDown() override
    {
        // This check will run after EVERY test in this suite.
        EXPECT_EQ(ZvdcMallocFreeMemoryAllocator::GetLiveAllocations(), 0) << "Memory leak detected!";
    }
};

TEST_F(ZvdcUTestDArrayPushBackTest, GrowthStrategyIsCorrect)
{
    // Check min capacity of 4 and 1.5x growth factor.
    ZvdcDArray<int> arr;
    EXPECT_EQ(arr.capacity(), 0);

    arr.push_back(1); // 0 -> 4 (min capacity)
    EXPECT_EQ(arr.capacity(), 4);

    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    EXPECT_EQ(arr.capacity(), 4); // Still fits

    arr.push_back(5); // 4 -> 4 + (4/2) = 6
    EXPECT_EQ(arr.capacity(), 6);

    arr.push_back(6);
    EXPECT_EQ(arr.capacity(), 6);

    arr.push_back(7); // 6 -> 6 + (6/2) = 9
    EXPECT_EQ(arr.capacity(), 9);

    // Verify content
    for (int i = 0; i < 7; ++i) {
        EXPECT_EQ(arr[i], i + 1);
    }
}

TEST_F(ZvdcUTestDArrayPushBackTest, HandlesNoexceptMoveCorrectly)
{
    // Test that the array prefers moving over copying.
    ZvdcDArray<zvd::utest::DummyNoexceptMoveOnly> arr;
    arr.reserve(2); // Start with a known capacity

    arr.push_back(zvd::utest::DummyNoexceptMoveOnly(10));
    arr.push_back(zvd::utest::DummyNoexceptMoveOnly(20));

    // Reset counters to ignore initial nConstructions
    zvd::utest::CDCMCounter::Reset();

    // This push_back will trigger a reallocation.
    // It must use MOVE, not COPY.
    arr.push_back(zvd::utest::DummyNoexceptMoveOnly(30));

    EXPECT_EQ(zvd::utest::CDCMCounter::nConstructions, 1); // For the new object DummyNoexceptMoveOnly(30)
    EXPECT_EQ(zvd::utest::CDCMCounter::nCopies, 0); // MUST be zero
    EXPECT_GE(zvd::utest::CDCMCounter::nMoves, 2);  // At least 2 nMoves for the old elements
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[2].value, 30);
}

TEST_F(ZvdcUTestDArrayPushBackTest, HandlesCopyOnlyCorrectly)
{
    // Test that the array falls back to copying for copy-only types.
    ZvdcDArray<zvd::utest::DummyCopyOnly> arr;
    arr.reserve(2);

    zvd::utest::DummyCopyOnly obj1(10);
    arr.push_back(obj1);
    zvd::utest::DummyCopyOnly obj2(20);
    arr.push_back(obj2);

    zvd::utest::CDCMCounter::Reset();

    // This push_back will trigger a reallocation.
    // It MUST use COPY.
    zvd::utest::DummyCopyOnly obj3(30);
    arr.push_back(obj3);

    EXPECT_EQ(zvd::utest::CDCMCounter::nConstructions, 1); // For the new object DummyCopyOnly(30)
    EXPECT_GE(zvd::utest::CDCMCounter::nCopies, 2);  // At least 2 nCopies for the old elements
    EXPECT_EQ(zvd::utest::CDCMCounter::nMoves, 0); // MUST be zero
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[2].value, 30);
}

TEST_F(ZvdcUTestDArrayPushBackTest, IsExceptionSafeDuringReallocation)
{
    // The most important test: verify strong exception safety.
    ZvdcDArray<zvd::utest::DummyThrowingCopy> arr;
    arr.reserve(4);

    // Let's make the 3rd copy (when copying element with value=3) throw.
    // Total nCopies: 4 old, copy new, copy elem 0, copy elem 1, copy elem 2 (throws!)
    zvd::utest::DummyThrowingCopy::s_nThrowOnCopyAttempt = 8;

    arr.push_back(zvd::utest::DummyThrowingCopy(1));
    arr.push_back(zvd::utest::DummyThrowingCopy(2));
    arr.push_back(zvd::utest::DummyThrowingCopy(3));
    arr.push_back(zvd::utest::DummyThrowingCopy(4));

 
    // The next push_back will reallocate.
    zvd::utest::DummyThrowingCopy obj5(5);
    ZvdRegularResult result;
    // We expect our push_back to catch the exception and return an error code.
    result = arr.push_back(obj5);
    // After the push_back that threw
    // Let's say we tried to copy 4 elements and the 3rd one threw.
    // 3 elements were successfully constructed in the new buffer before the exception.
    // Our exception-safe algorithm MUST destroy these 3 elements during rollback.
    // So, we expect 7 destructor calls.
    EXPECT_EQ(zvd::utest::CDCMCounter::nDestructions, 7);

    // Check the result
    EXPECT_FALSE(result.IsOk());
    EXPECT_EQ(result.Error().Code(), kZVD_EC_CONSTRUCTEXCEPTION);

    // CRITICAL CHECK: The original array must be in its original state.
    // This is the strong exception safety guarantee.
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr.capacity(), 4);
    EXPECT_EQ(arr[0].value, 1);
    EXPECT_EQ(arr[1].value, 2);
    EXPECT_EQ(arr[2].value, 3);
    EXPECT_EQ(arr[3].value, 4);
}

TEST_F(ZvdcUTestDArrayPushBackTest, IsExceptionSafeDuringReallocation2)
{
    // The most important test: verify strong exception safety.
    ZvdcDArray<zvd::utest::DummyThrowingCopy> arr;
    arr.reserve(4);

    // Let's make the 3rd copy (when copying element with value=3) throw.
    // Total nCopies: 4 old, copy new (throws!)
    zvd::utest::DummyThrowingCopy::s_nThrowOnCopyAttempt = 5;

    arr.push_back(zvd::utest::DummyThrowingCopy(1));
    arr.push_back(zvd::utest::DummyThrowingCopy(2));
    arr.push_back(zvd::utest::DummyThrowingCopy(3));
    arr.push_back(zvd::utest::DummyThrowingCopy(4));


    // The next push_back will reallocate.
    zvd::utest::DummyThrowingCopy obj5(5);
    ZvdRegularResult result;
    // We expect our push_back to catch the exception and return an error code.
    result = arr.push_back(obj5);
    // After the push_back that threw
    // Let's say we tried to copy 4 elements and the 3rd one threw.
    // 0 elements were successfully constructed in the new buffer before the exception.
    // Our exception-safe algorithm MUST destroy these 0 elements during rollback.
    // So, we expect 4 destructor calls.
    EXPECT_EQ(zvd::utest::CDCMCounter::nDestructions, 4);

    // Check the result
    EXPECT_FALSE(result.IsOk());
    EXPECT_EQ(result.Error().Code(), kZVD_EC_CONSTRUCTEXCEPTION);

    // CRITICAL CHECK: The original array must be in its original state.
    // This is the strong exception safety guarantee.
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr.capacity(), 4);
    EXPECT_EQ(arr[0].value, 1);
    EXPECT_EQ(arr[1].value, 2);
    EXPECT_EQ(arr[2].value, 3);
    EXPECT_EQ(arr[3].value, 4);
}
