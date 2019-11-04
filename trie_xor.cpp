#include<bits/stdc++.h>
using namespace std;
#define nbits 32
struct trie
{
    int data;
    trie * left;
    trie * right;
};
trie * create_node()
{
    trie * newnode= new trie;
    newnode->right=NULL;
    newnode->left=NULL;

    return newnode;
}
int powerr(int x,int n) {
    if(n==0)
        return 1;
    int smaintAns = powerr(x, n/2);
    if(n % 2 == 0)
        return (smaintAns * smaintAns);
    return (x * (smaintAns * smaintAns));
}
trie * insert(trie * root,vector <int> &b,int bcount,int inx)
{
    //cout<<"inx="<<inx<<" bcount="<<bcount<<endl;

    if(!root)
    {
        root=create_node();
        if(bcount==inx)
        {
            root->data=b[inx-1];
            return root;
        }
    }
    if(inx==bcount)
    {
      root->data=b[inx-1];
            return root;   
    }
    if(b[inx]==1)
        root->right=insert(root->right,b,bcount,inx+1);
    else
        root->left=insert(root->left,b,bcount,inx+1);
    if(inx>0)
    root->data=b[inx-1];
    return root;
}
trie * per_insert(trie * root,vector <int> &b,int bcount,int inx)
{
    trie * temp=create_node();
    if(!root)
    {
    
        if(bcount==inx)
        {
            temp->data=b[inx-1];
            return temp;
        }
        if(b[inx]==0)
            {
                temp->left=insert(temp->left,b,bcount,inx+1);
            }
            else
                {
                    temp->right=insert(temp->right,b,bcount,inx+1);
                }
            return temp;

    }
    if(inx==bcount)
    {
        temp->data=b[inx-1];
            return temp;   
    }
    if(b[inx]==1)
        {
            temp->left=root->left;
            temp->right=per_insert(root->right,b,bcount,inx+1);

        }
    else
        {
            temp->right=root->right;
            temp->left=per_insert(root->left,b,bcount,inx+1);
        }
   if(inx>0)
    temp->data=b[inx-1];
    return temp;
}
bool search(trie * root,vector <int> &b,int bcount,int inx)
{
    if(!root)
        return false;

    if(inx>0&&root->data!=b[inx-1])
        return false;
    if(inx==bcount)
    {
        return true;
    }
    if(b[inx]==0)
    {
        return search(root->left,b,bcount,inx+1);
        
    }
    else
    {
        return search(root->right,b,bcount,inx+1);
    }
}
void traversal(trie * root)
{
    if(!root)
    return ;
    
    traversal(root->left);
    cout<<"data="<<root->data<<endl;
    traversal(root->right);
    
    
}
int cal_xor(trie * root,vector <int > &b, int bcount,int inx,int ans)
{
    if(bcount==0)
    {
        ans=ans+powerr(2,bcount)*root->data;
        //cout<<ans<<endl;
        return ans; 
    }
    if(b[inx]==0)
    {
        if(root->right)
        ans=cal_xor(root->right,b ,bcount-1,inx+1,ans);
        else
        ans=cal_xor(root->left,b,bcount-1,inx+1,ans);
    }
    else 
    {
        if(root->left)
        ans=cal_xor(root->left,b,bcount-1,inx+1,ans);
        else
        ans=cal_xor(root->right,b,bcount-1,inx+1,ans);
    }

    ans=ans+powerr(2,bcount)*root->data;
        //cout<<ans<<endl;
        return ans; 
        
}
int countbits(unsigned int n) 
{ 
   int count = 0; 
   while (n) 
   { 
        count++; 
        n >>= 1; 
    } 
    return count; 
} 
int main()
 {
    cout<<"enter no of elements:\n";
     int n;
     int q;
     cin>>n;
     // cin>>q;
     trie * root=NULL;
     trie * latest;
    vector <trie *> per;

    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        int bcount=countbits(x);

        vector<int> b(nbits,0);
        int temp=x;
        int zeroes=nbits-bcount;
        //cout<<"zeroes="<<zeroes<<endl;
        for(int i=nbits-1;i>=zeroes;i--)
        {
            b[i]=temp&1;
            temp=temp>>1;
        }        

        // for(int i=0;i<nbits;i++)
        //     cout<<b[i]<<endl;
        // cout<<"end"<<endl;
        int inx=0;
        root=insert(root,b,nbits,inx);
        traversal(root);
        b.clear();
    }
    int version=0;
    per.push_back(root);
    
    
    while(1)
    {
    latest=per[version];
    int ch;
    cout<<"1:insert element with persistency\n2:max xor\n3:search element\n4:traversal\n5:exit\n"<<endl;
    cin>>ch;
   if(ch==1)
   {
        int x;
        cin>>x;
        int bcount=countbits(x);

        vector<int> b(nbits,0);
        int temp=x;
        int zeroes=nbits-bcount;
        //cout<<"zeroes="<<zeroes<<endl;
        for(int i=nbits-1;i>=zeroes;i--)
        {
            b[i]=temp&1;
            temp=temp>>1;
        }        

        // for(int i=0;i<nbits;i++)
        //     cout<<b[i]<<endl;
        // cout<<"end"<<endl;
        int inx=0;
        root=per_insert(root,b,nbits,inx);
        traversal(root);
        per.push_back(root);
        version++;
        b.clear();
   }
   if(ch==2)
    {
        int x;
        cout<<"enter the query"<<endl;
        cin>>x;
        cout<<"enter the version : Availaible versions\n"<<endl;
            int i;
            for(i=0;i<version;i++)
            {
                cout<<i<<": "<<endl;
            }
            cout<<i<<":(latest)"<<endl;
            int v;
            cin>>v;
        int bcount=countbits(x);
        vector<int> b(nbits,0);
        int temp=x;
        int zeroes=nbits-bcount;
        //cout<<"zeroes="<<zeroes<<endl;
        for(int i=nbits-1;i>=zeroes;i--)
        {
            b[i]=temp&1;
            temp=temp>>1;
        }          
        cout<<(x^cal_xor(per[v],b,nbits,0,0))<<endl;
        b.clear();
    }
    if(ch==3)
    {
        int x;
        cin>>x;
        int bcount=countbits(x);

        vector<int> b(nbits,0);
        int temp=x;
        int zeroes=nbits-bcount;
        //cout<<"zeroes="<<zeroes<<endl;
        for(int i=nbits-1;i>=zeroes;i--)
        {
            b[i]=temp&1;
            temp=temp>>1;
        }        

        // for(int i=0;i<nbits;i++)
        //     cout<<b[i]<<endl;
        // cout<<"end"<<endl;
        cout<<"enter the version : Availaible versions\n"<<endl;
            int i;
            for(i=0;i<version;i++)
            {
               cout<<i<<": "<<endl;
                cout<<endl;
            }
            cout<<i<<":(latest)"<<endl;
            int v;
            cin>>v;
       int inx=0;
       bool result=search(per[v],b,nbits,inx);
       if(result)
        cout<<"element exist"<<endl;
       else
        cout<<"element does not exist"<<endl;
    }
    if(ch==4)
    {
         cout<<"enter the version : Availaible versions\n"<<endl;
            int i;
            for(i=0;i<=version;i++)
            {
               cout<<i<<": "<<endl;
                cout<<endl;
            }
            cout<<i<<":(latest)"<<endl;
            int v;
            cin>>v;
            traversal(per[v]);
    }
    if(ch==5)
    {
        exit(0);
    }

}
    
    return 0;
}
