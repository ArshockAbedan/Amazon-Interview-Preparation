//============================================================================
// Name        : StringToInteger_atoi.cpp
// Author      : Aref Abedjooy
// Version     : 1.0
// Copyright   : Copyright (c) 2022, Aref Abedjooy. No Rights Reserved.
// Description : https://leetcode.com/problems/string-to-integer-atoi/
//============================================================================
#include <iostream>
using namespace std;

enum State
{
    q0,
    q1,
    q2,
    qd
};

class StateMachine
{
private:
    State currentState;
    int sign, result;

    // transition to state q1;
    void toStateQ1(char &ch)
    {
        sign = ch == '-' ? -1 : 1;
        currentState = q1;
    }

    // transition to sate Q2
    void toStateQ2(int digit)
    {
        currentState = q2;
        appendDigit(digit);
    }

    // transition to dead state
    void toStateQd()
    {
        currentState = qd;
    }

    // append digit to result, if out of range return handled value
    void appendDigit(int digit)
    {
        if ((result > INT_MAX / 10) || (result == INT_MAX / 10 && digit > INT_MAX % 10))
        {
            if (sign == 1)
            {
                // if sign is 1, handle overflowed value to INT_MAX
                result = INT_MAX;
            }
            else
            {
                // if sign is -1, handle underflowed value to INT_MIN
                result = INT_MIN;
                sign = 1;
            }

            // whne it is out of range, a dead state is reached.
            toStateQd();
        }
        else
        {
            // append current digit to the result.
            result = result * 10 + digit;
        }
    }

public:
    StateMachine()
    {
        currentState = q0;
        sign = 1;
        result = 0;
    }
    // Get current state
    State getState()
    {
        return currentState;
    }

    // chnage state based on current character of input
    void transition(char &c)
    {
        if (currentState == q0)
        {
            // beginnig state or some whitespace are skipped already.
            if (c == ' ')
            {
                // current character is whitspace. So, we stay in same state.
                return;
            }
            else if (c == '+' || c == '-')
            {
                // current character is a sign
                toStateQ1(c);
            }
            else if (isdigit(c))
            {
                // current character is digit.
                toStateQ2(c - '0');
            }
            else
            {
                // current character is not digit/sign/space
                // a dead state is reached
                toStateQd();
            }
        }
        else if (currentState == q1 || currentState == q2)
        {
            // prevoius character was a sign or a digit
            if (isdigit(c))
            {
                // current character is digit.
                toStateQ2(c - '0');
            }
            else
            {
                // Current character is not a digit.
                // Reached a dead state.
                toStateQd();
            }
        }
    }

    // return final result along with its sign
    int getInteger()
    {
        return result * sign;
    }
};

class Solution
{
public:
    int myAtoi(string s)
    {
        StateMachine Q;

        for (int i = 0; i < s.length() && Q.getState() != qd; i++)
        {
            Q.transition(s[i]);
        }

        return Q.getInteger();
    }
};

int main()
{
    Solution *solution = new Solution();
    string input = "12   4";
    cout << solution->myAtoi(input);
}