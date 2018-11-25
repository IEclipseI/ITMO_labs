import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N9 {
    static void gen (List<String> answer,StringBuilder now, int size, int n, int balance, int open) {
        //System.out.println(7);
        if (size == 2*n) {
            answer.add(now.toString());
        } else {
            if (open < n) {
                now.append('(');
                gen(answer, now, size + 1, n, balance + 1, open + 1);
                now.deleteCharAt(now.length() - 1);
            }
            if (balance > 0) {
                now.append(')');
                gen(answer, now, size + 1, n, balance - 1, open);
                now.deleteCharAt(now.length() - 1);
            }
        }
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("brackets.in"));
        PrintWriter out = new PrintWriter(new File("brackets.out"));
        int n = in.nextInt();
        List<String> answer = new ArrayList<String>();
        StringBuilder sb = new StringBuilder();
        gen(answer, sb, 0, n, 0, 0);
        for (String str: answer) {
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