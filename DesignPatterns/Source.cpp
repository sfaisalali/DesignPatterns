#include "pch.h"
#include "ChainOfResponsibilityPattern.h"
#include "TemplateMethodPattern.h"
#include "StrattegyPattern.h"
#include "StatePattern.h"
#include "ProxyPattern.h"
#include "ObserverPattern.h"
#include "NullObjectPattern.h"
#include "IteratorPattern.h"
#include "FacadePattern.h"
#include "DecoratorPattern.h"
#include "CompositePattern.h"
#include "CommandPattern.h"
#include "BuilderPattern.h"
#include "AdapterPatern.h"
#include "AbstractFactory.h"


void testChainOfresponsibility() {

    auto school = new School;
    auto college = new College;
    auto job = new Job;
    auto retire = new Retire;
    auto die = new Die;

    school->SetNext(college);
    college->SetNext(job);
    job->SetNext(retire);
    retire->SetNext(die);

    int arr[] = { 5,10,20,40,60,80 };
    for (auto i : arr)
    {
        school->ExecuteResponsibility(i);
    }
}

void testTemplatemethodpattern(){
    HookedAlgorithm alg;
    SomeEnhancer enhancer(alg);
    enhancer.EnhanceImage();
}

void testStrategyPattern(){
    SimpleFlyBehavior fly;
    CrazyDisplayBehavior displ;
    Bird simplebird(displ, fly);
    simplebird.Display();
    simplebird.fly();
}

void testStatePattern(){
    Context context(new OutDoor);
    context.Alert();
    context.Alert();
    context.SetState(new General);
    context.Alert();
    context.SetState(new Silent);
    context.Alert();
    context.Alert();
    context.SetState(new Vibrate);
    context.Alert();
}

void testProxyPattern(){
    Book book;
    ProxyBookParser parser(book);
    parser.getnopages();
}

void testObserverPattern(){
    WhetherStation station;
    auto obs1 = new TabView;
    station.Add(obs1);
    auto obs2 = new TreeView;
    station.Add(obs2);

    station.Notify();
    station.Remove(obs1);

    station.Notify();
}

void testNullObjectPattern(){
    Pages pages;
    auto page = pages.GetPage("Home");
    if (page->isNull())
        cout << page->getName() << " Not Found!\n";
    else
        cout << page->getName() << " Found!\n";
}

void testIteratorPattern(){
    Collection col;
    auto itr = col.GetIterator();
    while (itr->HasNext())
    {
        auto next = itr->Next();
        if (next != nullptr)
            next->Print();
    }
}

void testFacadePattern(){
    // Simple for the client 
    // no need to know the order or the 
    // dependencies among various subsystems.
    Order_Facade facade;
    facade.orderFood();
}

void testDecoratorPattern(){
    ConcreteClass obj;
    Decorator1 d1(obj);
    Decorator1 d2(d1);

    d2.FunctionA();
    d2.FunctionB();
}

void testCompositePattern(){
    vector< IToDo*> subItems = {
        new ToDoItem("First Item"),
        new ToDoItem("Second Item"),
        new CollectionOfToDoItems("Third Item", {
            new ToDoItem("First SubItem"),
            new ToDoItem("Second SubItem"),
            new ToDoItem("Third SubItem")
        }),
        new ToDoItem("Fourth Item")
    };
    CollectionOfToDoItems mainItem("SomeName", subItems);
    cout << mainItem.GetHtml();
}

void testCommandPattern(){
    Light light;
    LightONCommand onCommand(light);
    LightOFFCommand offCommand(light);
    Invoker invkr(onCommand, offCommand);
    invkr.ON();
    invkr.ON();
    invkr.OFF();
    invkr.UnDo();
    invkr.UnDo();
    invkr.UnDo();
    invkr.UnDo();
}

void testBuilderPattern(){
    Cook cook;
    auto tomashPizza = cook.build(new TomMashBuilder);
    tomashPizza.display();
    auto spicyPizza = cook.build(new SpicyAppleBuilder);
    spicyPizza.display();
}

void testAdapterPattern(){

    // Containment example
    Adaptee adaptee;
    AdapterContainment adapter(adaptee);
    adapter.Request();

    // Multiple inheritance example
    AdapterMultipleInheritance adapter1;
    adapter1.Request();
}


void DisplayTheme(ITheme* theme)
{
    theme->print();
    theme->GetButton()->print();
    theme->GetLabel()->print();
    theme->GetText()->print();
}
void testAbstractFactory(){
    DisplayTheme(new BlackTheme);
    DisplayTheme(new WhiteTheme);
}


int main() {
    testChainOfresponsibility();

    testTemplatemethodpattern();

    testStrategyPattern();

    testStatePattern();

    testProxyPattern();

    testObserverPattern();

    testNullObjectPattern();

    testIteratorPattern();

    testFacadePattern();

    testDecoratorPattern();

    testCompositePattern();

    testCommandPattern();

    testBuilderPattern();

    testAdapterPattern();

    testAbstractFactory();

    return 0;
}