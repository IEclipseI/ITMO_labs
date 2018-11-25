import java.io.*;
import java.util.*;
import java.lang.Math;


public class E1 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("dsu.in"));
        //Scanner in = new Scanner(new File("dsu.in"));
        PrintWriter out = new PrintWriter(new File("dsu.out"));
        String tmp1 = br.readLine(); 
        StringBuilder str = new StringBuilder();
        while (tmp1 != null) {
            str.append(tmp1);
            str.append(' ');
            tmp1 = br.readLine();
        }
        StringTokenizer in = new StringTokenizer(str.toString());
        int n = Integer.parseInt(in.nextToken());
        int[] ar = new int[n];
        ArrayList<ArrayList<Integer>> inclds = new ArrayList<ArrayList<Integer>>();
        int[] max = new int[n];
        int[] min = new int[n];
        for (int i = 0; i < n; i++) {
            max[i] = i + 1;
            min[i] = i + 1;
            ArrayList<Integer> tmp = new ArrayList<Integer>();
            tmp.add(i);
            inclds.add(tmp);
            ar[i] = i;
        }
        StringTokenizer token;
        while (in.hasMoreTokens()) {
            if (in.nextToken().equals("get")) {
                int k = Integer.parseInt(in.nextToken()) - 1;
                if (in.hasMoreTokens()) {
                    out.println(min[ar[k]] + " " + max[ar[k]] + " " + inclds.get(ar[k]).size());
                    //System.out.println(ar[k]);
                } else {
                    out.print(min[ar[k]] + " " + max[ar[k]] + " " + inclds.get(ar[k]).size());
                }
            } else {
                int k1 = Integer.parseInt(in.nextToken()) - 1;
                int k2 = Integer.parseInt(in.nextToken()) - 1;
                if (ar[k1] != ar[k2]) {
                    if (inclds.get(ar[k1]).size() >= inclds.get(ar[k2]).size()) {
                        min[ar[k1]] = Math.min(min[ar[k1]], min[ar[k2]]);
                        max[ar[k1]] = Math.max(max[ar[k1]], max[ar[k2]]);
                        int size = inclds.get(ar[k2]).size();
                        //System.out.println(inclds.get(ar[k1]).size() +" **** " +size +  " **** " + inclds.get(ar[k2]).size());
                        int bug = ar[k2];
                        for (int i = 0; i < size; i++) {
                            ar[inclds.get(bug).get(i)] = ar[k1];
                            inclds.get(ar[k1]).add(inclds.get(bug).get(i));
                        }
                    } else {
                        min[ar[k2]] = Math.min(min[ar[k1]], min[ar[k2]]);
                        max[ar[k2]] = Math.max(max[ar[k1]], max[ar[k2]]);
                        int size = inclds.get(ar[k1]).size();
                        int bug = ar[k1];
                        for (int i = 0; i < size; i++) {
                            ar[inclds.get(bug).get(i)] = ar[k2];
                            inclds.get(ar[k2]).add(inclds.get(bug).get(i));
                        }
                    }
                } 
            }
            
            //System.out.println(line);
        }
        //System.out.println(Arrays.toString(ar));       
        out.close();     
    }
    
}