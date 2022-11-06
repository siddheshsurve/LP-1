

import java.util.*;

class PageString{
    private int[] pages;
    private String pageStr;
    private int memCap;
    public int n;
    PageString(){
        n=0;
        memCap=0;
    }
    void getPageStr(){
        Scanner sc=new Scanner(System.in);
        System.out.print("Enter page string: ");
        this.pageStr=sc.nextLine();
        System.out.print("Enter memory frame capacity(in terms of number of pages): ");
        this.memCap=sc.nextInt();
        pages=new int[pageStr.length()+1];
        for(int i=0;i<pageStr.length();i++){
            if(pageStr.charAt(i)!=','){
                pages[n]=Integer.parseInt(String.valueOf(pageStr.charAt(i)));;
                n+=1;
            }
        }
        sc.close();
    }
    void getDetails(){
        System.out.println("Number of pages: "+n);
        System.out.print("Pages are: ");
        for(int i=0;i<this.n;i++) {
        	System.out.print(pages[i]+" ");
        }
        System.out.println();
    }
    int FIFO() {
    	HashSet<Integer> s = new HashSet<>(this.n);
        Queue<Integer> indexes = new LinkedList<>();
        int pagefaults=0;
        for(int i=0;i<this.n;i++) {
        	if(s.size()<this.memCap) {
        		if(!s.contains(pages[i])) {
        			s.add(pages[i]);
        			pagefaults+=1;
        			indexes.add(pages[i]);
        		}
        	}
        	else {
        		if(!s.contains(pages[i])) {
        			int r=indexes.peek();
        			indexes.poll();
        			s.remove(r);
        			s.add(pages[i]);
        			indexes.add(pages[i]);
        			pagefaults+=1;
        		}
        	}
        }
        return pagefaults;
    }
    int LRU() {
    	HashSet<Integer> s = new HashSet<>(memCap);
        HashMap<Integer, Integer> indexes = new HashMap<>();
        int pagefaults=0;
        for(int i=0;i<n;i++) {
        	if(s.size()<this.memCap) {
        		if(!s.contains(pages[i])) {
        			s.add(pages[i]);
        			pagefaults+=1;
        		}
        		indexes.put(pages[i], i);
        	}
        	else {
        		if(!s.contains(pages[i])) {
        			int lru = Integer.MAX_VALUE, val=Integer.MIN_VALUE;
                    Iterator<Integer> itr = s.iterator();
                    while (itr.hasNext()) {
                        int temp = itr.next();
                        if (indexes.get(temp) < lru)
                        {
                            lru = indexes.get(temp);
                            val = temp;
                        }
                    }
                    s.remove(val);
                    indexes.remove(val);
                    s.add(pages[i]);
                    pagefaults++;
        		}
        		indexes.put(pages[i], i);
        	}
        }
        return pagefaults;
    }
    int MRU() {
    	HashSet<Integer> s = new HashSet<>(memCap);
        HashMap<Integer, Integer> indexes = new HashMap<>();
        int pagefaults=0;
        for(int i=0;i<n;i++) {
        	if(s.size()<this.memCap) {
        		if(!s.contains(pages[i])) {
        			s.add(pages[i]);
        			pagefaults+=1;
        		}
    
        		indexes.put(pages[i], i);
        	}
        	else {
        		if(!s.contains(pages[i])) {
        			int mru = Integer.MIN_VALUE, val=Integer.MIN_VALUE;
                    Iterator<Integer> itr = s.iterator();
                    while (itr.hasNext()) {
                        int temp = itr.next();
                        if (indexes.get(temp) > mru)
                        {
                            mru = indexes.get(temp);
                            val = temp;
                        }
                    }
                    s.remove(val);
                    indexes.remove(val);
                    s.add(pages[i]);
                    pagefaults++;
        		}
        		indexes.put(pages[i], i);
        	}
        }
        return pagefaults;
    }
    static int predict(int []pg,int []f,int n,int index) {
    	int farthest=index;
    	int ans=-1;
    	for(int i=0;i<f.length;i++) {
    		int j;
    		for(j=index;j<n;j++) {
    			if(f[i]==pg[j]) {
    				if(j>farthest) {
    					farthest=j;
    					ans=i;
    				}
    				break;
    			}
    		}
    		if(j==n) {
				return i;
			}
    	}
    	if(ans!=-1)
			return ans;
		return 0;
    }
    int optimal() {
    	int []frames=new int[this.memCap];
    	int pos=0,pageHits=0;
    	for(int i=0;i<this.n;i++) {
    		if(search(this.pages[i],frames)) {
    			pageHits++;
    			continue;
    		}
    		if(pos<this.memCap) {
    			frames[pos++]=pages[i];
    		}
    		else {
                int j = predict(pages, frames, this.n, i + 1);
                frames[j] = pages[i];
            }	
    	}
    	return this.n-pageHits;
    }
    static boolean search(int key,int []f) {
    	for(int i=0;i<f.length;i++) {
    		if(f[i]==key) {
    			return true;
    		}
    	}
    	return false;
    }
}
public class page_replacement{

	public static void main(String[] args) {
		PageString p=new PageString();
		p.getPageStr();
		p.getDetails();
		ArrayList<Integer> faults= new ArrayList<Integer>();
		faults.add(p.FIFO());
		faults.add(p.LRU());
		faults.add(p.MRU());
		faults.add(p.optimal());
		System.out.println("\nAlgorithm-->    \tFIFO\tLRU\tMRU\tOptimal");
		System.out.println("No of page faults\t"+faults.get(0)+"\t"+faults.get(1)+"\t"+faults.get(2)+"\t"+faults.get(3));
		System.out.println("No of page hits   \t"+(p.n-faults.get(0))+"\t"+(p.n-faults.get(1))+"\t"+(p.n-faults.get(2))+"\t"+(p.n-faults.get(3)));
		String ans[]= {"FIFO","LRU","MRU","Optimal"};
		int a=Collections.min(faults);
		for(int i=0;i<4;i++) {
			if(a==faults.get(i)) {
				System.out.println("\nAs page faults for "+ans[i]+" are minimum ("+a+"), the "+ans[i]+" algorithm is the best for the given situation");
			}
		}
	}

}
