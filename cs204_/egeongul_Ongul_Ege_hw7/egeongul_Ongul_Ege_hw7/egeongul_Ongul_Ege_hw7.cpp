/**Artrim Kjamilji, 20.12.2021**/

/*include all the necessary files, libraries, etc. here, if any*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*if you choose not to write the 5 required classes in seperate .h and .cpp files, then write them here*/

class shape{
public:
    shape(){};
    ~shape(){};
    virtual float perimeter() const = 0;
    virtual float area() const = 0;
    virtual float volume() const = 0;
    string getName(){
        return myname;
    };
    string myname;
    
};

class TwoDShape: public shape {
public:
    TwoDShape(){};
    ~TwoDShape(){};
    virtual float perimeter(int w, int l) const{
        return 2*(w + l);
    };
    virtual float area(int w, int l) const{
        return (w * l);
    };
    virtual float volume() const = 0;
};

class Rectangle: public TwoDShape{
public:
    Rectangle(){};
    ~Rectangle(){};
    float width;
    float length;
    virtual float volume() const{
        return 0;
    }
    virtual float perimeter() const{
        return 2*(width + length);
    }
    virtual float area() const{
        return (width*length);
    }
};

class ThreeDShape: public shape{
public:
    ThreeDShape(){};
    ~ThreeDShape(){};
    virtual float perimeter() const = 0;
    virtual float area(int w, int l, int h) const{
        return 2*(w * l + w * h + l * h);
    };
    virtual float volume(int w, int l, int h) const{
        return (w * l * h);
    };
};

class Box: public ThreeDShape{
public:
    Box(){};
    ~Box(){};
    float width;
    float length;
    float height;
    virtual float area() const{
        return 2*(width*length+width*height+length*height);
    }
    virtual float volume() const{
        return (width*length*height);
    }
    virtual float perimeter() const{
        return 0;
    }
};



shape* getShape() {
    float  width, length, height;
    int choice;
    string name;
    cout << "Choose an option <1 or 2> :" << endl;
    cout << "1. Rectangle\n2. Box" << endl;
    cin >> choice;
    while(choice != 1 && choice !=2){
        cout << "UNAVALIABLE OPTION CHOSEN. Please try again." << endl;
        cout << "Choose an option <1 or 2> :" << endl;
        cout << "1. Rectangle\n2. Box" << endl;
        cin >> choice;
    }
    if (choice == 1){
        cout << "You chose rectangle. Give it's width, length and name: " << endl;
        cin >> width >> length >> name;
        Rectangle *rect1 = new Rectangle();
        rect1->length = length;
        rect1->width = width;
        rect1->myname = name;
        return rect1;
    }
    else{
        cout << "You chose box. Give it's width, length, height and name: " << endl;
        cin >> width >> length >> height >> name;
        Box *box = new Box();
        box->width = width;
        box->length = length;
        box->height = height;
        box->myname = name;
        return box;
    }
}


int main()
{
    cout<<"WELCOME TO THE SHAPE COMPARISONN PROGRAM"<<endl;
    cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
    shape *shape_1, *shape_2; /* define two varibles, named shape_1 and shape_2 of the class shape.*/
    /*What should they be in order to enable proper polymorphism?*/
    char c;
    while (tolower(c = getchar())!='y')
    {
        cout<<"Defining (getting) shape 1..."<<endl;
        
        shape_1 = getShape();
        cout<<"Defining (getting) shape 2..."<<endl;
        shape_2 = getShape();
        cout<<"********************************************************************"<<endl;
        cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "
            <<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
        cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "
            <<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;
        bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
        if(shape_1->perimeter()==shape_2->perimeter())
        {
            nothingInCommon = false;
            cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "
                <<shape_1->perimeter()<<" cm."<<endl;
        }
        if(shape_1->area()==shape_2->area())
        {
            nothingInCommon = false;
            cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "
                <<shape_1->area()<<" cm^2."<<endl;
        }
        if(shape_1->volume()==shape_2->volume())
        {
            nothingInCommon = false;
            cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "
                <<shape_1->volume()<<" cm^3."<<endl;
        }
        if (nothingInCommon)
            cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;
        cout<<"********************************************************************"<<endl;
        cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
        cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
      }//while(tolower(c = getchar())!='y')
    cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
    system("pause");
    return 0;
}
