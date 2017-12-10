/*
               Computational Geometry Assignment 1 
			   (29/01/2017)
			   Submitted by :
			   Avijit Verma
			   14CS01043
*/

#include<iostream>		
#include<algorithm>
#include<vector>
#include<cmath>
#define P pair<float,float>
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define ccw(A,B,C) ((B.X-A.X)*(C.Y-A.Y)-(B.Y-A.Y)*(C.X-A.X))
#define fr(i,n) for(int i=0;i<n;++i)


using namespace std;

bool compare(P A,P B)
{
	if(A.X<B.X)
		return true;
	else if(A.X==B.X && A.Y<B.Y)
		return true;
	else	
		return false;
}
void conv_hull(vector<P> & points, vector<P> & hull)
{
	hull.pb(points[0]);
	hull.pb(points[1]);
	for(int i=2;i<points.size();++i)
	{
		while(hull.size()>2&&ccw(hull[hull.size()-2],hull[hull.size()-1],points[i])>=0)
		{
			hull.pop_back();
		}
        if(ccw(hull[hull.size()-2],hull[hull.size()-1],points[i])>=0)
            hull.pop_back();
		hull.pb(points[i]);
	}
	int half_size = hull.size();
	hull.pb(points[points.size()-2]);
	for(int i=points.size()-3;i>=0;--i)
	{
		while(hull.size()>half_size+1&&ccw(hull[hull.size()-2],hull[hull.size()-1],points[i])>=0)
		{
			hull.pop_back();
		}
        if(ccw(hull[hull.size()-2],hull[hull.size()-1],points[i])>=0)
            hull.pop_back();
		hull.pb(points[i]);
	}
}																																
																																				
void get_halves(vector<P> &A,vector<P> &up,vector<P> &lo)
{
	int i=0;
	while(i<A.size()&&A[i].X<=A[i+1].X)
	{
		up.pb(A[i]);
		i++;
	}
	if(i==A.size())
	{
		return ;
	}
	up.pb(A[i]);
	int j=A.size()-2;
	while(j>i)
	{
		lo.pb(A[j--]);
		
	}

}
void merge(vector<P> &up,vector<P> &lo,vector<P> &ans)
{
	int i,j;
	i=j=0;
	while(i<up.size()&&j<lo.size())
	{
		if(compare(up[i],lo[j]))
		{
			ans.pb(up[i]);
		
			i++;
		}
		else
		{
			ans.pb(lo[j++]);
		}
	}
	while(i<up.size())
	{
		ans.pb(up[i++]);
	}
	while(j<lo.size())
		ans.pb(lo[j++]);
}
void print(vector<P> a)
{
for(int i=0;i<a.size();++i)
	cout<<'('<<a[i].X<<','<<a[i].Y<<") ";
cout<<endl;
}
void merge_conv_hull(vector<vector<P> > &a,vector<P> ans[],int max_size)
{
//	int max_size = ans[0][0];

	for(int i=max_size/2;i<max_size;++i)
	{
		ans[i]=a[i-max_size/2];
		//print(ans[i]);
		
	}

//	for(int i=sizeof(a);i<max_size;++i)
//	{vector<P> b; ans.pb(b);	}
int i;
	for(i=max_size/2-1;i>=max_size/4;i--)
	{
		//cout<<i<<endl;
		vector<P> aa,up,lo;

        get_halves(ans[2*i],up,lo);

		merge(up,lo,aa);

		vector<P> bb,up1,lo1;
		get_halves(ans[2*i+1],up1,lo1);

		merge(up1,lo1,bb);

		merge(aa,bb,ans[i]);

		//cout<<i<<":";
		//print(ans[i]);
	}
	for(;i>0;i--)
	{
		merge(ans[2*i],ans[2*i+1],ans[i]);
		
	}
}
int main()
{

	vector<vector<P> > aa;
	vector<P> a,b,c,d,e;

	// First Convex hull object - (x,y) coordinates from left most point in an anti-clockwise direction 
	a.pb(mp(1,2.5));
	a.pb(mp(3,3));
	a.pb(mp(4,2));
	a.pb(mp(3,1));
	a.pb(mp(2,1));
	a.pb(mp(1,2.5));

	// Second Convex hull object - (x,y) coordinates from left most point in an anti-clockwise direction
	b.pb(mp(4,4));
	b.pb(mp(5,5));
	b.pb(mp(6,4));
	b.pb(mp(5,3));
	b.pb(mp(4,4));

	// Third Convex hull object - (x,y) coordinates from left most point in an anti-clockwise direction
	c.pb(mp(3.5,2));
	c.pb(mp(5,3));
	c.pb(mp(5.5,2));
	c.pb(mp(4,1));
	c.pb(mp(3.5,2));

	// Fourth Convex hull object - (x,y) coordinates from left most point in an anti-clockwise direction
	d.pb(mp(4.1,3.8));
	d.pb(mp(4.3,4.8));
	d.pb(mp(4.8,4));
	d.pb(mp(4.1,3.8));

	// Fifth Convex hull object - (x,y) coordinates from left most point in an anti-clockwise direction
	e.pb(mp(5.5,2));
	e.pb(mp(7,9));
	e.pb(mp(8,4));
	e.pb(mp(5.5,2));
	 

	aa.pb(a);
	aa.pb(b);
	aa.pb(c);
	aa.pb(d);
	aa.pb(e);
	

	int i = aa.size();
	int height = (int)ceil(log2(i))+1;
	int max_size = 1<<height;
	vector<P> ans[max_size];
	
	merge_conv_hull(aa,ans,max_size);
		
	cout<<"The sorted points of all the convex hulls are :"<<endl;
	for(int i=0;i<ans[1].size();++i)
	{
		cout<<'('<<ans[1][i].X<<','<<ans[1][i].Y<<") ";

	}
	vector<P> hull;
	conv_hull(ans[1],hull);
	hull.pop_back();
	cout<<"The convex hull is :"<<endl;
	print(hull);
	cout<<endl;

return 0;
}


