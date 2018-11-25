import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N16 {
    static long getNumb(List<Integer> values, long[][] choos, int n, int k) {
        int numb = 0;
        for (int i = 1; i <= k; i++) {
            for (int j = values.get(i - 1) + 1; j < values.get(i); j++) {
                numb += choos[n - j][k - i];
            }                                                                 
        }                                                                     
        return numb;                                                          
    }
    public static void main(String[] args) throws IOException {                
        FastScanner in = new FastScanner(new File("choose2num.in"));
        PrintWriter out = new PrintWriter(new File("choose2num.out"));
        int n = in.nextInt();
        int k = in.nextInt();
        long[][] choos = new long[n + 1][k + 1];       ///////////////////
        for (int i = 0; i < n + 1; i++) {              //000000000000000//
            choos[i][0] = 1;                           ///////////////////
        }
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < k + 1; j++) {
                choos[i][j] = choos[i - 1][j - 1] + choos[i - 1][j];
            }
        }
        List<Integer> values = new ArrayList<Integer>();
        values.add(0);
        //System.out.println(choos[0].length);
        for (int i = 0; i < k; i++) {
            values.add(in.nextInt());                            
        }
        out.print(getNumb(values, choos, n, k));                            
        //out.print(sb.substring(0, sb.length() - 1));        
        out.close();     
    }
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();                                                                            
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}