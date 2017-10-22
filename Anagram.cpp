//Character Deletion in two strings to make them anagram


#include <iostream>
#include<ctype.h>
using namespace std;
 
int main()
{
    int t,count=0,same=0;
    cin>>t;
    while(t>0)
    {
        string a,b;
        cin>>a>>b;
        int aa[26]={0},bb[26]={0};
        int count=0;
        
        for(int i=0;i<a.length();i++)
        {
            a[i]=tolower(a[i]);
            aa[a[i]-97]++;
        }
        for(int i=0;i<b.length();i++)
        {
            b[i]=tolower(b[i]);
            bb[b[i]-97]++;
        }
        for(int i=0;i<26;i++)
        {
            count+=abs(aa[i]-bb[i]);
        }
        cout<<count;
        cout<<endl;
        t--;
    }
    return 0;
}