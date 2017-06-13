
#define for1(i,s,n) for(i=s;i<n;++i)
#define for2(i,s,n) for(i=s;i<=n;++i)
#include<vector>
#include<algorithm>
using namespace std;
class res{
        public:
        int top,left,down,right,cost;
        res(int a,int b,int c,int d,int e)
        {
            top=a;
            left=b;
            down=c;
            right=d;
            cost=e;
        }
    };
    int myComp(const res& a,const res& b)
    {
	    return a.cost<b.cost;
    }
class sparse{
    public:
    int r,c;
    sparse(int a,int b)
    {
        r=a;
        c=b;
    }
};
    int row,col,expense,tempExp=0,**grid,vecSize,finalAns=0;
    bool *dataCk;
    vector<res> dataS;
    int findMaxEmptyPlot()
    {
        int **dynamo,i,j=4*col,k,result=finalAns;
        dynamo=(int **)malloc(8*row);
        for(i=0;i<row;++i)
        dynamo[i]=(int *)malloc(j);
        for (i=0;i<col;i++)
        {
            dynamo[0][i] = grid[0][i];
        }
        
        for (i=1;i<row;i++)
        {
            for (j=0;j<col;j++)
            {
             dynamo[i][j] = dynamo[i-1][j]+grid[i][j];
            }
        }
        
        for (i=0;i<row;i++)
        {
            for (j=1;j<col;j++)
            {
               dynamo[i][j] += dynamo[i][j-1];
            }
        }
        /*for1(i,0,row)
        {
            for1(j,0,col)
            printf("%dt",grid[i][j]);
            printf("n");
        }
        printf("----------------n");
        */
        for1(i,0,row)
        {
            for1(j,0,col)
            {
                int btm,rght,maxSide,mxtmp;
                maxSide=col-j;
                mxtmp=row-i;
                if(mxtmp<maxSide)
                maxSide=mxtmp;
                for1(k,result,maxSide)
                {
                    btm=i+k;
                    rght=j+k;
                    int ans=dynamo[btm][rght];
                    if(i>0)
                    ans-=dynamo[i-1][rght];
                    if(j>0)
                    ans-=dynamo[btm][j-1];
                    if(i>0 && j>0)
                    {
                        ans+=dynamo[i-1][j-1];
                    }
                    if(ans>0)
                    break;
                    //ans == 0 then only lower line will execute
                    result=k+1;
                    
                    
                }
                
            }
        }
        free(dynamo);
        return result;
        
    }
    void bfs(int cur)
    {
        int i,j,k;
        for1(k,cur,vecSize)
        {
        if(expense<tempExp+dataS[k].cost)
        break;
        if(!dataCk[k])
        {
            dataCk[k]=true;
            int ans;
            tempExp+=dataS[k].cost;
            vector<sparse> reput;
            for1(i,dataS[k].top-1,dataS[k].down)
            for1(j,dataS[k].left-1,dataS[k].right)
            {
                reput.push_back(sparse(i,j));
                --grid[i][j];
            }
            ans=findMaxEmptyPlot();
            //printf("n---%d--Expense=%d---n",ans,tempExp);
            if(ans>finalAns)
            {
                finalAns=ans;
            }
            bfs(cur+1);
            dataCk[k]=false;
            tempExp-=dataS[k].cost;
            int reputSize=reput.size();
            for1(i,0,reputSize)
            ++grid[reput[i].r][reput[i].c];
            
        }
    }
        
    }
    int maxLength(char* rc,int mxCost,int resSize,int noRow,char** objCreator)
    {
        sscanf(rc,"%d,%d",&row,&col);
        //printf("%d %d",row,col);
        //int i;
        expense=mxCost;
        int i=4*col,j,it1,it2;
        grid=(int **)malloc(8*row);
		for1(it1,0,row)
		{
			grid[it1]=(int *)malloc(i);
			/*for1(it2,0,col)
			{
				grid[it1][it2]=0;
			}*/
		}
		dataCk=(bool *)malloc(sizeof(bool)*resSize);
        for(i=0;i<noRow;++i)
        {
            //char* tmp=strdup(objCreator[i]);
           char * pt;
            int arr[5];
            j=0;
            pt=strtok(strdup(objCreator[i]),",");
            while(pt!=NULL)
            {
                sscanf(pt,"%d",&arr[j]);
                ++j;
                pt=strtok(NULL,",");
            }
            //dataS.push_back(res(arr[0],arr[1],arr[2],arr[3],arr[4]));
            int x1=arr[0],y1=arr[1],x2=arr[2],y2=arr[3],c1=arr[4];
            dataS.push_back(res(x1,y1,x2,y2,c1));
            dataCk[i]=false;
			for1(it1,x1-1,x2)
			{
				for1(it2,y1-1,y2)
				{
					++grid[it1][it2];
				}
			}
            
        }
        vecSize=resSize;
        sort(dataS.begin(),dataS.end(),myComp);
        /*for(i=0;i<resSize;++i)
        {
            printf("%d %d %d %d %dn",dataS[i].top,dataS[i].left,dataS[i].down,dataS[i].right,dataS[i].cost);
        }*/
        //grid[1][1]=grid[4][4]=1;//for testing garden finding logic
        //grid[3][5]=grid[4][5]=0;//for testing garden finding logic
       /* for1(i,0,row)
        {
            for1(j,0,col)
            {
               printf("%d ",grid[i][j]); 
            }
            printf("n");
        }
        */
        /*for1(i,0,resSize)
        printf("%d ",dataCk[i]);
        */
        int value;
        if(mxCost<dataS[0].cost)//this part is done
		{
			value=findMaxEmptyPlot();
		}
		else
		{
		    tempExp=0;
		    bfs(0);
		    value=finalAns;
		}
		free(grid);
		free(dataCk);
        return value;
        
    }