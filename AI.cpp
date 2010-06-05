int analyze(int k, int l);
int deside(int k, int ag);
void pos(int **map, int **un, int **attai, int **attpl, int kolai, int n)
{
int k,l,ag,m,p,i,j;
for (i=0;i<n;i++)
	for (j=0;j<n;j++)
	{
		if (map[i][j]>0&&attai[i][j]!=0) 
		{
			k++;
			un[i][3]=map[i][j];
		}
		if (map[i][j]==-1&&attpl[i][j]!=0)
		{
			l++;
		};
	};
if (k==0)
{
	for (i=0;i<kolai;i++)
	{
		p=bestp(un[i]);
		j=p/n;
		map[j][p%n]=1;
		map[un[i][1]][un[i][2]]=0;
		un[i][1]=j;
		un[i][2]=p%n;
		un[i][4]=1;
	}
}
else
{
	int t=0;
	i=0;
	m=kolai-k;
	ag=analyze(k, l);
	while (t!=1)
	{
		t=1;
		for (i=0;i<kolai;i++)
			if (un[i][4]==0)
				if (un[i][3]==1)
					{
						attack();
						t=0;
						un[i][4]=1;
					};
		
	};
	for (i=0;i<kolai;i++)
		if (un[i][3]==0)
		{
			j=deside(un[i][3], ag);
			if (j==1)
			{
				attack();
				un[i][4]=1;
			}
			else
			{
				p=bestp(un[i]);
				j=p/n;
				map[j][p%n]=1;
				map[un[i][1]][un[i][2]]=0;
				un[i][1]=j;
				un[i][2]=p%n;
				un[i][4]=1;
			};
		};
};
};
int analyze(int k, int l)
{
	int ag;
	ag=(l-k);
	return ag;
};
int deside(int k, int ag)
{
	if (k<ag) return 1;
else return 0;
};
