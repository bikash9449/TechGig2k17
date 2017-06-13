
public static int maxPossibleWait(int n,int s,String[] grid)
    {
	//Write code here
	    HashSet<String> hs=new HashSet<String>();
	    HashSet<String> tmp=new HashSet<String>();
	    HashSet<String> mid=new HashSet<String>();
	    char arr[][]=new char[n][n];
	    int my[][]=new int[n][n];
	    int sol[][]=new int[n][n];
	    int res[][]=new int[n][n];
	    int i,j,k,count=0,Mr=0,Mc=0,Sr=0,Sc=0;
	    for(i=0;i<n;++i)
	    for(j=0;j<n;++j)
	    {
	        my[i][j]=sol[i][j]=res[i][j]=0;
	        char ch=grid[i].charAt(j);
	        arr[i][j]=ch;
	        if(ch=='L')
	        {
	            ++count;
	            hs.add(i+"#"+j);
				sol[i][j]=-1;
	        }
	        else if(ch=='M')
	        {
	            Mr=i;
	            Mc=j;
				
	        }
	        else if(ch=='S')
	        {
	            Sr=i;
	            Sc=j;
	        }
        
        
	    }
	    long min=0,reach=-1,find=-1;
	    tmp.add(Mr+"#"+Mc);
	    int step=1;				//baad me multiple jumps consider karna hai
		my[Mr][Mc]=-1;
	    while(true)
	    {
			mid=new HashSet<String>();
	        for(String each:tmp)
	        {
	            int x,y;
	            String token[]=each.split("#");
	            x=Integer.parseInt(token[0]);
	            y=Integer.parseInt(token[1]);
	            if(x>0 && my[x-1][y]==0 && arr[x-1][y]=='O')
	            {
					my[x-1][y]=step;
					mid.add((x-1)+"#"+y);
				}
			
	            if(y>0 && my[x][y-1]==0  && arr[x][y-1]=='O')
				{
					my[x][y-1]=step;
					mid.add(x+"#"+(y-1));
				} 
	            if(y<n-1 && my[x][y+1]==0  && arr[x][y+1]=='O')
	            {
					my[x][y+1]=step;
					mid.add(x+"#"+(y+1));
				}
	            if(x<n-1 && my[x+1][y]==0  && arr[x+1][y]=='O')
	            {
					my[x+1][y]=step;
					mid.add((x+1)+"#"+y);
				}
	            
	        }
			if(mid.size()==0)
				break;
			tmp=mid;
	        ++steps;//step=step/s+1;
	    }
		step=1;
		while(true)
	    {
			mid=new HashSet<String>();
	        for(String each:hs)
	        {
	            int x,y;
	            String token[]=each.split("#");
	            x=Integer.parseInt(token[0]);
	            y=Integer.parseInt(token[1]);
	            if(x>0 && sol[x-1][y]==0  && arr[x-1][y]=='O')
	            {
					sol[x-1][y]=step;
					mid.add((x-1)+"#"+y);
				}
			
	            if(y>0 && sol[x][y-1]==0  && arr[x][y-1]=='O')
				{
					sol[x][y-1]=step;
					mid.add(x+"#"+(y-1));
				} 
	            if(y<n-1 && sol[x][y+1]==0  && arr[x][y+1]=='O')
	            {
					sol[x][y+1]=step;
					mid.add(x+"#"+(y+1));
				}
	            if(x<n-1 && sol[x+1][y]==0  && arr[x+1][y]=='O')
	            {
					sol[x+1][y]=step;
					mid.add((x+1)+"#"+y);
				}
	            
	        }
			if(mid.size()==0)
				break;
			hs=mid;
	        ++step;
	    }
		
		int result=0;
		if(Sr>0 && result<sol[Sr-1][Sc]-my[Sr-1][Sc])
		{
			result=sol[Sr-1][Sc]-my[Sr-1][Sc];
		}
		if(Sc>0 && result<sol[Sr][Sc-1]-my[Sr][Sc-1])
		{
			result=sol[Sr][Sc-1]-my[Sr][Sc-1];
		}
		if(Sr<n-1 && result<sol[Sr+1][Sc]-my[Sr+1][Sc])
		{
			result=sol[Sr+1][Sc]-my[Sr+1][Sc];
		}
		if(Sc<n-1 && result<sol[Sr][Sc+1]-my[Sr][Sc+1])
		{
			result=sol[Sr][Sc+1]-my[Sr][Sc+1];
		}
		/*for(i=0;i<n;++i)
		{
			for(j=0;j<n;++j)
			{
				System.out.print(my[i][j]+" ");
			}
			System.out.println();
		}
	    for(i=0;i<n;++i)
		{
			for(j=0;j<n;++j)
			{
				System.out.print(sol[i][j]+" ");
			}
			System.out.println();
		}*/
	    return result-1;
    }