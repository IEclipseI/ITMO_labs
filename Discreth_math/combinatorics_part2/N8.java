import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
  
public class N8 {
    static void gen (boolean[] used, List<String> answer,StringBuilder now, int depth, int n, int k, int start) {
        //System.out.println(7);
        if (depth == k) {
            answer.add(now.toString());
        } else {
            for (int i = start + 1; i <= n; i++) {
                if (used[i - 1]) {
                    continue;
                } else {
                    used[i - 1] = true;
                    now.append(i + " ");
                    gen(used, answer, now, depth + 1, n, k, i);
                    used[i - 1] = false;
                    now.delete(now.length() - (Integer.toString(i).length() + 1), now.length());
                }
            }
        }
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("choose.in"));
        PrintWriter out = new PrintWriter(new File("choose.out"));
        int n = in.nextInt();
        int k = in.nextInt();
        int[] ar = new int[n];
        for (int i = 1; i <= n; i++) {
            ar[i-1] = i;
        }
        List<String> answer = new ArrayList<String>();
        StringBuilder sb = new StringBuilder();
        gen(new boolean[n], answer, sb, 0, n, k, 0);
        int numb = 1;
        for (String str: answer) {
            int l = str.length();
            //for(int i = 0; i <l; i++) {
              //  char ch = str.charAt(i);
                out.print(str);
            //}
            out.println();
            //numb++;
        }
        //System.out.println(answer.size());        
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