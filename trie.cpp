#include<bits/stdc++.h>
 
using namespace std;
struct trie
{
	int data;
	trie * left;
	trie * right;
	bool flag;
};
trie * create_node()
{
	trie * newnode= new trie;
	newnode->right=NULL;
	newnode->left=NULL;
}

trie * insert(trie * root,vector <int> b,int bcount,int inx)
{

	if(!root)
	{
		root=create_node();
		root->data=b[inx-1];
		//cout<<root->data<<endl;
		if(inx==bcount)
			{
				root->flag=true;
				return root;
			}
	}
	if(inx==bcount)
			{
				root->flag=true;
				return root;
			}
	if(b[inx]==1)
		root->right=insert(root->right,b,bcount,inx+1);
	else
		root->left=insert(root->left,b,bcount,inx+1);
	return root;
}
trie * per_insert(trie * root,vector<int> b,int bcount,int inx)
{

	trie * temp=create_node();
	if(!root)
	{
		
		temp->data=b[inx-1];

		//cout<<root->data<<endl;
		if(inx==bcount)
			{
				temp->flag=true;
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
				temp->flag=true;
				temp->right=root->right;
				temp->left=root->left; 
				return temp;
			}
	//cout<<"data="<<root->data;
			if(inx==bcount)
			{
				temp->flag=true;
				return root;
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
		temp->flag=root->flag;
		temp->data=root->data;
	return temp;
}
bool search(trie * root,vector <int> b,int bcount,int inx)
{
	if(!root)
		return false;
	if(root->data!=b[inx-1])
		return false;
	if(inx==bcount)
	{
		if(root->flag==true)
			return true;
		else
			return false;

	}
	if(b[inx]==0)
    {
        return search(root->left,b,bcount,inx+1);
        
    }
    else
    {
        return search(root->right,b,bcount,inx+1);
    }

   	return true;
	
}
void inorder(trie * root)
{
	if(!root)
		return ;
	
	inorder(root->left);
	cout<<"data="<<root->data<<" flag="<<root->flag<<endl;
	inorder(root->right);	
}

int main()
 {
	int n;
	cout<<"enter no. of elements to be inserted"<<endl;
	cin>>n;
	trie * root=NULL;
	trie * latest;
	 vector <trie *> per;
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>x;
		int bcount=(int)log2(x)+1;	

		vector<int> b(bcount);
		int temp=x;
		for(int i=bcount-1;i>=0;i--)
		{
			b[i]=temp&1;
			temp=temp>>1;
		}
		// for(int i=0;i<bcount;i++)
		// 	cout<<b[i]<<endl;
		// cout<<"end"<<endl;
		int inx=0;
		root=insert(root,b,bcount,inx+1);
		b.clear();
		inorder(root);

	}
	
		 int version=0;
		 per.push_back(root);
	while(1)
	{
		latest=per[version];
    	cout<<"1:insert element with persistency\n2:search element\n3:traversal\n4:exit\n"<<endl;
		int ch;
		cin>>ch;
		if(ch==1)
		{
			int x;
			cin>>x;
			int bcount=(int)log2(x)+1;

			vector<int> b(bcount);
			int temp=x;
			for(int i=bcount-1;i>=0;i--)
			{
				b[i]=temp&1;
				temp=temp>>1;
			}
			// for(int i=0;i<bcount;i++)
			// 	cout<<b[i]<<endl;
			// cout<<"end"<<endl;
			int inx=0;
			root=per_insert(root,b,bcount,inx+1);
			inorder(root);
			per.push_back(root);
			version++;
			b.clear();
				
		}
		if(ch==2)
		{
			int x;
			cin>>x;
			int bcount=(int)log2(x)+1;

			vector<int> b(bcount);
			int temp=x;
			for(int i=bcount-1;i>=0;i--)
			{
				b[i]=temp&1;
				temp=temp>>1;
			}
			cout<<"enter the version : Availaible versions\n"<<endl;
				int i;
				for(i=0;i<version;i++)
				{
					cout<<i<<": "<<endl;
				}
				cout<<i<<":(latest)"<<endl;
				int v;
				cin>>v;
			int inx=0;
			bool result=search(per[v],b,bcount,inx+1);
			if(result)
	        cout<<"element exist"<<endl;
	       	else
	        cout<<"element does not exist"<<endl;
		}
		if(ch==3)
		{
			cout<<"enter the version : Availaible versions\n"<<endl;
				int i;
				for(i=0;i<version;i++)
				{
					cout<<i<<": "<<endl;
				}
				cout<<i<<":(latest)"<<endl;
				int v;
				cin>>v;
				inorder(per[v]);	
		}
		if(ch==4)
		{
			exit(0);
		}
	}
	
	// cout<<"enter the key";
	// ll x;
	// 	cin>>x;
	// 	ll bcount=(ll)log2(x)+1;

	// 	vector<ll> b(bcount);
	// 	ll temp=x;
	// 	for(ll i=bcount-1;i>=0;i--)
	// 	{
	// 		b[i]=temp&1;
	// 		temp=temp>>1;
	// 	}
	// 	ll inx=0;
		
		
	
	return 0;
}