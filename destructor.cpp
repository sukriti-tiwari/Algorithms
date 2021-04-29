#include<iostream>
using namespace std;
class box
{
    float length, breadth, height;
    public:
    box(float l, float b, float h)
    {
        length=l;
        breadth=b;
        height=h;
    }
    float operator +(box ob1)
    {
        box temp;
        temp.length=length+ob1.length;
        temp.breadth=breadth+ob1.breadth;
        temp.height=height+ob1.height;
        return box(length, breadth, height);
    }
    float cal_vol(float l, float b, float h)
    {
        return (l*b*h);
    }
    disp()
    {
        cout<<"Volume = "<<vol;
    }
};

int main()
{
    box ob2(14.3, 5.5, 8.7);

}
