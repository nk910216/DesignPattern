#include<iostream>

using namespace std;

/*
 *  Desktop components : screen / keyboard / computer
 */
typedef struct Screen
{
    int width;
    int height;
    Screen(int w, int h)
    {
        width = w;
        height = h;
    }
}Screen;

typedef struct Keyboard
{
    int color;
    Keyboard(int c)
    {
        color = c;
    }
}Keyboard;

typedef struct Computer
{
    int core;
    Computer(int c)
    {
        core = c;
    }
}Computer;
/*
 * Desktop Factory : list of componenet that need to generate.
 */
class DesktopFactory
{
public:
    virtual Screen* GenerateScreen() const = 0;
    virtual Keyboard* GenerateKeyboard() const = 0;
    virtual Computer* GenerateComputer() const = 0;
};

class AppleFactory : public DesktopFactory
{
public:
    AppleFactory()
    {}
    Screen* GenerateScreen() const
    {
        return new Screen(4000, 4000);
    }

    Keyboard* GenerateKeyboard() const
    {
        return new Keyboard(256);
    }

    Computer* GenerateComputer() const
    {
        return new Computer(8);
    }
};

class SosoFactory : public DesktopFactory
{
public:
    Screen* GenerateScreen() const
    {
        return new Screen(2048, 2048);
    }
    
    Keyboard* GenerateKeyboard() const
    {
        return new Keyboard(7);
    }

    Computer* GenerateComputer() const
    {
        return new Computer(2);
    }
};

/*
 * Desktop Product
 */
typedef struct Desktop
{
    Screen *m_screen;
    Keyboard *m_keyboard;
    Computer *m_computer;
    Desktop()
    {
        m_screen = NULL;
        m_keyboard = NULL;
        m_computer = NULL;
    }

    Desktop(Screen *s, Keyboard *k, Computer *c)
    {
        m_screen = s;
        m_keyboard = k;
        m_computer = c;
    }

    ~Desktop()
    {
        if (m_screen)
        {
            delete m_screen;
            m_screen = NULL;
        }
        if (m_keyboard)
        {
            delete m_keyboard;
            m_keyboard = NULL;
        }
        if (m_computer)
        {
            delete m_computer;
            m_computer = NULL;
        }
    }

    void printInfo()
    {
        if (m_screen && m_keyboard && m_computer)
        {
            cout << "---------------------" << endl;
            cout << "screen resolution : " << m_screen->width << " x " << m_screen->height << endl;
            cout << "keyboard color number : " << m_keyboard->color << endl;
            cout << "computer core number : " << m_computer->core << endl;
            cout << "---------------------" << endl; 
        }
        else 
        {
            cout << "Some component is missing !!!" << endl;
        }
    }
}Desktop;

class DesktopProduct
{
public:
    virtual Desktop* GiveMeDesktop(DesktopFactory *factory) = 0;
};

class NormalProduct : public DesktopProduct
{
public:
    Desktop* GiveMeDesktop(DesktopFactory *factory)
    {
        Desktop *d = new Desktop(factory->GenerateScreen(),
                                 factory->GenerateKeyboard(),
                                 factory->GenerateComputer());
        return d;
    }
};

class SuperProduct : public DesktopProduct
{
public:
    Desktop* GiveMeDesktop(DesktopFactory *factory)
    {
        Desktop *d = new Desktop(factory->GenerateScreen(),
                                 factory->GenerateKeyboard(),
                                 factory->GenerateComputer());
        d->m_keyboard->color *= 2;
        d->m_computer->core *= 2; // black technology.
        return d;
    }
};

int main()
{
    AppleFactory apple_factory;
    SosoFactory soso_factory;

    NormalProduct normal_product;
    SuperProduct super_product;

    cout << "Apple factory + Apple product" << endl;
    Desktop* d1 = normal_product.GiveMeDesktop(&apple_factory);
    d1->printInfo();

    cout << "Apple factory + Super product" << endl;
    Desktop* d2 = super_product.GiveMeDesktop(&apple_factory);
    d2->printInfo();

    cout << "Soso factory + Normal product" << endl;
    Desktop* d3 = normal_product.GiveMeDesktop(&soso_factory);
    d3->printInfo();

    cout << "Soso factory + Super product" << endl;
    Desktop *d4 = super_product.GiveMeDesktop(&soso_factory);
    d4->printInfo();

    // release
    if (d1)
    {
        delete d1;
        d1 = NULL;
    }

    if (d2)
    {
        delete d2;
        d2 = NULL;
    }
    if (d3)
    {
        delete d3;
        d3 = NULL;
    }
    if (d4)
    {
        delete d4;
        d4 = NULL;
    }
    return 0;
}
