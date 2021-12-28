#include "src/Yolk/Yolk.h"
#include <unordered_map>
#include <map>
#include <typeindex>
#include <cstring>
#include <cstddef>

int FunctionTest(int a, float b)
{
    int o = a + (int)b;
    return o;
}
int main()
{
    Yolk::Memory::MemoryManager manager;

    auto w1 = manager.AllocateMemory<int>(7);      // <---- This is on Memory Block
    auto w2 = manager.AllocateMemory<float>(12.1);//  <---- This is also on Memory Block

    // Problem: How to change reg such that w1 now points to the same piece of data as w2?
    // I could make w1 = w2, but YVM is a register based machine. It can't directly touch w1 or w2

    // Alternative 1: Erase w1 from memory. Copy w2 to reg. Store reg on memory with the same name as w1.

    // Alternative 2? Why is this necessary? References should be a different type than normal variables. This makes no sense.
    // 
    // Extending on this:
    // Perhaps a reference should be defined as:
    // var& reference = Variable;
    //
    // How is this coded? 
    //
    // Like this:

    // Okay! Do we support pointers then? What happens if we want a reference to point to another variable. For example:
    // var& reference = &w1;
    // reference = 12; // Changes the value of w1,
    // reference = &w2; // Reference now points to w2
    // reference = 13; // w1 = 12 but w2 = 13;
    // Let's just not do this.
    // It's too complicated.
    // For now, simple basic variables and references should work fine.
    // Why would we even need pointers.
    //
    // Summarizing:
    // var& a = w1;          Translates to:
    // 
    // REGA = manager.CopyByReference(w1);
    // memblock.RegisterFieldByName("a", REGA);
    //
    // Which is written in Assembly as:
    //
    // mov REGA, w1
    // NAMEL REGA, "a"
    //
    //
    // var a = w1;           Translates to:
    //
    // REGA = manager.CopyByValue(w1);
    // memblock.RegisterFieldByName("a", REGA);
    //
    // Which is written in Assembly as:
    //
    // clone REGA, w1
    // NAMEL REGA, "a"
    //
    //
    // var a : int;
    // a = w1;          Translates to:
    //
    // REGA = manager.AllocateMemory<int>();
    // memblock.RegisterFieldByName("a", REGA);
    // REGA = memblock.GetFieldByName("a");
    // REGA.field->Copy(*w1.field);
    //
    //
    // Which is written in Assembly as:
    // 
    // set REGA, INT
    // namel REGA, "a"
    // mov REGA, "a"
    // copy REGA, w1
    //
    //
    //
    // We have used the following instructions for this:
    //
    // mov, clone, set, namel, copy, 
    //
    //
    // var x = w1 as float;
    // Translates to:
    //
    // mov REGA, w1
    // cast REGA, float
    // namel REGA, "x"



}
