#include<bits/stdc++.h>
using namespace std;
struct s_tree
{
	int data;
	s_tree *left,*right;
	int max;
	int min;
};
vector <int> arr;
s_tree* create_node()
{
	s_tree * newnode = new s_tree;
	newnode->left=NULL;
	newnode->right=NULL;
	//newnode->data=key;
	return newnode;
}
s_tree* construct(s_tree *root,int first,int last)
{
	root=create_node();
	if(first==last)
	{
		root->data=arr[first];
		root->max=arr[first];
		root->min=arr[first];
		
		return root;
	}
	root->left=construct(root->left,first,(first+last)/2);
	root->right=construct(root->right,(first+last)/2+1,last);
	root->data=root->left->data+root->right->data;

	root->max=max(root->left->max,root->right->max);
	root->min=min(root->left->min,root->right->min);
	return root;
}
void inorder(s_tree * root)
{
	if(!root)
		return;

	inorder(root->left);
	cout<<root->data<<endl;
	inorder(root->right);

}

int sum_query(s_tree * root,int first, int last, int l, int r)
{
	// if(first==l&&last==r)
	// 	return root->data;

	// if(first==last)
	// {
	// 	return root->data;
	// }
	// int mid=(first+last)/2;
	// if(r<=mid)
	// 	return sum_query(root->left,first,mid,l,r);
	// if(l>=mid)
	// 	return sum_query(root->right,mid+1,last,l,r);
	if(l>r)
		return 0;
	if(first==l&&last==r)
	{
		return root->data;
	}
	int mid=(first+last)/2;
	return sum_query(root->left,first,mid,l,min(mid,r))+sum_query(root->right,mid+1,last,max(l,mid+1),r);

}
void update_query(s_tree *root,int first,int last,int index,int key)
{
	root->data+=key;
	if(first==last)
	{
		root->max=arr[first];
		root->min=arr[first];
		return;
	}
	
	int mid=(first+last)/2;
	if(index<=mid)
	update_query(root->left,first,mid,index,key);
	if(index>mid)
		update_query(root->right,mid+1,last,index,key);

	root->max=max(root->left->max,root->right->max);
	root->min=min(root->left->min,root->right->min);


}
int max_query(s_tree *root,int first,int last,int l,int r)
{
	if(l>r)
		return INT_MIN;
	if(first==l&&last==r)
	{
		return root->max;
	}
	int mid=(first+last)/2;
	return max(max_query(root->left,first,mid,l,min(mid,r)),max_query(root->right,mid+1,last,max(l,mid+1),r));

}
int min_query(s_tree *root,int first,int last,int l,int r)
{
	if(l>r)
		return INT_MAX;ks behind, settles into punching it away through point
	if(first==l&&last==r)
	{
		return root->min;
	}
	int mid=(first+last)/2;
	return min(min_query(root->left,first,mid,l,min(mid,r)),min_query(root->right,mid+1,last,max(l,mid+1),r));

}
int main()
{
	s_tree * root=NULL;
	int n;
	cout<<"enter no. of nodes for segment tree"<<endl;
	cin>>n;
	cout<<"enter "<<n<<" elements"<<endl;
	for(int i=0;i<n;i++)
	{
		int temp;
		cin>>temp;
		arr.push_back(temp);
	}
	root=construct(root,0,n-1);
	while(1)
	{
		cout<<"\n1:sum query\n2:update_query\n3:traversal\n4:max_query\n5:min_query\n6:exit"<<endl;
		int num;
		cin>>num;
		if(num==1)
		{
			int l,r;
			cout<<"enter your range"<<endl;
			cin>>l>>r;
				if(l>r)
				{
					int temp=l;
					r=temp;
					l=r;				
				}
			cout<<sum_query(root,0,n-1,l,r)<<endl;
		}
		if(num==2)
		{
			cout<<"enter the index and update key"<<endl;
			int index,key;
			cin>>index>>key;
			int sum_key=key-arr[index];
			arr[index]=key;
			update_query(root,0,n-1,index,sum_key);
		}
		if(num==3)
		{
			inorder(root);
		}
		if(num==4)
		{
			int l,r;
			cout<<"enter your range"<<endl;
			cin>>l>>r;
				if(l>r)
				{
					int temp=l;
					r=temp;
					l=r;				
				}
			cout<<max_query(root,0,n-1,l,r)<<endl;
		}
		if(num==5)
		{
			int l,r;
			cout<<"enter your range"<<endl;
			cin>>l>>r;
				if(l>r)
				{
					int temp=l;
					r=temp;
					l=r;				
				}
			cout<<min_query(root,0,n-1,l,r)<<endl;	
		}
		if(num==6)
		{
			exit(0);
		}

	}
	return 0;
}