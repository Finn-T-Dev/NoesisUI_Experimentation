////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include "ArithmeticParser.h"

#include <NsCore/StringUtils.h>


namespace
{

struct Operator
{
    enum class Associativity
    {
        Right, Left, None
    };

    char op;
    uint32_t precedence;
    Associativity associativity;
    float (*func)(Noesis::BaseVector<float>& stack);
};

}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float Pop(Noesis::BaseVector<float>& stack)
{
    if (!stack.Empty())
    {
        float v = stack.Back();
        stack.PopBack();
        return v;
    }

    return 0.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static Operator ParseFunc(const char* expr, uint32_t& parsed)
{
    if (Noesis::StrStartsWith(expr, "min"))
    {
        parsed = (uint32_t)strlen("min");

        return Operator{ 'F', 10, Operator::Associativity::None, [](Noesis::BaseVector<float>& stack)
        {
            float b = Pop(stack);
            float a = Pop(stack);
            return Noesis::Min(a, b);
        }};
    }
    else if (Noesis::StrStartsWith(expr, "max"))
    {
        parsed = (uint32_t)strlen("max");

        return Operator{ 'F', 10, Operator::Associativity::None, [](Noesis::BaseVector<float>& stack)
        {
            float b = Pop(stack);
            float a = Pop(stack);
            return Noesis::Max(a, b);
        }};
    }
    else if (Noesis::StrStartsWith(expr, "floor"))
    {
        parsed = (uint32_t)strlen("floor");

        return Operator{ 'F', 10, Operator::Associativity::None, [](Noesis::BaseVector<float>& stack)
        {
            float a = Pop(stack);
            return Noesis::Floor(a);
        }};
    }
    else if (Noesis::StrStartsWith(expr, "round"))
    {
        parsed = (uint32_t)strlen("round");

        return Operator{ 'F', 10, Operator::Associativity::None, [](Noesis::BaseVector<float>& stack)
        {
            float a = Pop(stack);
            return (float)Noesis::Round(a);
        }};
    }
    else if (Noesis::StrStartsWith(expr, "ceil"))
    {
        parsed = (uint32_t)strlen("ceil");

        return Operator{ 'F', 10, Operator::Associativity::None, [](Noesis::BaseVector<float>& stack)
        {
            float a = Pop(stack);
            return Noesis::Ceil(a);
        } };
    }
    else if (Noesis::StrStartsWith(expr, "sin"))
    {
        parsed = (uint32_t)strlen("sin");

        return Operator{ 'F', 10, Operator::Associativity::None, [](Noesis::BaseVector<float>& stack)
        {
            float a = Pop(stack);
            return sinf(a);
        }};
    }
    else if (Noesis::StrStartsWith(expr, "cos"))
    {
        parsed = (uint32_t)strlen("cos");

        return Operator{ 'F', 10, Operator::Associativity::None, [](Noesis::BaseVector<float>& stack)
        {
            float a = Pop(stack);
            return cosf(a);
        }};
    }
    else if (Noesis::StrStartsWith(expr, "pow"))
    {
        parsed = (uint32_t)strlen("pow");

        return Operator{ 'F', 10, Operator::Associativity::None, [](Noesis::BaseVector<float>& stack)
        {
            float b = Pop(stack);
            float a = Pop(stack);
            return powf(a, b);
        }};
    }
    else if (Noesis::StrStartsWith(expr, "abs"))
    {
        parsed = (uint32_t)strlen("abs");

        return Operator{ 'F', 10, Operator::Associativity::None, [](Noesis::BaseVector<float>& stack)
        {
            float a = Pop(stack);
            return fabsf(a);
        } };
    }

    parsed = 0;
    return Operator{};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static bool ParseOperator(const char* expr, Operator& op, bool binaryAllowed)
{
    if (binaryAllowed)
    {
        switch (*expr)
        {
            case '*':
            {
                op = { '*', 8, Operator::Associativity::Left, [](Noesis::BaseVector<float>& stack)
                {
                    float b = Pop(stack);
                    float a = Pop(stack);
                    return a * b;
                }};

                return true;
            }
            case '/':
            {
                op = { '/', 8, Operator::Associativity::Left, [](Noesis::BaseVector<float>& stack)
                {
                    float b = Pop(stack);
                    float a = Pop(stack);
                    return a / b;
                }};

                return true;
            }
            case '%':
            {
                op = { '%', 8, Operator::Associativity::Left, [](Noesis::BaseVector<float>& stack)
                {
                    float b = Pop(stack);
                    float a = Pop(stack);
                    return fmodf(a, b);
                }};

                return true;
            }
            case '+':
            {
                op = { '+', 6, Operator::Associativity::Left, [](Noesis::BaseVector<float>& stack)
                {
                    float b = Pop(stack);
                    float a = Pop(stack);
                    return a + b;
                }};

                return true;
            }
            case '-':
            {
                op = { '-', 6, Operator::Associativity::Left, [](Noesis::BaseVector<float>& stack)
                {
                    float b = Pop(stack);
                    float a = Pop(stack);
                    return a - b;
                }};

                return true;
            }
        }
    }

    switch (*expr)
    {
        case '+':
        {
            // Unary plus
            op = { '+', 9, Operator::Associativity::Right, [](Noesis::BaseVector<float>& stack)
            {
                float a = Pop(stack);
                return a;
            }};

            return true;
        }
        case '-':
        {
            // Unary minus 
            op = { '-', 9, Operator::Associativity::Right, [](Noesis::BaseVector<float>& stack)
            {
                float a = Pop(stack);
                return -a;
            }};

            return true;
        }
        case '(':
        {
            op= { '(', 0, Operator::Associativity::None, nullptr};
            return true;
        }
        case ')':
        {
            op= { ')', 0, Operator::Associativity::None, nullptr};
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
static float ParseConstant(const char* expr, Noesis::ArrayRef<float> inputs, float param, uint32_t& parsed)
{
    if (expr[0] == '{')
    {
        uint32_t charParsed;
        uint32_t N = Noesis::StrToUInt32(expr + 1, &charParsed);

        if (N < inputs.Size() && charParsed > 0 && expr[charParsed + 1] == '}')
        {
            parsed = charParsed + 2;
            return inputs[N];
        }
    }

    if (Noesis::StrStartsWith(expr, "{_}"))
    {
        parsed = 3;
        return param;
    }

    parsed = 0;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool Parse(const char* expr, Noesis::ArrayRef<float> inputs, float param, float& value)
{
    uint32_t numChars = (uint32_t)strlen(expr);
    uint32_t pos = 0;

    struct Out
    {
        enum Type
        {
            Value, Op
        };

        Type type;

        union
        {
            float v;
            Operator op;
        };
    };

    Noesis::Vector<Out, 256> queue;
    Noesis::Vector<Operator, 128> stack;

    bool binaryOpAllowed = false;

    while (pos < numChars)
    {
        // Skip spaces
        while (expr[pos] == ' ') pos++;
        if (pos == numChars) break;

        uint32_t parsed;

        // Function
        Operator func = ParseFunc(expr + pos, parsed);
        if (parsed > 0)
        {
            stack.PushBack(func);
            pos += parsed;
            binaryOpAllowed = false;
            continue;
        }

        Operator op;
        if (ParseOperator(expr + pos, op, binaryOpAllowed))
        {
            // Operator
            if (op.op != '(' && op.op != ')')
            {
                while (!stack.Empty() && stack.Back().op != '(')
                {
                    Operator op2 = stack.Back();

                    if (op2.precedence > op.precedence || (op2.precedence == op.precedence &&
                        op.associativity == Operator::Associativity::Left))
                    {
                        stack.PopBack();

                        Out out;
                        out.type = Out::Type::Op;
                        out.op = op2;

                        queue.PushBack(out);
                    }
                    else break;
                }

                stack.PushBack(op);
                pos++;
                binaryOpAllowed = false;
                continue;
            }

            // Left parenthesis
            if (op.op == '(')
            {
                stack.PushBack(op);
                pos++;
                binaryOpAllowed = false;
                continue;
            }

            // Right parenthesis
            if (op.op == ')')
            {
                while (!stack.Empty() && stack.Back().op != '(')
                {
                    Out out;
                    out.type = Out::Type::Op;
                    out.op = stack.Back();

                    stack.PopBack();
                    queue.PushBack(out);
                }

                if (stack.Empty() || stack.Back().op != '(')
                {
                    // Mismatched parentheses
                    return false;
                }

                NS_ASSERT(!stack.Empty() && stack.Back().op == '(');
                stack.PopBack();

                // If there is a function in the stack, move it to the queue
                if (!stack.Empty() && stack.Back().op == 'F')
                {
                    Out out;
                    out.type = Out::Type::Op;
                    out.op = stack.Back();

                    stack.PopBack();
                    queue.PushBack(out);
                }

                pos++;
                binaryOpAllowed = true;
                continue;
            }
        }

        // Comma
        if (expr[pos] == ',')
        {
            while (!stack.Empty() && stack.Back().op != '(')
            {
                Out out;
                out.type = Out::Type::Op;
                out.op = stack.Back();

                stack.PopBack();
                queue.PushBack(out);
            }

            pos++;
            binaryOpAllowed = false;
            continue;
        }

        // Number
        float v = Noesis::StrToFloat(expr + pos, &parsed);
        if (parsed > 0)
        {
            queue.PushBack(Out{ Out::Type::Value, { v } });
            pos += parsed;
            binaryOpAllowed = true;
            continue;
        }

        // Constant
        v = ParseConstant(expr + pos, inputs, param, parsed);
        if (parsed > 0)
        {
            queue.PushBack(Out{ Out::Type::Value, { v } });
            pos += parsed;
            binaryOpAllowed = true;
            continue;
        }

        // Invalid expression
        return false;
    }

    // Pop the remaining items from the operator stack into the output queue
    while (!stack.Empty())
    {
        if (stack.Back().op == '(')
        {
            // Mismatched parentheses
            return false;
        }

        Out out;
        out.type = Out::Type::Op;
        out.op = stack.Back();

        stack.PopBack();
        queue.PushBack(out);
    }

    // RPN evaluation
    Noesis::Vector<float, 128> values;
    for (const Out& o : queue)
    {
        if (o.type == Out::Type::Value)
        {
            values.PushBack(o.v);
        }
        else
        {
            values.PushBack(o.op.func(values));
        }
    }

    if (values.Size() != 1)
    {
        return false;
    }

    NS_ASSERT(values.Size() == 1);
    value = values.Back();
    return true;
}
