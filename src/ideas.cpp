#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <math.h>
#include "Yolk/Yolk/TypedMethod.h"

decltype(std::placeholders::_10) a;

#define RegisterMethod(Class, Name) \
    Register _##Name = Register( std::bind(&Class::Name, this ))

class Object{};

class Register
{
    public:
    template<typename T>
    Register(T func)
    {
        f = func;
    }
    std::function<void(void)> f;

};

template <int placeholders, typename Method, typename CallerType, typename... Args>
struct Registrant
{
    static void Register(Object* objCaller, CallerType* caller, Method method, Args... rest)
    {
        return Registrant<placeholders - 1, Method, CallerType, Args...>::Register(objCaller, caller, method, rest..., std::_Placeholder<placeholders>());
    }
};
template <typename Method, typename CallerType, typename... Args>
struct Registrant<0, Method, CallerType, Args...>
{
    static void Register(Object* objCaller, CallerType* caller, Method method, Args... rest)
    {
        auto helper = std::bind(method, caller, rest...);
    }
};


class A : public Object
{
    public:
    A(int _a) : a(_a){}
    int Print()
    {
        std::cout << a << ": Hello World!\n";
        return -12;
    }
    RegisterMethod(A, Print);

    void Test()
    {
        Registrant<1, int(A::*)(), A>::Register(this, this, &A::Print);
    }
    int a;
};

int main()
{

    A a(15);
    
    int out;
    Yolk::TypedVariable o = out;
    Yolk::TypedParameter p;

    std::cout << out << std::endl;

}
    /*
    Let's Chill out a little bit!

    This is NOT a scripting language.

    This is not Python.

    This is not C, or Java.

    This is primarily, just a way to control C++ structures dynamically.

    What we need to be able to do:
        -> Register Methods we can call dynamically
        -> Register fields we can control dynamically

    Not every constructor needs to be accessible from within.

    With that in mind:

    All we need to do is make sure that RegisterField( Field ) is recursive when the Field is an object.

    That is ALL.

    Maybe later on I'll build an actual scripting language which will be AWESOME. And since it won't have to communicate with C+, i won't have to deal
    with bullshit abstract objects. I'll just create them in the language itself.

    But for now: This is only, merely, a way to control C++ objects dynamically.

    No need for fancy language stuff.

    We can register Methods and register Fields onto a Memory Block.

    This memory block contains: 
    
        A link to a Memory Manager, where everything is stored:
        A Reference Table, with an id -> { Information about id} Map
        A Name table, with a name -> reference table id Map
        A Wrapper Pointer Array.

    Every child of Yolk::Object that is instantiated has it's own Memory Block.

    When code runs on the scripting language, the memory block is passed as reference to an evaluator:
    This evaluator runs the code itself.

    Sometimes, one may wish to control the memory block of other objects from within a class.

    You can do this!

    The memory block contains a list of pointers to other Memory Blocks.

    So for example, if i have this:

        Global::Print()

    First the interpreter will read parse: Global::Print and identify Global as an object.
    Then interpreter will search the Name table for the key: "_OBJECT_Global"
    The interpreter will find the ID in the reference table.
    It will search the information in the reference table and make sure that it is an actual object. 
    More importantly, it will get the Wrapper ID of the object.
    It will go through the Wrapper array and find the Wrapper Pointer.
    Cast this Wrapper Pointer into an Object Wrapper Global.
    Execute Global.Execute("Print()") and return the output.

    Note that: Since we are invoking Execute on another class, we could have defined Print to be private in Global. Then the function Execute
    will simply check that and return an error.

    Otherwise, it will return a new Wrapper, which we can store accordingly if we so desired.


    Let's see something more simple.

    This is executed:

    Health = Health + 10.



*/

template<typename Out, typename... In>
struct DemoA
{
    DemoA(std::function<Out(In...)> func)
    {
        func(3);
    }
};

class Example
{
    int F(int x)
    {
        std::cout << "F: " << x << std::endl;
        return x;
    }

    DemoA<int, int> a = DemoA<int, int>( std::bind(&Example::F, this, std::placeholders::_1 ));
    DemoA<int, int> b = DemoA<int, int>( [this](int _1){ return this->F(_1);} );
};
void marx()
{
    std::cout << "This is a void void func!\n";
}

template <typename T, typename... F>
struct Helper
{
    static std::function<T(F...)> GetFunction(std::function<T(F...)> _input)
    {
        return _input;
    }
};
Yolk::Wrapper::Pointer New(Yolk::Memory::MemoryManager& manager)
{
    auto i = manager.AllocateMemory<int>(14);
    Yolk::Wrapper::Pointer o = std::make_shared<Yolk::Wrapper>(i);
    return o;
}


class RequiredClass
{
    public:
    RequiredClass(int x) : a(x) {}
    void Test()
    {
        std::cout << a << " Hello!\n";
    }
    private:
    int a;
    RequiredClass(){}
};

class Object
{
    public:
    Object(Object& _Father) : Father(_Father), Mode("Child"), required(_Father.required) {}

    void Print()
    {
        std::cout << Mode << std::endl;
        required.Test();
    }
    std::string Mode;
    Object& Father;

    RequiredClass& required;

    protected:
    Object(RequiredClass& _required) : Father(*this), Mode("God"), required(_required) {}
};

class God : public Object
{
    public:
    God() : r(12), Object(r) { }

    RequiredClass r;
};

#include <iostream>
#include "Krill/Window/GLFWHandler.h"

int main()
{
    Krill::Window::GLFWHandler::GLFWHandlerOptions options;
    Krill::Window::GLFWHandler glfwHandler(options, [](std::string in){std::cout << in << std::endl;});
    
    glfwHandler.InitializeGLFW();
    glfwHandler.InitializeWindow();

    while(!glfwWindowShouldClose(glfwHandler.GetWindow()))
    {
        glfwHandler.Loop();
        if(glfwGetKey(glfwHandler.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(glfwHandler.GetWindow(), true);
        }
        if(glfwGetKey(glfwHandler.GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
        {
            glfwHandler.TerminateWindow();
            glfwHandler.options.WindowHeight += 50;
            glfwHandler.InitializeWindow();
        }
        if(glfwGetKey(glfwHandler.GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            glfwHandler.TerminateWindow();
            glfwHandler.options.WindowHeight -= 50;
            glfwHandler.InitializeWindow();
        }
        if(glfwGetKey(glfwHandler.GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            glfwHandler.TerminateWindow();
            glfwHandler.options.WindowWidth += 50;
            glfwHandler.InitializeWindow();
        }
        if(glfwGetKey(glfwHandler.GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            glfwHandler.TerminateWindow();
            glfwHandler.options.WindowWidth -= 50;
            glfwHandler.InitializeWindow();
        }
    }
}

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



/*
The new Memory Block needs to be:

    Compatible with the Old Memory Block.
    Forget about privacy stuff.
    Extendable horizontally:
        When one registers an object, what one actually does is extend the memory block horizontally.
        It contains several maps to other memory blocks, each with an assigned name.
    Extendable vertically:
        One can branch the memory block, generating another one with the same entries. Modifying an entry which were in the original memory block should affect the original one, however, adding new should not add to the original one.

    
    Example:

    MemoryBlock memoryBlock;
    memoryBlock.RegisterField("Health", HealthField);

    memoryBlock.Link(Enemy.memoryBlock);

    memoryBlock.GetFieldWrapper("Enemy::Health");  // Works!

    memoryBlock.Unlink(Enemy.memoryBlock);

    memoryBlock.GetFieldWrapper("Enemy::Health"); // Fails!

    MemoryBlock newBlock = memoryBlock.Branch();

    newBlock.GetFieldWrapper("Health").field->Copy(121); // Workd! Health is now 121

    newBlock.RegisterField("Status", Status);

    memoryBlock.GetFieldWrapper("Status"); // Fails!

    newBlock.Father.RegisterField("OP", OP);

    memoryBlock.GetFieldWrapper("OP"); // Works!

    newBlock.Destroy();


    How to do this:

    It's gonna be a huge, tremendous pain the ass, but....

    There is no reason why every object should have it's own Wrapper table.

    There should be only one Wrapper table, mantained by the Environment.

    A Memory Block should contain:
        It's own Symbol Table
        Maps to other Symbol Tables.

    With this, the YVM, would work the following way:

    When an object Object asks for something to be executed:

    YVM Branches the Objects Memory Block.

    Every time a { } clause is encountered, the Memory Block Branches downwards. When the code exits the branch, the Memory Block branches upwards again.

    Perhaps, branching should not create a new Memory Block.

    So... YVM Copies the Objects Memory Block.

    Branching downwards means setting a variable

    level = level + 1;

    And then every time you register a wrapper, it is registered under that level.

    Branching upwawrds means deleting every wrapper at level level, and doing level = level - 1;

    This is definitely safer.


*/