#include<iostream>
#include<list>
#include<set>
#include<vector>
#include<map>
#include<unordered_map>
#include<unordered_set>
using namespace std;
int main()
{

    /*list<int> lis={1,3,4,5,6,7,8,9,2,0};
    vector<int> vec={10, 11, 12, 13, 15};
    cout<<vec[3];
    vector<int>::reverse_iterator rit, ritb, rite;*/
    //ritb=vec.rbegin();
    //rie=vec.rend();

    //lis.insert(23);

    set<int> se=(1,2,3,4,5);
    set<int>::iterator st, stb, ste;
    stb=se.begin();
    ste=se.end();
    for(st=stb; st!=ste; st++)
        cout<<*st;
    multiset<int> fr=(1,11,2,22);
    fr.insert(9);

    map<char,int> mymap;
    mymap.insert(pair<char,int>('a', 100);


    return 0;

}
