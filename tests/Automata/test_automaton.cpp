#include <gtest/gtest.h>
#include <string>
#include "../../src/Yolk/Automata/Automata.h"


TEST(Test_Automata, FSM_Basic_A)
{
    Yolk::Automata::State<std::string> A("A");
    Yolk::Automata::State<std::string> B("B");
    Yolk::Automata::State<std::string> C("C");

    Yolk::Automata::FSM<std::string, int> fsm(A);
    fsm.push_rule(A, 1, B);
    fsm.push_rule(B, 1, C);
    fsm.push_rule(C, 1, A);

    std::string test_A = fsm()();
    std::string test_B = fsm(1)();
    std::string test_C = fsm(1)();
    fsm << 1 << 1;
    std::string test_D = fsm()();
    std::string test_E = fsm(1, 1, 1, 1)();
    fsm.SetState(B);
    std::string test_F = fsm()();

    EXPECT_STREQ(test_A.c_str(), "A");
    EXPECT_STREQ(test_B.c_str(), "B");
    EXPECT_STREQ(test_C.c_str(), "C");
    EXPECT_STREQ(test_D.c_str(), "B");
    EXPECT_STREQ(test_E.c_str(), "C");
    EXPECT_STREQ(test_F.c_str(), "B");
}

TEST(Test_Automata, FSM_Basic_B)
{
    Yolk::Automata::State<std::string> A("A");
    Yolk::Automata::State<std::string> B("B");
    Yolk::Automata::State<std::string> C("C");

    Yolk::Automata::FSM<std::string, int> fsm(A);
    fsm.push_rule(A, 1, B);
    fsm.push_rule(B, 1, C);
    fsm.push_rule(C, 1, A);
    std::string test_A = fsm(1)();
    fsm.SetState(A);
    fsm.remove_rule(A, 1);
    std::string test_B = fsm(1)();
    fsm.push_rule(A, 0, C);
    std::string test_C = fsm(0)();
    fsm.SetState(A);
    fsm.push_rule(A, 1, B, true);
    std::string test_D = fsm(1)();
    
    EXPECT_STREQ(test_A.c_str(), "B");
    EXPECT_STREQ(test_B.c_str(), "A");
    EXPECT_STREQ(test_C.c_str(), "C");
    EXPECT_STREQ(test_D.c_str(), "B");
}

std::string Print(std::vector<Yolk::Automata::State<std::string>> values)
{
    std::string o = "";
    for(auto& v : values)
    {
        o += v();
    }
    return o;
}
TEST(Test_Automata, NFA_Basic_A)
{
    Yolk::Automata::State<std::string> A("A");
    Yolk::Automata::State<std::string> B("B");
    Yolk::Automata::State<std::string> C("C");
    Yolk::Automata::State<std::string> D("D");
    Yolk::Automata::NFA<std::string, int> nfa(A);

    nfa.push_rule(A, 0, B);
    nfa.push_rule(A, 0, C);
    nfa.push_rule(B, 1, C);
    nfa.push_rule(C, 1, D);
    nfa.push_rule(D, 0, B);

    std::string test_A = Print(nfa()); // A
    std::string test_B = Print(nfa(0)); // A -> B | A -> C = B C
    std::string test_C = Print(nfa(1, 1)); // B -> C -> D | C -> D ->   =  D
    nfa << 0 << 1 << 1;  // D -> B -> C -> D =  D
    std::string test_D = Print(nfa());

    EXPECT_STREQ(test_A.c_str(), "A");
    EXPECT_STREQ(test_B.c_str(), "BC");
    EXPECT_STREQ(test_C.c_str(), "D");
    EXPECT_STREQ(test_D.c_str(), "D");
}

TEST(Test_Automata, NFA_Basic_B)
{

    Yolk::Automata::State<std::string> A("A");
    Yolk::Automata::State<std::string> B("B");
    Yolk::Automata::State<std::string> C("C");
    Yolk::Automata::State<std::string> D("D");
    Yolk::Automata::NFA<std::string, int> nfa(A);

    nfa.push_rule(A, 0, B);
    nfa.push_rule(A, 0, C);
    nfa.push_rule(B, 1, C);
    nfa.push_rule(C, 1, D);
    nfa.push_rule(D, 0, B);

    nfa(0); // A -> B | A -> C = B C
    nfa.SetState({A, B, C, D}); // A B C D
    std::string test_A = Print(nfa(0, 0)); // A -> B -> X | A -> C -> X | C -> X | D -> B -> X = X
    nfa.push_rule(A, 0, D);
    nfa.SetState(A);
    nfa << 0; // A -> B | A -> C | A-> D
    std::string test_B = Print(nfa());

    EXPECT_STREQ(test_A.c_str(), "");
    EXPECT_STREQ(test_B.c_str(), "BCD");

}
TEST(Test_Automata, NFA_Basic_C)
{

    Yolk::Automata::State<std::string> A("A");
    Yolk::Automata::State<std::string> B("B");
    Yolk::Automata::NFA<std::string, int> nfa(A);

    nfa.push_rule(A, 1, B);
    nfa << 1;
    auto result = nfa().at(0);
    EXPECT_STREQ(result().c_str(), "B");

}
TEST(Test_Automata, FSM_Exception)
{
    Yolk::Automata::State<> Start(0);
    Yolk::Automata::State<> FORSTATE(1);
    Yolk::Automata::State<> ARG1(2);
    Yolk::Automata::State<> ARG2(3);
    Yolk::Automata::State<> ARG3(4);
    Yolk::Automata::State<> END(5);
    Yolk::Automata::State<> ERR(-1);

    Yolk::Automata::FSM<int, std::string> for_parser(Start);

    std::string FOR = "for";
    std::string LP = "(";
    std::string RP = ")";
    std::string COL = ";";

    for_parser.push_rule(Start, FOR, FORSTATE);
    for_parser.push_exception(Start, ERR);
    
    for_parser.push_rule(FORSTATE, LP, ARG1);
    for_parser.push_exception(FORSTATE, ERR);
    
    for_parser.push_rule(ARG1, COL, ARG2);
    for_parser.push_exception(ARG1, ARG1);
    
    for_parser.push_rule(ARG2, COL, ARG3);
    for_parser.push_exception(ARG2, ARG2);
    
    for_parser.push_rule(ARG3, RP, END);
    for_parser.push_exception(ARG3, ARG3);

    for_parser << "for" << "(" << "int" << "i" << "=" << "0" << ";" << "i" << "<" << "10" << ";" << "i++" << ")";

    auto result = for_parser();

    EXPECT_EQ(result(), 5);
    
    for_parser.SetState(Start);
    for_parser << "for" << "(" << "int" << "i" << "=" << "0" << ";" << "i" << "<" << "10" << ":" << "i++" << ")"; // ; becomes : . Error. Should not parse

    auto result2 = for_parser();

    EXPECT_NE(result2(), 5);
}

int GetInput(char character)
{
    int letters(0);
    int quotes(2);
    int backslash(3);
    int numbers(4);
    int symbols(5);

    if(std::isdigit(character))
    {
        return numbers;
    }
    if(std::isalpha(character))
    {
        return letters;
    }
    if(character == '\"')
    {
        return quotes;
    }
    if(character == '\\')
    {
        return backslash;
    }
    return symbols;
}
void EvaluateTest(std::string input, char mode)
{
    if(mode == 0)
        EXPECT_STREQ(input.c_str(), "asdsd214");
    else if(mode == 1)
        EXPECT_STREQ(input.c_str(), "!=");
    else if(mode == 2)
        EXPECT_STREQ(input.c_str(), "9875");
    else if(mode == 3)
        EXPECT_STREQ(input.c_str(), " ");
    else if(mode == 4)
        EXPECT_STREQ(input.c_str(), "parser");
    else if(mode == 5)
        EXPECT_STREQ(input.c_str(), " != ");
    else if(mode == 6)
        EXPECT_STREQ(input.c_str(), "1234");
    else if(mode == 7)
        EXPECT_STREQ(input.c_str(), " ");
    else if(mode == 8)
        EXPECT_STREQ(input.c_str(), "and");
    else if(mode == 9)
        EXPECT_STREQ(input.c_str(), " ");
    else if(mode == 10)
        EXPECT_STREQ(input.c_str(), "there");
    else if(mode == 11)
        EXPECT_STREQ(input.c_str(), " ");
    else if(mode == 12) 
        EXPECT_STREQ(input.c_str(), "is");
    else if(mode == 13) 
        EXPECT_STREQ(input.c_str(), " ");
    else if(mode == 14) 
        EXPECT_STREQ(input.c_str(), "a");
    else if(mode == 15) 
        EXPECT_STREQ(input.c_str(), " ");
    else{
        std::cout << input.c_str() << std::endl;
        EXPECT_STREQ(input.c_str(), "\"quotes\\\" in here\"");
    }
}
TEST(Test_Automata, First_parser)
{
    Yolk::Automata::State<> Start(0, true);
    Yolk::Automata::State<> Sentences(1);
    Yolk::Automata::State<> Sentences_Helper(5);
    Yolk::Automata::State<> Sentences_End(6);
    Yolk::Automata::State<> Alphanumeric(2);
    Yolk::Automata::State<> Numeric(3);
    Yolk::Automata::State<> Symbolic(4);

    int letters(0);
    int quotes(2);
    int backslash(3);
    int numbers(4);
    int symbols(5);

    Yolk::Automata::FSM<int, int> parser(Start);

    parser.push_rule(Start, numbers, Numeric);
    parser.push_rule(Start, letters, Alphanumeric);
    parser.push_rule(Start, quotes, Sentences);
    parser.push_rule(Start, symbols, Symbolic);
    parser.push_rule(Start, backslash, Symbolic);

    parser.push_rule(Numeric, numbers, Numeric);
    parser.push_exception(Numeric, Start);

    parser.push_rule(Alphanumeric, numbers, Alphanumeric);
    parser.push_rule(Alphanumeric, letters, Alphanumeric);
    parser.push_exception(Alphanumeric, Start);

    parser.push_rule(Symbolic, symbols, Symbolic);
    parser.push_rule(Symbolic, backslash, Symbolic);
    parser.push_exception(Symbolic, Start);

    parser.push_rule(Sentences, quotes, Sentences_End);
    parser.push_rule(Sentences, backslash, Sentences_Helper);
    parser.push_exception(Sentences, Sentences);

    parser.push_exception(Sentences_Helper, Sentences);
    parser.push_exception(Sentences_End, Start);
    
    std::string input = "asdsd214!=9875 parser != 1234 and there is a \"quotes\\\" in here\"";  // asdsd214!=9875 parser != 1234 and there is a "quotes \" in here\""
                                                                                                // Should parse: 
                                                                                                //  asdsd214
                                                                                                //  !=
                                                                                                //  9875
                                                                                                //  parser
                                                                                                //  !=
                                                                                                //  1234
                                                                                                //  and
                                                                                                //  there
                                                                                                //  is
                                                                                                //  a
                                                                                                //  "quotes \"in here\""
    auto checkpoint = input.begin();
    int id = 0;
    for(auto it = input.begin(); it != input.end(); it++)
    {
        char current_char = *it;
        auto current_input = GetInput(current_char);
        parser(current_input);

        if(parser.Accepts())
        {
            std::string substring = std::string(checkpoint, it);
            EvaluateTest(substring, id);
            id++;
            
            checkpoint = it;
            it--;
        }
    }
}